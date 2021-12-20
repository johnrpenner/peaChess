// peaBrain 3.4
// Move Generator
// 
// Copyright 2012 by John Roland Penner <johnrolandpenner-at-gmail-dot-com>
// Created: April 19, 2012 (Toronto Island)
// Updated: July 30, 2012


int sq2X( int index ) 
{
    return index % 8; 
}  

int sq2Y( int index ) 
{
    int y; 
    if (index < 0) {y = -1;}
    else { y = index/8;}
    return y; 
}  


int wPawnMoves( boardRecord theBoard, moveRecord moves[], int numMoves, int querySquare )
{
    int moveIndex, pieceMoves, fromY;
	int testMask, newMask, testSquare;

    pieceMoves = 0;
	fromY = sq2Y(querySquare);

	// pawn NW (captures)
	testMask = sq2Mask[querySquare];
	newMask = testMask + wPawnMask[0];
	testSquare = querySquare + wPawnVect[0];
	
	if (gMaskBoard[newMask] == 1) {
		if (theBoard.square[testSquare] < 0) {
			moveIndex = numMoves + pieceMoves;
			moves[moveIndex].fromSquare = querySquare;
			moves[moveIndex].toSquare = testSquare;
			moves[moveIndex].capturedPiece = theBoard.square[testSquare];
			moves[moveIndex].moveScore = 0;
			pieceMoves++;			
			}
		}

	// pawn NE (captures)
	testMask = sq2Mask[querySquare];
	newMask = testMask + wPawnMask[1];
	testSquare = querySquare + wPawnVect[1];
	
	if (gMaskBoard[newMask] == 1) {
		if (theBoard.square[testSquare] < 0) {
			moveIndex = numMoves + pieceMoves;
			moves[moveIndex].fromSquare = querySquare;
			moves[moveIndex].toSquare = testSquare;
			moves[moveIndex].capturedPiece = theBoard.square[testSquare];
			moves[moveIndex].moveScore = 0;
			pieceMoves++;			
			}
		}

    //pawn forward 1x (space)
	testMask = sq2Mask[querySquare];
	newMask = testMask + wPawnMask[2];
	testSquare = querySquare + wPawnVect[2];
	
	if (gMaskBoard[newMask]==1) {
		if (theBoard.square[testSquare]==0) {
			moveIndex = numMoves + pieceMoves;
			moves[moveIndex].fromSquare = querySquare;
			moves[moveIndex].toSquare = testSquare;
			moves[moveIndex].capturedPiece = 0;
			moves[moveIndex].moveScore = 0;
			pieceMoves++;
			}
		}
	
    //pawn forward 2x (space)
	testMask = sq2Mask[querySquare];
	newMask = testMask + wPawnMask[3];
	testSquare = querySquare + wPawnVect[3];
	
	if (gMaskBoard[newMask]==1) {
		if ( (querySquare > 7) && (querySquare < 16) && (theBoard.square[testSquare]==0) && (theBoard.square[testSquare-8]==0) ) {
			moveIndex = numMoves + pieceMoves;
			moves[moveIndex].fromSquare = querySquare;
			moves[moveIndex].toSquare = testSquare;
			moves[moveIndex].capturedPiece = 0;
			moves[moveIndex].moveScore = 0;
			pieceMoves++;
			}
		}

	// pawn enPassant-West (captures)
	testMask = sq2Mask[querySquare];
	newMask = testMask + wPawnMask[4];
	testSquare = querySquare + wPawnVect[4];
	
	if (gMaskBoard[newMask] == 1) {
		if ( (fromY = 4) && (testSquare == theBoard.enPassantSq) ) {
			moveIndex = numMoves + pieceMoves;
			moves[moveIndex].fromSquare = querySquare;
			moves[moveIndex].toSquare = querySquare + 7; //legal because Y=6 and enPasSq=onBoard
			moves[moveIndex].capturedPiece = theBoard.square[testSquare];
			moves[moveIndex].moveScore = 0;
			pieceMoves++;
			}
		}
		
	// pawn enPassant-East (captures)
	testMask = sq2Mask[querySquare];
	newMask = testMask + wPawnMask[5];
	testSquare = querySquare + wPawnVect[5];
	
	if (gMaskBoard[newMask] == 1) {
		if ( (fromY = 4) && (testSquare == theBoard.enPassantSq) ) {
			moveIndex = numMoves + pieceMoves;
			moves[moveIndex].fromSquare = querySquare;
			moves[moveIndex].toSquare = querySquare + 9; //legal because Y=5 and enPasSq=onBoard
			moves[moveIndex].capturedPiece = theBoard.square[testSquare];
			moves[moveIndex].moveScore = 0;
			pieceMoves++;
			}
		}
    
	return pieceMoves;
}


