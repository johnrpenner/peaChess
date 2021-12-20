// peaBrain 3.4
// Recursive Search Engine
// 
// Copyright 2013 by John Roland Penner <johnrolandpenner-at-gmail-dot-com>
// Created: April 19, 2012 (Toronto Island)
// Updated: April 14, 2013

void makeMove( boardRecord &theBoard, moveRecord theMove )
{
    int y1, y2, pieceType;

    y1 = sq2Y(theMove.fromSquare) + 1;
    y2 = sq2Y(theMove.toSquare) + 1;
    
    pieceType = theBoard.square[ theMove.fromSquare ];

    // PAWN ENPASSANT
    if (pieceType == 1) {
        
		//test and take White enPassant West
		if ( (theMove.fromSquare > 32) && (theMove.fromSquare < 40) ) {
			if ( (theBoard.square[theMove.fromSquare]==1) && (theBoard.square[theMove.fromSquare-1] == -1) && (theMove.toSquare - theMove.fromSquare == 7) && (theMove.fromSquare-1 == theBoard.enPassantSq) ) {
				theBoard.square[theMove.fromSquare-1] = 0;
				theBoard.square[theMove.toSquare] = theBoard.square[theMove.fromSquare];
				theBoard.square[theMove.fromSquare] = 0;
				theBoard.halfMoves++;
				theBoard.who2move = -theBoard.who2move;
				theBoard.enPassantSq = _noSuchSquare;
				return;
				}
			}

		//test and take White enPassant East
		if ( (theMove.fromSquare > 31) && (theMove.fromSquare < 39) ) {
			if ( (theBoard.square[theMove.fromSquare]==1) && (theBoard.square[theMove.fromSquare+1] == -1) && (theMove.toSquare - theMove.fromSquare == 9) && (theMove.fromSquare+1 == theBoard.enPassantSq) ) {
				theBoard.square[theMove.fromSquare+1] = 0;
				theBoard.square[theMove.toSquare] = theBoard.square[theMove.fromSquare];
				theBoard.square[theMove.fromSquare] = 0;
				theBoard.halfMoves++;
				theBoard.who2move = -theBoard.who2move;
				theBoard.enPassantSq = _noSuchSquare;
				return;
				}
			}		
        }

    if (pieceType == -1) {
		//test and take Black enPassant West
		if ( (theMove.fromSquare > 23) && (theMove.fromSquare < 31) ) {
			if ( (theBoard.square[theMove.fromSquare]==-1) && (theBoard.square[theMove.fromSquare+1] == 1) && (theMove.fromSquare - theMove.toSquare == 7) && (theMove.fromSquare+1 == theBoard.enPassantSq) ) {
				theBoard.square[theMove.fromSquare+1] = 0;
				theBoard.square[theMove.toSquare] = theBoard.square[theMove.fromSquare];
				theBoard.square[theMove.fromSquare] = 0;
				theBoard.halfMoves++;
				theBoard.who2move = -theBoard.who2move;
				theBoard.enPassantSq = _noSuchSquare;
				return;
				}
			}

		//test and take Black enPassant East
		if ( (theMove.fromSquare > 24) && (theMove.fromSquare < 32) ) {
			if ( (theBoard.square[theMove.fromSquare]==-1) && (theBoard.square[theMove.fromSquare-1] == 1) && (theMove.fromSquare - theMove.toSquare == 9) && (theMove.fromSquare-1 == theBoard.enPassantSq) ) {
				theBoard.square[theMove.fromSquare+1] = 0;
				theBoard.square[theMove.toSquare] = theBoard.square[theMove.fromSquare];
				theBoard.square[theMove.fromSquare] = 0;
				theBoard.halfMoves++;
				theBoard.who2move = -theBoard.who2move;
				theBoard.enPassantSq = _noSuchSquare;
				return;
				}
			}		
        }
		

    // KING CASTLING
    if (pieceType == 6) {
        
        // castling - white-kingSide
        if ( (theMove.fromSquare == 4) && (theMove.toSquare==6) && (theBoard.square[4]==6) && (theBoard.square[7]==4) ) {
            theBoard.square[theMove.toSquare] = theBoard.square[theMove.fromSquare];
            theBoard.square[theMove.fromSquare] = 0;
            theBoard.square[5] = 4;
            theBoard.square[7] = 0;
            theBoard.wCastleKside = false;
            theBoard.wCastleQside = false;
            theBoard.wHasCastled = true;
            theBoard.who2move = -theBoard.who2move;
            theBoard.halfMoves++;
            return;
            }

        // castling - white-queenSide
        if ( (theMove.fromSquare == 4) && (theMove.toSquare==2) && (theBoard.square[4]==6) && (theBoard.square[0]==4) ) {
            theBoard.square[theMove.toSquare] = theBoard.square[theMove.fromSquare];
            theBoard.square[theMove.fromSquare] = 0;
            theBoard.square[3] = 4;
            theBoard.square[0] = 0;
            theBoard.wCastleKside = false;
            theBoard.wCastleQside = false;
            theBoard.wHasCastled = true;
            theBoard.who2move = -theBoard.who2move;
            theBoard.halfMoves++;
            return;
            }
        }
    
    if (pieceType == -6) {
        
        // castling - black-kingSide
        if ( (theMove.fromSquare == 60) && (theMove.toSquare==62) && (theBoard.square[60]==-6) && (theBoard.square[63]==-4) ) {
            theBoard.square[theMove.toSquare] = theBoard.square[theMove.fromSquare];
            theBoard.square[theMove.fromSquare] = 0;
            theBoard.square[61] = -4;
            theBoard.square[63] = 0;
            theBoard.bCastleKside = false;
            theBoard.bCastleQside = false;
            theBoard.bHasCastled = true;
            theBoard.who2move = -theBoard.who2move;
            theBoard.halfMoves++;
            return;
        }
        
        // castling - black-queenSide
        if ( (theMove.fromSquare == 60) && (theMove.toSquare==58) && (theBoard.square[60]==-6) && (theBoard.square[56]==-4) ) {
            theBoard.square[theMove.toSquare] = theBoard.square[theMove.fromSquare];
            theBoard.square[theMove.fromSquare] = 0;
            theBoard.square[59] = -4;
            theBoard.square[56] = 0;
            theBoard.bCastleKside = false;
            theBoard.bCastleQside = false;
            theBoard.bHasCastled = true;
            theBoard.who2move = -theBoard.who2move;
            theBoard.halfMoves++;
            return;
        }
    }
	

    //==| MAKE MOVE |========================================
    // if !funkyMove >> then make Regular Move and bump the moveRecord
	
    // make the actual move
    theBoard.square[ theMove.toSquare ] = theBoard.square[ theMove.fromSquare ];
    theBoard.square[ theMove.fromSquare ] = 0;
    theBoard.who2move = -theBoard.who2move;
    //theBoard.hashCode = not( theBoard.hashCode );
    theBoard.halfMoves++;

    // Pawn to Queen Promotion (queen always assumed)
    if ( (pieceType == 1) && (y1==7) && (y2==8) ) {
        theBoard.square[theMove.toSquare] = 5;
        gPromotion = true;
        //theMove.promoPiece = 5;
        }
    if ( (pieceType == -1) && (y1==2) && (y2==1) ) {
        theBoard.square[theMove.toSquare] = -5;
        gPromotion = true;
        //theMove.promoPiece = -5;
        }

    // if the King or either Rook has moved, we can no longer castle
    if (pieceType == 6) theBoard.wCastleKside = false;
    if (pieceType == -6) theBoard.bCastleKside = false;
    if ( (pieceType == 4) && (theMove.fromSquare==0) ) theBoard.wCastleQside = false;
    if ( (pieceType == 4) && (theMove.fromSquare==7) ) theBoard.wCastleKside = false;
    if ( (pieceType == -4) && (theMove.fromSquare==56) ) theBoard.bCastleQside = false;
    if ( (pieceType == -4) && (theMove.fromSquare==63) ) theBoard.bCastleKside = false;
    
    // handle SETTING enPassant (into the new board)
    theBoard.enPassantSq = _noSuchSquare;
    if ( (pieceType == 1) && (y1==2) && (y2==4) ) theBoard.enPassantSq = theMove.toSquare;
    if ( (pieceType == -1) && (y1==7) && (y2==5) ) theBoard.enPassantSq = theMove.toSquare;
	
    gMovesMade++;
    return;

}


