// peaBrain 3.4
// Evaluation Module
// Port from pChess 2.0rc7 on April 13, 2013
//
// Copyright 2013 by John Roland Penner <johnrolandpenner-at-gmail-dot-com>
// Created: April 13, 2013 (Toronto Island)
// Updated: April 15, 2013


int staticEval( boardRecord &theBoard )
{
	//-------------------------------------    <---- gree
	int _whitee = 1;
	int _blackk = -1;		

	// Eval Switches
	bool _eval01material 	= true;
	bool _eval02mobility 	= true;
	bool _evalCastleBonus 	= true;
	bool _evalPawnTropism 	= true;
	bool _evalKingGravity 	= true;
	bool _evalKingSafety 	= true;
	bool _evalKnightTropism = true;
	bool _evalBishopPair 	= true;

	// Pickup Evaluation Weights
	int gWtMobility = _wtMobility;
	int gCastleBonus = _wtCastleBonus;
	int gWtTropism = _wtTropism;
	int gWtKingGravity = _wtKingGravity;
	int gWtPassedPawn = _wtPassedPawn;
	int gWtDoubledPawn = _wtDoubledPawn;
	int gWtKingShelter = _wtKingShelter;
	int gWtBishopPair = _wtBishopPair;


	// King Tropism kZone2 Vectors (first set for 8x8; second set for 10x12)
	int kZone2[16] = {14, 15, 16, 17, 18, 10, 2, -6, -14, -15, -16, -17, -18, -10, -2, 6};
	int kZone220[16] = {18, 19, 20, 21, 22, 12, 2, -8, -18, -19, -20, -21, -22, -12, -2, 8};

	// King Tropism kZone3 Vectors (first set for 8x8; second set for 10x12)
	int kZone3[9] = {7, 8, 9, 1, -7, -8, -9, -1, 0};
	int kZone320[9] = {9, 10, 11, 1, -9, -10, -11, -1, 0};
	
	//-------------------------------------    <---- gree

	/* Claude Shannon (1949):
	f(p) = 200(K-K') + 9(Q-Q') + 5(R-R') + 3(B-B'+N-N') + 1(P-P')
		  - 0.5(D-D'+S-S'+I-I') + 0.1(M-M') + ...
	 KQRBNP = number of kings, queens, rooks, bishops, knights and pawns
	 D,S,I  = doubled, blocked and isolated pawns
	 M      = Mobility (the number of legal moves) 
	*/

	int querySquare, pieceType;
	int wP, wB, wN, wR, wQ, wK;
	int bP, bB, bN, bR, bQ, bK;
	int who2hold, wM, bM;
	int materialScore, positionalScore, mobilityScore;
	int staticScore, numMoves, numReplies;
	int z, n, n2, fromPiece;

	// NOTE: used for kingGravity, but declared globally, 
	// are: sq2mask(63) and maskBoard(119) -- i believe this
	// is faster than redeclaring them everytime in the loop. 
	int wKingSq, bKingSq, kingField[64], testSq;
	int wKingSq120, bKingSq120, testSq120;
	int kingGravityScore, wKingGravity, bKingGravity;

	boardRecord scoreBoard;
	moveRecord moves[_maxMoves];

	// initialize scoring setup
	staticScore = 0;
	positionalScore = 0;
	wKingSq = _noSuchSquare;
	bKingSq = _noSuchSquare;

	//======================================================
	// FIRST Evaluator: MATERIAL Score

	materialScore = 0;

	if (_eval01material) {

		wP = wB = wN = wR = wQ = wK = bP = bB = bN = bR = bQ = bK = 0;

		for (querySquare = 0; querySquare < 64; querySquare++) {
			pieceType = theBoard.square[querySquare];
			switch (pieceType) {

				case 1 : wP++; break;
				case 2 : wB++; break;
				case 3 : wN++; break;
				case 4 : wR++; break;
				case 5 : wQ++; break;
				case 6 : wK++; wKingSq = querySquare; break;	//	used in kingGravity

				case -1 : bP++; break;
				case -2 : bB++; break;
				case -3 : bN++; break;
				case -4 : bR++; break;
				case -5 : bQ++; break;
				case -6 : bK++; bKingSq = querySquare; break;	//	used in kingGravity
				}
			}
		
		materialScore = gPieceWt[6] * (wK-bK) + gPieceWt[5] * (wQ-bQ) + gPieceWt[4] * (wR-bR) + gPieceWt[3] * (wN-bN) + gPieceWt[2] * (wB-bB) + gPieceWt[1] * (wP-bP);
	}

	//==================================================
	// Evaluators: MOBILITY | KING GRAVITY | KING SAFETY
	// 

	scoreBoard = theBoard;
	who2hold = scoreBoard.who2move;

	kingGravityScore = wKingGravity = bKingGravity = 0;

	// WHITE MOBILITY score
	scoreBoard.who2move = 1;
	numMoves = 0;
	wM = generateRawMoves(scoreBoard, moves, numMoves);

	if ( _evalKingGravity ) {
	
		for (z = 0; z < 64; z++) {		// begin white kingGRAVITY: initialize the kingField()
			kingField[z] = 0;
			}

		bKingSq120 = sq2Mask[bKingSq];
		
		for (z = 0; z < 16; z++) {			// cycle thru kZone2, and test if each vector is on the theBoard
			testSq = bKingSq + kZone2[z];
			testSq120 = bKingSq120 + kZone220[z];
			
			if (testSq120 < 0) testSq120 = 0;
			if (testSq120 > 119) testSq120 = 119;
			
			if (gMaskBoard[testSq120] == 1) kingField[testSq] = 2;
		}
		
		
		for (z = 0; z < 9; z++) {			// cycle thru kZone3, and test if each vector is on the theBoard
			testSq120 = bKingSq120 + kZone320[z];
			testSq = bKingSq + kZone3[z];
			
			if (gMaskBoard[testSq120] == 1 ) kingField[testSq] = 3;
			}
		
		// finished creating the white king target - now its time to see how many moves hit it.
		for (z = 0; z < wM; z++) {
			wKingGravity = wKingGravity + kingField[moves[z].toSquare];
			}

		}
	
	// KING SAFETY
	if ( _evalKingSafety ) {
		if (who2hold == _whitee) {			// white king safety eval
			if (wKingSq == 2  ||  wKingSq == 1) {
				if (theBoard.square[9] > 0) wKingGravity += gWtKingShelter;
				if (theBoard.square[10] > 0) wKingGravity += gWtKingShelter;
				}
			if (wKingSq == 6) {
				if (theBoard.square[13] > 0) wKingGravity += gWtKingShelter;
				if (theBoard.square[14] > 0) wKingGravity += gWtKingShelter;
				}
			}
		}
	
	
	// BLACK MOBILITY score
	scoreBoard.who2move = -1;
	numMoves = 0;
	bM = generateRawMoves(scoreBoard, moves, numMoves);
	
	if ( _evalKingGravity ) {
		
		for (z = 0; z < 64; z++) {			// begin BLACK kingGRAVITY: initialize the kingField()
			kingField[z] = 0;
			}
		
		wKingSq120 = sq2Mask[wKingSq];
		
		for (z = 0; z < 16; z++) {			// cycle thru kZone2, and test if each vector is on the theBoard
			testSq = wKingSq + kZone2[z];
			testSq120 = wKingSq120 + kZone220[z];
			
			if (testSq120 < 0) testSq120 = 0;
			if (testSq120 > 119) testSq120 = 119;
			
			if (gMaskBoard[testSq120] == 1 ) kingField[testSq] = 2;
			}
		
		for (z = 0; z < 9; z++) {			// cycle thru kZone3, and test if each vector is on the theBoard
			testSq120 = wKingSq120 + kZone320[z];
			testSq = wKingSq + kZone3[z];
			
			if (gMaskBoard[testSq120] == 1 ) kingField[testSq] = 3;
				
			}
		
		// finished creating the black king target - now its time to see how many moves hit it. 
		for (z = 0; z < bM; z++) {
			bKingGravity = bKingGravity + kingField[moves[z].toSquare];
			}
		
		}

	// KING SAFETY
	// FIND: this eval feature needs update for fischer!!
	if ( _evalKingSafety ) {				// black king safety eval
		if (who2hold == _blackk) {
			if (bKingSq == 57  ||  bKingSq == 58) {
				if (theBoard.square[49] < 0) bKingGravity += gWtKingShelter;
				if (theBoard.square[50] < 0) bKingGravity += gWtKingShelter;
				}
			if (bKingSq == 62) {
				if (theBoard.square[53] < 0) bKingGravity += gWtKingShelter;
				if (theBoard.square[54] < 0) bKingGravity += gWtKingShelter;
				}
			}
		}

	scoreBoard.who2move = who2hold;				// reset who2move and score mobility
	mobilityScore = wM - bM;
	
	kingGravityScore = (wKingGravity - bKingGravity) * gWtKingGravity;	
	
	
	//=======================================================================
	// CASTLE BONUS Evaluator
	// we want to promote castling - but not into peril. 
	// hence, it should promote castling, but only into a sheltered position. 
	// rnbq1rk1/pp3ppp/2p2b2/3p4/Q2P4/2N2N2/PP2PPPP/R3KB1R w KQ -
	// the above FEN should NOT castle to queenside (a disaster!); rather e3!

	// FIND: this eval feature needs update for fischer!!

	int castleScore = 0;
	int wCastleScore = 0;
	int bCastleScore = 0;
	
	if (_evalCastleBonus) {
		if (theBoard.wHasCastled) {
			//grrrrrrrreeeee  	if ((wKingSq <> 2  &&  wKingSq <> 6)  ||  (wKingSq = 2  &&  theBoard.square[10] = 1)  || (wKingSq = 6  &&  theBoard.square[14] = 1)) {	//if theBoard.wHasCastled = _true then wCastleScore = 10 else wCastleScore = -5
			if ((wKingSq != 2  &&  wKingSq != 6)  ||  (wKingSq == 2  &&  theBoard.square[10] == 1)  || (wKingSq == 6  &&  theBoard.square[14] == 1)) { 		//if theBoard.wHasCastled = _true then wCastleScore = 10 else wCastleScore = -5
				wCastleScore = gCastleBonus;
				}
			else {
				wCastleScore = -5;
				}
			}

		if (theBoard.bHasCastled) {
			//if ((bKingSq <> 58  &&  bKingSq <> 62)  ||  (bKingSq = 58  &&  theBoard.square[50] = -1)  ||  (bKingSq = 62  &&  theBoard.square[54] = -1)) {			//if theBoard.bHasCastled = _true then bCastleScore = 10 else bCastleScore = -5
			if ((bKingSq != 58  &&  bKingSq != 62)  ||  (bKingSq == 58  &&  theBoard.square[50] == -1)  ||  (bKingSq == 62  &&  theBoard.square[54] == -1)) { 			//if theBoard.bHasCastled = _true then bCastleScore = 10 else bCastleScore = -5
				bCastleScore = gCastleBonus;
				}
			else {
				bCastleScore = -5;
				}
			}
		
		}

	//castleScore = (wCastleScore - bCastleScore) * gCastleBonus
	castleScore = wCastleScore - bCastleScore;


//	this one was confusing - gree
	
	//========================================================
	// PAWN Evaluator (PAWN TROPISM / PASSED / DOUBLED)
	// A Passed Pawn increases in strength as the 
	// number of pieces on the theBoard diminishes.  (Capablanca)
	// pawn tester FEN: 8/pppppppp/8/8/8/8/PPPPPPPP/8 w KQkq

	int rank, offset, passed, doubled;
	int tropismScore = 0;
	int wTropism = 0;
	int bTropism = 0;

	if (_evalPawnTropism) {

		for (querySquare = 0; querySquare < 64; querySquare++) {

			pieceType = theBoard.square[querySquare];

			// WHITE PAWN Tests
			if (pieceType == 1) {
				rank = passed = doubled = offset = 0;
				rank = sq2Y(querySquare);
				
				wTropism = wTropism + gWhitePawnTropism[querySquare];		// add white pawn tropism
				
				if (querySquare < 56) {
					// check for doubled white pawns
					if (theBoard.square[querySquare + 8] == 1) doubled = 1;

					// check for white passed pawn
					passed = 1;
					for (z = 0; z < 8 - rank; z++) {
						offset = 8 * z;
						if (querySquare - offset <= 63) { 		//	<---- < 64 [?] gree
							if (theBoard.square[querySquare + offset] != 0) {
								passed = 0;
								break;
								}
							}
						}
					}
				
				if (doubled == 1) {
					wTropism = wTropism - gWtDoubledPawn;
					doubled = 0;
					}
				if (passed == 1) {
					wTropism = wTropism + gWtPassedPawn;
					passed = 0;
					}
				}
			
			// BLACK PAWN Tests
			if (pieceType == -1) {
				rank = passed = doubled = offset = 0;
				rank = sq2Y(querySquare);
			
				bTropism = bTropism + gBlackPawnTropism[querySquare];		//add black pawn tropism
				
				if (querySquare > 7) {
					if (theBoard.square[querySquare - 8 ] == -1) doubled = 1;	// check for doubled black pawns
					
					passed = 1;												// check for black passed pawn
					
					for (z = 0; z <= rank; z++) {
						offset = 8 * z;
						if (querySquare - offset >= 0) {
							if (theBoard.square[querySquare - offset] != 0) {
								passed = 0;
						 		break;
								}
							}
						}
					}
					
				if (doubled == 1) {
					bTropism = bTropism - gWtDoubledPawn;
					doubled = 0;
					}
				
				if (passed == 1) {
					bTropism = bTropism + gWtPassedPawn;
					passed = 0;
					}
				
				}
			
			}	//next querySquare
			
		tropismScore = (wTropism - bTropism) * gWtTropism;
	}


	//==========================================
	// KNIGHT TROPISM Evaluator

	int knightTropismScore = 0;
	int wKnightTropism = 0;
	int bKnightTropism = 0;

	if ( _evalKnightTropism ) {
		for (querySquare = 0; querySquare < 64; querySquare++) {
			pieceType = theBoard.square[querySquare];
			if (pieceType == 3) wKnightTropism += gWhiteKnightTropism[querySquare];
			if (pieceType == -3) bKnightTropism += gBlackKnightTropism[querySquare];
			}
		
			knightTropismScore = wKnightTropism - bKnightTropism;
		}


	//==========================================
	// BISHOP PAIR Evaluator
	// An unpaired bishop and knight are of equal value.. 
	// The bishop pair has an average value of half a pawn. 
	// (GM Larry Kaufman, The Evaluation of Material Imbalances, Chess Life, 1999)

	int wBishopPairScore = 0;
	int bBishopPairScore = 0;
	int bishopPairScore = 0;

	if ( _evalBishopPair ) {
		if (wB >= 2) wBishopPairScore += _wtBishopPair;
		if (bB >= 2) bBishopPairScore += _wtBishopPair;
		}

	bishopPairScore = wBishopPairScore - bBishopPairScore;

	//==========================================
	// Sum all the Evaluative Scores and Invert for Black -- 
	// because we must return the score relative to the side2move (!!)

	positionalScore = mobilityScore + kingGravityScore;
	positionalScore = positionalScore + castleScore;
	positionalScore = positionalScore + tropismScore;
	positionalScore = positionalScore + knightTropismScore;
	positionalScore = positionalScore + bishopPairScore;

	positionalScore = positionalScore / 2;				//normalize to ~160 centiPawns
	staticScore = (materialScore + positionalScore) * theBoard.who2move;

	return staticScore;
}