int bPawnMoves( boardRecord theBoard, moveRecord moves[], int numMoves, int querySquare )
{
    int moveIndex, pieceMoves, fromY;
	int testMask, newMask, testSquare;

    pieceMoves = 0;
	fromY = sq2Y(querySquare);

    // black pawn forward 1x (space)
	testMask = sq2Mask[querySquare];
	newMask = testMask + bPawnMask[2];
	testSquare = querySquare + bPawnVect[2];
	
	if (gMaskBoard[newMask]==1) {
		if (theBoard.square[testSquare]==0) {
			moveIndex = numMoves + pieceMoves;
			moves[moveIndex].fromSquare = querySquare;
			moves[moveIndex].toSquare = testSquare;
			moves[moveIndex].capturedPiece = 0;
			moves[moveIndex].moveScore = 0;
			pieceMoves++;
			}
		}
	
    // black pawn forward 2x (space)
	testMask = sq2Mask[querySquare];
	newMask = testMask + bPawnMask[3];
	testSquare = querySquare + bPawnVect[3];
	
	if (gMaskBoard[newMask]==1) {
		if ( (querySquare > 47) && (querySquare < 56) && (theBoard.square[testSquare]==0) && (theBoard.square[testSquare+8]==0) ) {
			moveIndex = numMoves + pieceMoves;
			moves[moveIndex].fromSquare = querySquare;
			moves[moveIndex].toSquare = testSquare;
			moves[moveIndex].capturedPiece = 0;
			moves[moveIndex].moveScore = 0;
			pieceMoves++;
			}
		}

	// black pawn SW (captures)
	testMask = sq2Mask[querySquare];
	newMask = testMask + bPawnMask[0];
	testSquare = querySquare + bPawnVect[0];
	
	if (gMaskBoard[newMask] == 1) {
		if (theBoard.square[testSquare] > 0) {
			moveIndex = numMoves + pieceMoves;
			moves[moveIndex].fromSquare = querySquare;
			moves[moveIndex].toSquare = testSquare;
			moves[moveIndex].capturedPiece = theBoard.square[testSquare];
			moves[moveIndex].moveScore = 0;
			pieceMoves++;
			}
		}

	// black pawn SE (captures)
	testMask = sq2Mask[querySquare];
	newMask = testMask + bPawnMask[1];
	testSquare = querySquare + bPawnVect[1];
	
	if (gMaskBoard[newMask] == 1) {
		if (theBoard.square[testSquare] > 0) {
			moveIndex = numMoves + pieceMoves;
			moves[moveIndex].fromSquare = querySquare;
			moves[moveIndex].toSquare = testSquare;
			moves[moveIndex].capturedPiece = theBoard.square[testSquare];
			moves[moveIndex].moveScore = 0;
			pieceMoves++;
			}
		}

	// black pawn enPassant-West (captures)
	testMask = sq2Mask[querySquare];
	newMask = testMask + bPawnMask[4];
	testSquare = querySquare + bPawnVect[4];
	
	if (gMaskBoard[newMask] == 1) {
		if ( (fromY = 3) && (testSquare == theBoard.enPassantSq) ) {
			moveIndex = numMoves + pieceMoves;
			moves[moveIndex].fromSquare = querySquare;
			moves[moveIndex].toSquare = querySquare - 7; //legal cause Y=6 and enPasSq=onBoard
			moves[moveIndex].capturedPiece = theBoard.square[testSquare];
			moves[moveIndex].moveScore = 0;
			pieceMoves++;
			}
		}
		
	// black pawn enPassant-East (captures)
	testMask = sq2Mask[querySquare];
	newMask = testMask + bPawnMask[5];
	testSquare = querySquare + bPawnVect[5];
	
	if (gMaskBoard[newMask] == 1) {
		if ( (fromY = 3) && (testSquare == theBoard.enPassantSq) ) {
			moveIndex = numMoves + pieceMoves;
			moves[moveIndex].fromSquare = querySquare;
			moves[moveIndex].toSquare = querySquare - 9; //legal cause Y=5 and enPasSq=onBoard
			moves[moveIndex].capturedPiece = theBoard.square[testSquare];
			moves[moveIndex].moveScore = 0;
			pieceMoves++;
			}
		}
    
	return pieceMoves;
}


