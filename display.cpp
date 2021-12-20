// peaBrain 3.4
// Display Module
// 
// Copyright 2012 by John Roland Penner <johnrolandpenner-at-gmail-dot-com>
// Created: April 19, 2012 (Toronto Island)
// Updated: Septmeber 13, 2012


void cls() {
    //#define ESC   27
    fprintf(stdout, "%c[2J", ESC);
    cout << endl;
    }

void home() {
    //#define ESC   27
    printf("%c[0;0H", ESC);    
    }

void gotoxy(int x, int y) {
    printf("%c[%d;%df", 0x1B, y, x);
    }


void displayBoard( boardRecord board )
{
    long x, y, n;
    
    //cls; //0black 1red 2green 3yellow 4blue 5magnta 6cyan 7white
    printf("%c[30;43m", ESC);
	printf("--| %s |-----------------", peaVersion);
    printf("%c[m", ESC);
    cout << endl;

    cout << "+---+---+---+---+---+---+---+---+" << endl;
    for (x=8; x>0; x--) {
        cout << "|"; 
        for (y=0; y<8; y++) {
            n = (x-1)*8 + y;
            
            // colour Pieces black or white
            if (board.square[n] > 0) {
                printf("%c[30;47m", ESC);
                }
            if (board.square[n] < 0) {
                //0black 1red 2green 3yellow 4blue 5magnta 6cyan 7white
                printf("%c[30;46m", ESC);
                }

			// fancy-schmancy UTF unicode chess characters
			if (UTF8) {			

			// error trap for funky values
			if ( (board.square[n] > 6) || (board.square[n] < -6) ) cout << board.square[n];

            switch(abs(board.square[n])) {
                case  0: cout << "   "; break;
                case  1: cout << " ♟ "; break;
                case  2: cout << " ♝ "; break;
                case  3: cout << " ♞ "; break;
                case  4: cout << " ♜ "; break;
                case  5: cout << " ♛ "; break;
                case  6: cout << " ♚ "; break;
                }
			}

			// plain ASCII characters
			if (!UTF8) {
			
			// error trap for funky values
			if ( (board.square[n] > 6) || (board.square[n] < -6) ) cout << board.square[n];
			
            switch(board.square[n]) {
                case  0: cout << "   "; break;
                case  1: cout << " P "; break;
                case  2: cout << " B "; break;
                case  3: cout << " N "; break;
                case  4: cout << " R "; break;
                case  5: cout << " Q "; break;
                case  6: cout << " K "; break;
                case -1: cout << " p "; break;
                case -2: cout << " b "; break;
                case -3: cout << " n "; break;
                case -4: cout << " r "; break;
                case -5: cout << " q "; break;
                case -6: cout << " k "; break;
                }
			}
            
            // turn off colour
            printf("%c[m", ESC);
            cout << "|"; 
            }
        cout << " " << x << endl;
        cout << "+---+---+---+---+---+---+---+---+" << " " << endl;
        }

    cout << "  a   b   c   d   e   f   g   h  "; 
    if (board.who2move==1)  { printf("%c[30;47m", ESC); cout << " " << board.who2move; }
    if (board.who2move==-1) { printf("%c[30;46m", ESC); cout << board.who2move; }
    printf("%c[m", ESC); 
    cout << " " << endl;
	
	// verbose board
	if (gVerbose) {
		cout << "who2move: " << board.who2move << "      halfmoves: " << board.halfMoves << endl;
		cout << "bCastleQside: " << board.bCastleQside << "  bCastleKside: " << board.bCastleKside << endl;
		cout << "wCastleQside: " << board.wCastleQside << "  wCastleKside: " << board.wCastleKside << endl;
		cout << "wHasCastled: " << board.wHasCastled << "   bHasCastled: " << board.bHasCastled << endl;		
		cout << "enPassantSq: " << board.enPassantSq << "  fiftyCount: " << board.fiftyCount << endl;
		}
    
    return;
}