// based on robert purves insertion method [rip]
void sortMoves( moveRecord moves[], int numMoves )
{
	int i, j;
	struct moveRecord tempMove;
	
	for (j=1; j<numMoves; j++) {
		tempMove = moves[j];
		for (i=j-1; i<1; i--) {
			// need to compare abs() values, or else black & white get sorted differently
			if ( abs(moves[i].capturedPiece) >= abs(tempMove.capturedPiece) ) break;
			moves[i+1] = moves[i];
			}
		moves[i+1] = tempMove;
		}
	
}


bool isAttacked( int querySquare, boardRecord &theBoard )
{
    bool attacked = false;
    int numMoves = 0;
    int n, sq, pieceType;
    int attackedSquares[_maxMoves];

    pieceType = theBoard.square[querySquare];
    
    for (sq=0; sq<64; sq++) {

		// white pawn attacks
		if ( (theBoard.square[sq] == 1) && (theBoard.who2move == 1) ) {
			numMoves = wPawnAttacks( theBoard, attackedSquares, 0, sq );
			for (n=0; n<numMoves; n++) {
				if (attackedSquares[n] == querySquare) {
				attacked = true; 
				return attacked;
				}
			}
		}

		// black pawn attacks
	    if ( (theBoard.square[sq] == -1) && (theBoard.who2move == -1) ) {
			numMoves = bPawnAttacks( theBoard, attackedSquares, 0, sq );
			for (n=0; n<numMoves; n++) {
				if (attackedSquares[n] == querySquare) {
				attacked = true; 
				return attacked;
				}
			}
		}

		// bishop (and diagonal queen) attacks
		if ( (-(theBoard.square[sq] * theBoard.who2move == 2)) | (-(theBoard.square[sq] * theBoard.who2move == 5)) ) {
			numMoves = bishopAttacks( theBoard, attackedSquares, 0, sq, theBoard.who2move );
			for (n=0; n<numMoves; n++) {
				if (attackedSquares[n] == querySquare) {
				attacked = true; 
				return attacked;
				}
			}
		}

		// knight attacks
		if ( theBoard.square[sq] * theBoard.who2move == 3 ) {
			numMoves = knightAttacks( theBoard, attackedSquares, 0, sq, theBoard.who2move );
			for (n=0; n<numMoves; n++) {
				if (attackedSquares[n] == querySquare) {
				attacked = true; 
				return attacked;
				}
			}
		}

		// rook (and perpendicular queen) attacks
		if ( (-(theBoard.square[sq] * theBoard.who2move == 4)) | (-(theBoard.square[sq] * theBoard.who2move == 5)) ) {
			numMoves = rookAttacks( theBoard, attackedSquares, 0, sq, theBoard.who2move );
			for (n=0; n<numMoves; n++) {
				if (attackedSquares[n] == querySquare) {
				attacked = true; 
				return attacked;
				}
			}
		}

		// white king attacks
		if ( (theBoard.square[sq] == 6) && (theBoard.who2move == 1) ) {
			numMoves = wKingAttacks( theBoard, attackedSquares, 0, sq );
			for (n=0; n<numMoves; n++) {
				if (attackedSquares[n] == querySquare) {
				attacked = true; 
				return attacked;
				}
			}
		}

		// black king attacks
		if ( (theBoard.square[sq] == -6) && (theBoard.who2move == -1) ) {
			numMoves = bKingAttacks( theBoard, attackedSquares, 0, sq );
        	for (n=0; n<numMoves; n++) {
            	if (attackedSquares[n] == querySquare) {
				attacked = true; 
				return attacked;
				}
			}
		}
        
		// end of for(sq)
		}

	// if we made it this far, we have not been attacked! :-D
	return attacked;
    
}