int bishopMoves( boardRecord theBoard, moveRecord moves[], int numMoves, int querySquare, int pieceColour )
{
    int testSquare, moveIndex;
    int pieceMoves, pieceHit;
    int vectorCount, testMask, newMask;
    
    pieceMoves = 0;
    
    for (vectorCount=0; vectorCount<=3; vectorCount++) {
		pieceHit = 0;
		testSquare = querySquare;        
        do {            
            // hit ourselves first
            if ( (-(pieceHit < 2)) & (-((theBoard.square[testSquare] * pieceColour) > 0)) ) {
                pieceHit++;
				}
            
            // bishop space
            if ( (-(pieceHit < 2)) & (-(theBoard.square[testSquare] == 0)) ) {
				moveIndex = numMoves + pieceMoves;
                moves[moveIndex].fromSquare = querySquare;
                moves[moveIndex].toSquare = testSquare;
                moves[moveIndex].moveScore = 0;
				moves[moveIndex].capturedPiece = 0;
                pieceMoves++;
				}
            
            // bishop capture (terminal end of vector)
            if ( (-(pieceHit < 2)) & (-((theBoard.square[testSquare] * pieceColour) < 0)) ) {
				pieceHit++;
                moveIndex = numMoves + pieceMoves;
                moves[moveIndex].fromSquare = querySquare;
                moves[moveIndex].toSquare = testSquare;
                moves[moveIndex].moveScore = 0;
				moves[moveIndex].capturedPiece = theBoard.square[testSquare];
                pieceMoves++;
				}
            
			testMask = sq2Mask[testSquare]; 
            newMask = testMask + gBishopMask[vectorCount];
            testSquare = testSquare + gBishopVect[vectorCount];
            
        	} while ( !( (-(pieceHit == 2)) | (-(gMaskBoard[newMask] == - 1)) ) );
		}
	return pieceMoves;
}


int knightMoves( boardRecord theBoard, moveRecord moves[], int numMoves, int querySquare, int pieceColour )
{
    int moveIndex, pieceMoves;
    int testMask, newMask, testSquare, vectorCount;

    pieceMoves = 0;

    for (vectorCount=0; vectorCount<8; vectorCount++) {
        testMask = sq2Mask[querySquare]; 
        newMask = testMask + gKnightMask[vectorCount];
        testSquare = querySquare + gKnightVect[vectorCount];
        
        if ( gMaskBoard[newMask] == 1 ) {
		// using <1 generates both spcase and captures
            if ( ( theBoard.square[testSquare] * pieceColour ) < 1 ) {
                moveIndex = numMoves + pieceMoves;
                moves[moveIndex].fromSquare = querySquare;
                moves[moveIndex].toSquare = testSquare;
                moves[moveIndex].moveScore = theBoard.square[testSquare];
				moves[moveIndex].capturedPiece = theBoard.square[testSquare];
                pieceMoves++;
            	}
        	}
    	}
	return pieceMoves;
}


