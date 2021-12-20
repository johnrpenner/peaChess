// peaBrain 3.4
// Attack Move Generator
// 
// Copyright 2012 by John Roland Penner <johnrolandpenner-at-gmail-dot-com>
// Created: July 4, 2012 (Toronto Island)
// Updated: July 30, 2012


int wPawnAttacks( boardRecord theBoard, int attackedSquares[], int numMoves, int querySquare )
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
			attackedSquares[moveIndex] = testSquare;
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
			attackedSquares[moveIndex] = testSquare;
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
			attackedSquares[moveIndex] = querySquare + 7; //legal because Y=6 and enPasSq=onBoard
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
			attackedSquares[moveIndex] = querySquare + 9; //legal because Y=5 and enPasSq=onBoard
			pieceMoves++;
			}
		}
    
	return pieceMoves;
}


int bPawnAttacks( boardRecord theBoard, int attackedSquares[], int numMoves, int querySquare )
{
    int moveIndex, pieceMoves, fromY;
	int testMask, newMask, testSquare;

    pieceMoves = 0;
	fromY = sq2Y(querySquare);

	// black pawn SW (captures)
	testMask = sq2Mask[querySquare];
	newMask = testMask + bPawnMask[0];
	testSquare = querySquare + bPawnVect[0];
	
	if (gMaskBoard[newMask] == 1) {
		if (theBoard.square[testSquare] > 0) {
			moveIndex = numMoves + pieceMoves;
			attackedSquares[moveIndex] = testSquare;
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
			attackedSquares[moveIndex] = testSquare;
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
			attackedSquares[moveIndex] = querySquare - 7; //legal cause Y=6 and enPasSq=onBoard
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
			attackedSquares[moveIndex] = querySquare - 9; //legal cause Y=5 and enPasSq=onBoard
			pieceMoves++;
			}
		}

	return pieceMoves;
}


int bishopAttacks( boardRecord theBoard, int attackedSquares[], int numMoves, int querySquare, int pieceColour )
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
            
            // bishop capture (terminal end of vector)
            if ( (-(pieceHit < 2)) & (-((theBoard.square[testSquare] * pieceColour) < 0)) ) {
				pieceHit++;
                moveIndex = numMoves + pieceMoves;
				attackedSquares[moveIndex] = testSquare;
                pieceMoves++;
				}
            
			testMask = sq2Mask[testSquare]; 
            newMask = testMask + gBishopMask[vectorCount];
            testSquare = testSquare + gBishopVect[vectorCount];
            
        	} while ( !( (-(pieceHit == 2)) | (-(gMaskBoard[newMask] == - 1)) ) );
		}
	return pieceMoves;
}


int knightAttacks( boardRecord theBoard, int attackedSquares[], int numMoves, int querySquare, int pieceColour )
{
    int moveIndex, pieceMoves;
    int testMask, newMask, testSquare, vectorCount;

    pieceMoves = 0;

    for (vectorCount=0; vectorCount<8; vectorCount++) {
        testMask = sq2Mask[querySquare]; 
        newMask = testMask + gKnightMask[vectorCount];
        testSquare = querySquare + gKnightVect[vectorCount];
        
        if ( gMaskBoard[newMask] == 1 ) {
			// using <0 generates only captures
            if ( ( theBoard.square[testSquare] * pieceColour ) < 0 ) {
                moveIndex = numMoves + pieceMoves;
				attackedSquares[moveIndex] = testSquare;
                pieceMoves++;
            	}
        	}
    	}
	return pieceMoves;
}


int rookAttacks( boardRecord theBoard, int attackedSquares[], int numMoves, int querySquare, int pieceColour )
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
            
            // rook capture (terminal end of vector)
            if ( (-(pieceHit < 2)) & (-((theBoard.square[testSquare] * pieceColour) < 0)) ) {
                pieceHit++;
                moveIndex = numMoves + pieceMoves;
				attackedSquares[moveIndex] = testSquare;
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
int queenAttacks( boardRecord theBoard, int attackedSquares[], int numMoves, int querySquare, int pieceColour )
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
            
            // queen capture (terminal end of vector)
            if ( (-(pieceHit < 2)) & (-((theBoard.square[testSquare] * pieceColour) < 0)) ) {
                pieceHit++;
                moveIndex = numMoves + pieceMoves;
				attackedSquares[moveIndex] = testSquare;
                pieceMoves++;
				}
            
            testMask = sq2Mask[testSquare]; 
            newMask = testMask + gQueenMask[vectorCount];
            testSquare = testSquare + gQueenVect[vectorCount];
                        
        	} while ( !( (-(pieceHit == 2)) | (-(gMaskBoard[newMask] == - 1)) ) );
    	}
    return pieceMoves;
}


int wKingAttacks( boardRecord theBoard, int attackedSquares[], int numMoves, int querySquare )
{
    int moveIndex, pieceMoves;
    int testMask, newMask, testSquare, vectorCount;
    bool sqAttacked1, sqAttacked2, sqAttacked3;
    int n, kingSq, holder[8];
    bool wKside, wQside;
    
    pieceMoves = 0;
    
    for (vectorCount=0; vectorCount<8; vectorCount++) {
        testMask = sq2Mask[querySquare]; 
        newMask = testMask + gKingMask[vectorCount];
        testSquare = querySquare + gKingVect[vectorCount];
        
        if ( gMaskBoard[newMask] == 1 ) {
			// using <0 generates only captures
            if ( theBoard.square[testSquare] < 0 ) {
                moveIndex = numMoves + pieceMoves;
				attackedSquares[moveIndex] = testSquare;
                pieceMoves++;
                }
            }
        }

    return pieceMoves;
}


int bKingAttacks( boardRecord theBoard, int attackedSquares[], int numMoves, int querySquare )
{
    int moveIndex, pieceMoves;
    int testMask, newMask, testSquare, vectorCount;
    bool sqAttacked1, sqAttacked2, sqAttacked3;
    int n, kingSq, holder[8];
    bool bKside, bQside;
    
    pieceMoves = 0;
    
    for (vectorCount=0; vectorCount<8; vectorCount++) {
        testMask = sq2Mask[querySquare]; 
        newMask = testMask + gKingMask[vectorCount];
        testSquare = querySquare + gKingVect[vectorCount];
        
        if ( gMaskBoard[newMask] == 1 ) {
			// using >0 generates only bKing captures
            if ( theBoard.square[testSquare] > 0 ) {
                moveIndex = numMoves + pieceMoves;
				attackedSquares[moveIndex] = testSquare;
                pieceMoves++;
                }
            }
        }
    
    return pieceMoves;
}