bool isSideToMoveInCheck( boardRecord &theBoard )
{
    int myKingSq;
    bool inCheck = false;

    for (myKingSq = 0; myKingSq < 64; myKingSq++) {
        if ( theBoard.square[myKingSq] * theBoard.who2move == 6 ) {
            //cout << "kingSq: " << myKingSq << endl;
            theBoard.who2move = -theBoard.who2move;
            inCheck = isAttacked( myKingSq, theBoard );
            theBoard.who2move = -theBoard.who2move;
            }
        }
    
    // if no king, we cant be in check (allows debugging minus king values)
    return inCheck;
    
}


bool isLegalPosition( boardRecord &theBoard )
{
    int oppKingSq;
    bool legal = true;
    
    // false means that the last move was illegal. 
    // i.e. the side to move can capture opposing K
    
    for (oppKingSq=0; oppKingSq < 64; oppKingSq++) {
        if ( theBoard.square[oppKingSq] * theBoard.who2move == -6 ) {
            legal = ( isAttacked(oppKingSq, theBoard ) == false );
            }
        }

    return legal;
}


int quiescenceSearch( boardRecord &board, int alphaScore, int betaScore, int depth )
{
	int numMoves, moveIndex, moveScore, patScore;
	struct boardRecord &testBoard = board;
	struct moveRecord theMove;
	struct moveRecord moves[_maxMoves];
	
	patScore = staticEval( board );
	
	if ( depth < _minQSearchDepth ) {
		alphaScore = patScore;
		return alphaScore;
		}
		
	if ( patScore > alphaScore ) {
		alphaScore = patScore;
		// beta cutoff
		if ( alphaScore >= betaScore ) {
			return alphaScore;
			}
		}
		
	numMoves = generateCaptureMoves( board, moves );
	if ( numMoves==0 ) {
		return patScore;
		}
	
    sortMoves( moves, numMoves );


	// find: this next two lines just a dummy test -> REMOVE IT <- for thinsg to work right.
	gqNodes++;
	return patScore;

	
	for (moveIndex = 0; moveIndex < numMoves; moveIndex++ ) {
        testBoard = board;
		theMove = moves[moveIndex];
		makeMove( testBoard, theMove );
		
		if ( isLegalPosition(testBoard) ) {
			//gqNodes++;
			moveScore = -quiescenceSearch( testBoard, -betaScore, -alphaScore, depth-1 );
			
			if ( moveScore > alphaScore ) {
				alphaScore = moveScore;

				// beta cutoff
				if ( alphaScore >= betaScore) {
					return alphaScore;
					}
				
				}
			}
		}
	
	return alphaScore;
}