int rookMoves( boardRecord theBoard, moveRecord moves[], int numMoves, int querySquare, int pieceColour )
{
    int testSquare, moveIndex;
    int pieceMoves, pieceHit;
    int vectorCount, testMask, newMask;
    
    pieceMoves = 0;
    
    for (vectorCount=0; vectorCount<=3; vectorCount++) {
        pieceHit = 0;
        testSquare = querySquare; 
        do {
            // hit ourselves first
            if ( (-(pieceHit < 2)) & (-((theBoard.square[testSquare] * pieceColour) > 0)) ) {
                pieceHit++;
				}
            
            // rook space
            if ( (-(pieceHit < 2)) & (-(theBoard.square[testSquare] == 0)) ) {
                moveIndex = numMoves + pieceMoves;
                moves[moveIndex].fromSquare = querySquare;
                moves[moveIndex].toSquare = testSquare;
                moves[moveIndex].moveScore = 0;
				moves[moveIndex].capturedPiece = 0;
                pieceMoves++;
				}
            
            // rook capture (terminal end of vector)
            if ( (-(pieceHit < 2)) & (-((theBoard.square[testSquare] * pieceColour) < 0)) ) {
                pieceHit++;
                moveIndex = numMoves + pieceMoves;
                moves[moveIndex].fromSquare = querySquare;
                moves[moveIndex].toSquare = testSquare;
                moves[moveIndex].moveScore = 0;
				moves[moveIndex].capturedPiece = theBoard.square[testSquare];
                pieceMoves++;
				}
            
            testMask = sq2Mask[testSquare]; 
            newMask = testMask + gRookMask[vectorCount];
            testSquare = testSquare + gRookVect[vectorCount];
			
			} while ( !( (-(pieceHit == 2)) | (-(gMaskBoard[newMask] == - 1)) ) );
		}
	return pieceMoves;
}


// find: to be depreciated (not yet!) in favour of compound queen {rook + bishop} move generation
int queenMoves( boardRecord theBoard, moveRecord moves[], int numMoves, int querySquare, int pieceColour )
{
    int testSquare, moveIndex;
    int pieceMoves, pieceHit;
    int vectorCount, testMask, newMask;
    
    pieceMoves = 0;
    
    for (vectorCount=0; vectorCount<=7; vectorCount++) {
        pieceHit = 0;
        testSquare = querySquare; 
        do {
            
            // hit ourselves first
            if ( (-(pieceHit < 2)) & (-((theBoard.square[testSquare] * pieceColour) > 0)) ) {
				pieceHit++;
				}
            
            // queen space
            if ( (-(pieceHit < 2)) & (-(theBoard.square[testSquare] == 0)) ) {
                moveIndex = numMoves + pieceMoves;
                moves[moveIndex].fromSquare = querySquare;
                moves[moveIndex].toSquare = testSquare;
                moves[moveIndex].moveScore = 0;
				moves[moveIndex].capturedPiece = theBoard.square[testSquare];
                pieceMoves++;
				}
            
            // queen capture (terminal end of vector)
            if ( (-(pieceHit < 2)) & (-((theBoard.square[testSquare] * pieceColour) < 0)) ) {
                pieceHit++;
                moveIndex = numMoves + pieceMoves;
                moves[moveIndex].fromSquare = querySquare;
                moves[moveIndex].toSquare = testSquare;
                moves[moveIndex].moveScore = 0;
				moves[moveIndex].capturedPiece = theBoard.square[testSquare];
                pieceMoves++;
				}
            
            testMask = sq2Mask[testSquare]; 
            newMask = testMask + gQueenMask[vectorCount];
            testSquare = testSquare + gQueenVect[vectorCount];
                        
        	} while ( !( (-(pieceHit == 2)) | (-(gMaskBoard[newMask] == - 1)) ) );
    	}
    return pieceMoves;
}