void displayOverlay( boardRecord &theBoard, moveRecord theMoves[], int numMoves )
{
    long x, y, n;
    int moveIndex;
    
    //cls; //0black 1red 2green 3yellow 4blue 5magnta 6cyan 7white
    printf("%c[30;43m", ESC); 
	printf("--| %s |-----------------", peaVersion);
    printf("%c[m", ESC);
    cout << endl;
    
    cout << "+---+---+---+---+---+---+---+---+" << endl;
    for (x=8; x>0; x--) {
        cout << "|"; 
        
        for (y=0; y<8; y++) {
            n = (x-1)*8 + y;
            
            // colour Pieces black or white
            // 0black 1red 2green 3yellow 4blue 5magnta 6cyan 7white
            if (theBoard.square[n] > 0) printf("%c[30;47m", ESC);
            if (theBoard.square[n] < 0) printf("%c[30;46m", ESC);
            
            // COLOUR IF it is one of the moves in the list
            for (moveIndex=0; moveIndex < numMoves; moveIndex++) {
                if ( (n==theMoves[moveIndex].fromSquare) || (n==theMoves[moveIndex].toSquare) ) printf("%c[30;43m", ESC); 
                }

			// fancy-schmancy UTF unicode chess characters
			if (UTF8) {
            switch(abs(theBoard.square[n])) {
                case  0: cout << "   "; break;
                case  1: cout << " ♟ "; break;
                case  2: cout << " ♝ "; break;
                case  3: cout << " ♞ "; break;
                case  4: cout << " ♜ "; break;
                case  5: cout << " ♛ "; break;
                case  6: cout << " ♚ "; break;
                }
			}

			// plain ASCII characters
			if (!UTF8) {
			
			if ( (theBoard.square[n] > 6) || (theBoard.square[n] < -6) ) cout << theBoard.square[n];
			
            switch(theBoard.square[n]) {
                case  0: cout << "   "; break;
                case  1: cout << " P "; break;
                case  2: cout << " B "; break;
                case  3: cout << " N "; break;
                case  4: cout << " R "; break;
                case  5: cout << " Q "; break;
                case  6: cout << " K "; break;
                case -1: cout << " p "; break;
                case -2: cout << " b "; break;
                case -3: cout << " n "; break;
                case -4: cout << " r "; break;
                case -5: cout << " q "; break;
                case -6: cout << " k "; break;
                }
			}
			
            // turn off colour
            //if (colour==1) printf("%c[m", ESC); colour=0;
            printf("%c[m", ESC); 
            cout << "|"; 
            }
        
        cout << " " << x << endl;
        cout << "+---+---+---+---+---+---+---+---+" << " " << endl;
        }

    cout << "  a   b   c   d   e   f   g   h  "; 
    if (theBoard.who2move==1)  { printf("%c[30;47m", ESC); cout << " " << theBoard.who2move; }
    if (theBoard.who2move==-1) { printf("%c[30;46m", ESC); cout << theBoard.who2move; }
    printf("%c[m", ESC); 
    cout << " " << endl;
	
	// verbose board
	if (gVerbose) {
		cout << "who2move: " << theBoard.who2move << "      halfmoves: " << theBoard.halfMoves << endl;
		cout << "bCastleQside: " << theBoard.bCastleQside << "  bCastleKside: " << theBoard.bCastleKside << endl;
		cout << "wCastleQside: " << theBoard.wCastleQside << "  wCastleKside: " << theBoard.wCastleKside << endl;
		cout << "wHasCastled: " << theBoard.wHasCastled << "   bHasCastled: " << theBoard.bHasCastled << endl;
		cout << "enPassantSq: " << theBoard.enPassantSq << "  fiftyCount: " << theBoard.fiftyCount << endl;
		}
	    
    return;
}


void displayMoves( boardRecord board )
{
    long x, y, n;
    int numMoves, moveIndex;
    struct moveRecord moves[_maxMoves];

    // generate raw moves
    numMoves = generateRawMoves(board, moves, 0);
    cout << numMoves << " moves" << endl;
    displayOverlay( board, moves, numMoves );
 
 }


void displaySqMoves( boardRecord board, int querySquare )
{
    long x, y, n, colour;
    int numMoves, moveIndex;
    struct moveRecord moves[_maxMoves];
    
    // generate raw moves
    numMoves = pieceTree(board, moves, 0, querySquare);
    cout << numMoves << " moves" << endl;
    displayOverlay( board, moves, numMoves );
}
    