int negaSearch( boardRecord &board, int alphaScore, int betaScore, int depth, int ply)
{
    int numRawMoves, moveIndex;
    int moveScore;
    int numLegal = 0;
    struct moveRecord moves[_maxMoves];
    struct moveRecord theMove;
    struct boardRecord testBoard;
    
    // check for timed abortSearch
    // hash lookup
    // if depth<=0 then quiescenceSearch
    
    if (depth <= 0) {
        alphaScore = staticEval( board );
		//alphaScore = quiescenceSearch( board, alphaScore, betaScore, depth-1 );
        return alphaScore;
        }
    
    numRawMoves = generateRawMoves( board, moves, 0 );
    
    sortMoves( moves, numRawMoves );
    
    for (moveIndex=0; moveIndex<numRawMoves; moveIndex++) {
        testBoard = board;
        theMove = moves[moveIndex];
        makeMove( testBoard, theMove );
		
        if ( isLegalPosition(testBoard) ) {
			numLegal++;
         	
        	moveScore = -negaSearch( testBoard, -betaScore, -alphaScore, depth-1, ply+1 );
         	
        	if (moveScore > alphaScore) {
        		alphaScore = moveScore;
				theMove.moveScore = moveScore;
				}
         	
         	if (alphaScore >= betaScore) {
             	break;
            	}
            
            if (numLegal==0) {
            	if (isSideToMoveInCheck(board)) {
            		alphaScore = _iAmMateScore + ply;
            		return alphaScore;
            		}
            	else {
            		alphaScore = _stalemateScore;
            		return alphaScore;
            		}
				}
            
       		}
   		}
    
	return alphaScore;
}


moveRecord computerSearch( boardRecord &theBoard, int depth )
{
    struct boardRecord testBoard;
    struct moveRecord moves[_maxMoves];
    struct moveRecord theMove;
    int alphaScore, betaScore;
    int numMoves, moveIndex, moveScore, highMove;

    highMove = 0;
    alphaScore = -_infinity;
    betaScore = _infinity;

    theMove.fromSquare = _noSuchSquare;
    theMove.toSquare = _noSuchSquare;
    theMove.moveScore = 0;
	theMove.capturedPiece = 0;

    // first see if we are in check (used for kingMove generation only)
    gInCheck = false;
    gInCheck = isSideToMoveInCheck( theBoard );
	gMovesMade = 0; gqNodes = 0;
    
	// generate the ROOT Moves
    numMoves = generateLegalMoves( theBoard, moves );
    
    if (numMoves > 0) {
	
		// captures first
	    sortMoves( moves, numMoves );
        
	    for (moveIndex=0; moveIndex < numMoves; moveIndex++) {
    	    testBoard = theBoard;
    	    theMove = moves[moveIndex];
    	    makeMove( testBoard, theMove );
    	    
        	moveScore = -negaSearch( testBoard, -betaScore, -alphaScore, depth, 1);
        	
        	if ( moveScore > alphaScore ) {
        	    alphaScore = moveScore;
        	    highMove = moveIndex;
        	    moves[moveIndex].moveScore = moveScore;
        	    cout << ".";
        	    }
        
         	if (alphaScore >= betaScore) {
            	break;
            	}
			}

    	// create the move entry
		theMove.fromSquare = moves[highMove].fromSquare;
    	theMove.toSquare = moves[highMove].toSquare;
    	theMove.moveScore = moves[highMove].moveScore;
    	theMove.capturedPiece = moves[highMove].capturedPiece;
    	gInCheck = false;
    	}

	// display info
    cout << endl << "moves: " << gMovesMade << " qui: " << gqNodes << " | score: " << alphaScore << endl;
    return theMove;
}


int perft( boardRecord &inBoard, int depth )
{
	int nodes = 0;
	int numLegal, j;
	struct moveRecord moves[_maxMoves];
	struct boardRecord board;
    
	numLegal = generateLegalMoves( inBoard, moves );

	if (depth == 1 )
		nodes = numLegal;
    else
        for (j = 0; j < numLegal; j++) {
			board = inBoard;
			makeMove( board, moves[j] );
			nodes += perft( board, depth -1 );
			}
    
    return nodes;    
}


/*
 PERFT Correct results from NEW: 
 1  20
 2  400
 3  8902
 4  197281
 5  4865609
 6  119060324
 7  3195901860
 8  84998978956
 9  2439530234167
 10 69352859712417
 11 2097651003696806
 12 62854969236701747
 */