int wKingMoves( boardRecord theBoard, moveRecord moves[], int numMoves, int querySquare )
{
    int moveIndex, pieceMoves;
    int testMask, newMask, testSquare, vectorCount;
    bool sqAttacked1, sqAttacked2, sqAttacked3;
    int n, kingSq, holder[8];
    bool wKside, wQside;
    
    pieceMoves = 0;
    
	// generate both captures (-1 is <1); and spaces are (0 is <1)
    for (vectorCount=0; vectorCount<8; vectorCount++) {
        testMask = sq2Mask[querySquare]; 
        newMask = testMask + gKingMask[vectorCount];
        testSquare = querySquare + gKingVect[vectorCount];
        
        if ( gMaskBoard[newMask] == 1 ) {
            if ( theBoard.square[testSquare] < 1 ) {
                moveIndex = numMoves + pieceMoves;
                moves[moveIndex].fromSquare = querySquare;
                moves[moveIndex].toSquare = testSquare;
				moves[moveIndex].moveScore = 0;
				moves[moveIndex].capturedPiece = theBoard.square[testSquare];
                pieceMoves++;
                }
            }
        }

    // Castling only if not in Check
    if (!gInCheck) {
        
    // king wCastleKside (classic)
    if ( (querySquare == 4) && (theBoard.square[4]==6) && (theBoard.square[5]==0) && (theBoard.square[6]==0) && (theBoard.square[7]==4) && (theBoard.wCastleKside==true) ) {

        // setup dummy pieces for testSquares (and we could not get here if they were not empty!)
        theBoard.square[5] = 1;
        theBoard.square[6] = 1;
        theBoard.who2move = -theBoard.who2move;
        
        // cant castle through check!!
        sqAttacked1 = isAttacked( 5, theBoard );
        sqAttacked2 = isAttacked( 6, theBoard );
        sqAttacked3 = false;
        
        if ( (sqAttacked1==false) && (sqAttacked2==false) && (gInCheck==false) ) {
            moveIndex = numMoves + pieceMoves;
            moves[moveIndex].fromSquare = querySquare;
            moves[moveIndex].toSquare = 6;
            //moves.capturePiece[moveIndex] = 0;
            moves[moveIndex].moveScore = 0;
			moves[moveIndex].capturedPiece = 0;
            pieceMoves++;
            }
        
        theBoard.square[5] = 0;
        theBoard.square[6] = 0;
        theBoard.who2move = -theBoard.who2move;
        }
    
    // king wCastleQside (classic)
    if ( (querySquare == 4) && (theBoard.square[4]==6) && (theBoard.square[3]==0) && (theBoard.square[2]==0) && (theBoard.square[1]==0) && (theBoard.square[0]==4) && (theBoard.wCastleQside==true) ) {
        
        // setup dummy pieces for testSquares (and we could not get here if they were not empty!)
        theBoard.square[1] = 1;
        theBoard.square[2] = 1;
        theBoard.square[3] = 1;
        theBoard.who2move = -theBoard.who2move;
        
        // cant castle through check!!
        sqAttacked1 = isAttacked( 1, theBoard );
        sqAttacked2 = isAttacked( 2, theBoard );
        sqAttacked3 = isAttacked( 3, theBoard );
        
        if ( (sqAttacked1==false) && (sqAttacked2==false) && (sqAttacked3==false) && (gInCheck==false) ) {
            moveIndex = numMoves + pieceMoves;
            moves[moveIndex].fromSquare = querySquare;
            moves[moveIndex].toSquare = 2;
            //moves.capturePiece[moveIndex] = 0;
            moves[moveIndex].moveScore = 0;
			moves[moveIndex].capturedPiece = 0;
            pieceMoves++;
            }
        
        theBoard.square[1] = 0;
        theBoard.square[2] = 0;
        theBoard.square[3] = 0;
        theBoard.who2move = -theBoard.who2move;
        }
        
    }
    return pieceMoves;
}


int bKingMoves( boardRecord theBoard, moveRecord moves[], int numMoves, int querySquare )
{
    int moveIndex, pieceMoves;
    int testMask, newMask, testSquare, vectorCount;
    bool sqAttacked1, sqAttacked2, sqAttacked3;
    int n, kingSq, holder[8];
    bool bKside, bQside;
    
    pieceMoves = 0;

	// generate both captures (-1 is <1); and spaces are (0 is <1)    
    for (vectorCount=0; vectorCount<8; vectorCount++) {
        testMask = sq2Mask[querySquare]; 
        newMask = testMask + gKingMask[vectorCount];
        testSquare = querySquare + gKingVect[vectorCount];
        
        if ( gMaskBoard[newMask] == 1 ) {
            if ( theBoard.square[testSquare] > -1 ) {
                moveIndex = numMoves + pieceMoves;
                moves[moveIndex].fromSquare = querySquare;
                moves[moveIndex].toSquare = testSquare;
				moves[moveIndex].moveScore = 0;
				moves[moveIndex].capturedPiece = theBoard.square[testSquare];
                pieceMoves++;
                }
            }
        }

    // Castling only if not in Check
    if (!gInCheck) {

    // black king bCastleKside (classic)
    if ( (querySquare == 60) && (theBoard.square[60]==-6) && (theBoard.square[61]==0) && (theBoard.square[62]==0) && (theBoard.square[63]==-4) && (theBoard.bCastleKside==true) ) {
        
        // setup dummy pieces for testSquares (and we could not get here if they were not empty!)
        theBoard.square[61] = -1;
        theBoard.square[62] = -1;
        theBoard.who2move = -theBoard.who2move;
        
        // cant castle through check!!
        sqAttacked1 = isAttacked( 61, theBoard );
        sqAttacked2 = isAttacked( 62, theBoard );
        sqAttacked3 = false;
        
        if ( (sqAttacked1==false) && (sqAttacked2==false) && (gInCheck==false) ) {
            moveIndex = numMoves + pieceMoves;
            moves[moveIndex].fromSquare = querySquare;
            moves[moveIndex].toSquare = 62;
            //moves.capturePiece[moveIndex] = 0;
            moves[moveIndex].moveScore = 0;
			moves[moveIndex].capturedPiece = 0;
            pieceMoves++;
            }
        
        theBoard.square[61] = 0;
        theBoard.square[62] = 0;
        theBoard.who2move = -theBoard.who2move;
        }
    
    // black king bCastleQside (classic)
    if ( (querySquare == 60) && (theBoard.square[60]==-6) && (theBoard.square[59]==0) && (theBoard.square[58]==0) && (theBoard.square[57]==0) && (theBoard.square[56]==-4) && (theBoard.bCastleQside==true) ) {
        
        // setup dummy pieces for testSquares (and we could not get here if they were not empty!)
        theBoard.square[57] = 1;
        theBoard.square[58] = 1;
        theBoard.square[59] = 1;
        theBoard.who2move = -theBoard.who2move;
        
        // cant castle through check!!
        sqAttacked1 = isAttacked( 57, theBoard );
        sqAttacked2 = isAttacked( 58, theBoard );
        sqAttacked3 = isAttacked( 59, theBoard );
        
        if ( (sqAttacked1==false) && (sqAttacked2==false) && (sqAttacked3==false) && (gInCheck==false) ) {
            moveIndex = numMoves + pieceMoves;
            moves[moveIndex].fromSquare = querySquare;
            moves[moveIndex].toSquare = 58;
            moves[moveIndex].moveScore = 0;
            moves[moveIndex].capturedPiece = 0;
            pieceMoves++;
            }
        
        theBoard.square[57] = 0;
        theBoard.square[58] = 0;
        theBoard.square[59] = 0;
        theBoard.who2move = -theBoard.who2move;
        }
    }
    
    return pieceMoves;
}


// adjunct to FN generateRawMoves()
int pieceTree( boardRecord theBoard, moveRecord moves[], int numMoves, int querySquare )
{
    int pieceMoves = 0;
    int pieceType, pieceColour;

    pieceType = theBoard.square[querySquare];
    if (pieceType > 0) pieceColour = 1; else pieceColour = -1;
    
    switch ( pieceType ) {
        case 1:
            pieceMoves = wPawnMoves( theBoard, moves, numMoves, querySquare );
            return pieceMoves;
            
        case -1:
            pieceMoves = bPawnMoves( theBoard, moves, numMoves, querySquare );
            return pieceMoves;

        case 2:
            pieceMoves = bishopMoves( theBoard, moves, numMoves, querySquare, pieceColour );
            return pieceMoves;
            
        case -2:
            pieceMoves = bishopMoves( theBoard, moves, numMoves, querySquare, pieceColour );
            return pieceMoves;
            
        case 3:
            pieceMoves = knightMoves( theBoard, moves, numMoves, querySquare, pieceColour );
            return pieceMoves;
            
        case -3:
            pieceMoves = knightMoves( theBoard, moves, numMoves, querySquare, pieceColour );
            return pieceMoves;
            
        case 4:
            pieceMoves = rookMoves( theBoard, moves, numMoves, querySquare, pieceColour );
            return pieceMoves;
            
        case -4:
            pieceMoves = rookMoves( theBoard, moves, numMoves, querySquare, pieceColour );
            return pieceMoves;

		/*
        case 5:
            // gree's compound queen {rook, bishop} allows removal of queenMoves()
            pieceMoves = bishopMoves( theBoard, moves, numMoves, querySquare, pieceColour ); 
            numMoves += pieceMoves; 
            pieceMoves = rookMoves( theBoard, moves, numMoves, querySquare, pieceColour ); 
            return pieceMoves;
            
        case -5:
            pieceMoves = bishopMoves( theBoard, moves, numMoves, querySquare, pieceColour ); 
            numMoves += pieceMoves; 
            pieceMoves = rookMoves( theBoard, moves, numMoves, querySquare, pieceColour ); 
            return pieceMoves;
			*/
			
        case 5:
            // depreciated (not yet!!) non-compounded queen moves depends on queenMoves()
            pieceMoves = queenMoves( theBoard, moves, numMoves, querySquare, pieceColour ); 
            return pieceMoves;

        case -5:
            // depreciated (not yet!!) non-compounded queen moves depends on queenMoves()
            pieceMoves = queenMoves( theBoard, moves, numMoves, querySquare, pieceColour ); 
            return pieceMoves;
 
        case 6:
            pieceMoves = wKingMoves( theBoard, moves, numMoves, querySquare );
            return pieceMoves;
            
        case -6:
            pieceMoves = bKingMoves( theBoard, moves, numMoves, querySquare );
            return pieceMoves;

    }
    
    return pieceMoves;
}


// adjunct to FN generateCaptureMoves()
int attacks2moves( int sq, boardRecord &theBoard, int numCaptureMoves, int attackedSquares[], int numMoves, moveRecord moves[] )
{
int j;

for (j=0; j<numMoves; j++) {
	moves[numCaptureMoves].fromSquare = 	sq;
	moves[numCaptureMoves].toSquare = 		attackedSquares[j];
	moves[numCaptureMoves].capturedPiece = 	theBoard.square[ attackedSquares[j] ];
	moves[numCaptureMoves].moveScore =		0;
	numCaptureMoves++;
	}

return numCaptureMoves;
}


int generateRawMoves( boardRecord &board, moveRecord moves[], int numMoves )
{
    int querySquare;
    int pieceMoves;

    for (querySquare=0 ;querySquare<64; querySquare++) {
        pieceMoves = 0;

        // generate white moves
        if ( board.who2move == 1 && board.square[querySquare] > 0 ) {
            pieceMoves = pieceTree( board, moves, numMoves, querySquare );
            numMoves += pieceMoves;
        	}

        // generate black moves
        if ( board.who2move == -1 && board.square[querySquare] < 0 ) {
            pieceMoves = pieceTree( board, moves, numMoves, querySquare);
            numMoves += pieceMoves;
        	}
    	}
	return numMoves;
}


int generateLegalMoves( boardRecord &board, moveRecord moves[] )
{
    int numRawMoves, n, numLegalMoves = 0;
    struct boardRecord testBoard;
    struct moveRecord theMove;
    struct moveRecord rawMoves[_maxMoves];
    
    numRawMoves = generateRawMoves( board, rawMoves, 0 ); 
    
    for (n=0; n<numRawMoves; n++) {
        testBoard = board;
        theMove = rawMoves[n];
        
        makeMove( testBoard, theMove );
        
        if (isLegalPosition( testBoard )) {
            moves[numLegalMoves] = theMove;
            numLegalMoves++;
        	}
     	}
		
    return numLegalMoves;
}


int generateCaptureMoves( boardRecord &theBoard, moveRecord moves[] )
{
	//int attackedSquares[_maxMoves];
	int attackedSquares[10000];
	int numMoves = 0; 
	int numCaptureMoves = 0;
    int querySquare, pieceType, pieceColour;

	for (querySquare=0; querySquare<64; querySquare++) {

		pieceColour = theBoard.who2move;
		pieceType = theBoard.square[querySquare];

		if ( (pieceType==1) && (pieceColour==1) ) {
			numMoves = wPawnAttacks( theBoard, attackedSquares, 0, querySquare );
			numCaptureMoves = attacks2moves( querySquare, theBoard, numCaptureMoves, attackedSquares, numMoves, moves );
			}
            
		if ( (pieceType==-1) && (pieceColour==-1) ) {
            numMoves = bPawnAttacks( theBoard, attackedSquares, 0, querySquare );
			numCaptureMoves = attacks2moves( querySquare, theBoard, numCaptureMoves, attackedSquares, numMoves, moves );
			}

		if ( pieceType * pieceColour == 2 ) {
            numMoves = bishopAttacks( theBoard, attackedSquares, 0, querySquare, pieceColour );
			numCaptureMoves = attacks2moves( querySquare, theBoard, numCaptureMoves, attackedSquares, numMoves, moves );
			}
            
		if ( pieceType * pieceColour == 3 ) {
            numMoves = knightAttacks( theBoard, attackedSquares, 0, querySquare, pieceColour );
			numCaptureMoves = attacks2moves( querySquare, theBoard, numCaptureMoves, attackedSquares, numMoves, moves );
			}
            
		if ( pieceType * pieceColour == 4 ) {
			numMoves = rookAttacks( theBoard, attackedSquares, 0, querySquare, pieceColour );
			numCaptureMoves = attacks2moves( querySquare, theBoard, numCaptureMoves, attackedSquares, numMoves, moves );
			}

		if ( pieceType * pieceColour == 5 ) {
            numMoves = queenAttacks( theBoard, attackedSquares, 0, querySquare, pieceColour );
			numCaptureMoves = attacks2moves( querySquare, theBoard, numCaptureMoves, attackedSquares, numMoves, moves );
			}

		if ( (pieceType==6) && (pieceColour==1) ) {
            numMoves = wKingAttacks( theBoard, attackedSquares, 0, querySquare );
			numCaptureMoves = attacks2moves( querySquare, theBoard, numCaptureMoves, attackedSquares, numMoves, moves );
			}
            
		if ( (pieceType==-6) && (pieceColour==-1) ) {
            numMoves = bKingAttacks( theBoard, attackedSquares, 0, querySquare );
			numCaptureMoves = attacks2moves( querySquare, theBoard, numCaptureMoves, attackedSquares, numMoves, moves );
			}
			
		}
		
	return numCaptureMoves;
}

