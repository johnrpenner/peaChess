// peaBrain 3.4
// Internal Tools and peaCmds
// 
// Copyright 2012 by John Roland Penner <johnrolandpenner-at-gmail-dot-com>
// Created: April 19, 2012 (Toronto Island)
// Updated: September 11, 2012 (Long Lake)


int mod( int square )
{
    int mod, div;

    div = square/8;
    mod = square-8*div;
    return mod;
}


void convert2XYandPrint( int square )
{
    int x = mod(square);
    switch(x) {
        case 0: cout<<"a"; break; case 1:cout<<"b";break;
        case 2: cout<<"c"; break; case 3:cout<<"d";break;
        case 4: cout<<"e"; break; case 5:cout<<"f";break;
        case 6: cout<<"g"; break; case 7:cout<<"h";break;
        }
    cout << square/8+1;
    return;
}


void displayMovelist( boardRecord board )
{
    int numMoves, moveIndex;
    struct moveRecord moves[_maxMoves];
    
    numMoves = generateRawMoves(board, moves, 0);
    cout << endl << "Moves: " << numMoves << endl;
    
    for (moveIndex=0; moveIndex < numMoves; moveIndex++) {
        cout << "  " << moveIndex+1 << ". ";
        convert2XYandPrint( moves[moveIndex].fromSquare );
        cout << "-";
        convert2XYandPrint( moves[moveIndex].toSquare );
        cout << endl;
        }
    return;
}


void displayCaptures( boardRecord board )
{
    int numMoves, moveIndex;
    struct moveRecord moves[_maxMoves];

	// FIND: create, add, and display strings
	//string a = "myString";
	//a += " is concatenated.";
	//cout << a << endl;

    
    numMoves = generateCaptureMoves( board, moves );
    cout << endl << "Captures: " << numMoves << endl;
    
    for (moveIndex=0; moveIndex < numMoves; moveIndex++) {
        cout << "  " << moveIndex+1 << ". ";
        convert2XYandPrint( moves[moveIndex].fromSquare );
        cout << "-";
        convert2XYandPrint( moves[moveIndex].toSquare );
        cout << endl;
        }
    return;
}


void parseMove( boardRecord &board, string cmd )
{
    int a, n, x1, x2, y1, y2;
    int piece;
    int fromSquare, toSquare; 

    char cmdRowTest[] = {'a','b','c','d','e','f','g','h','\0'};
    char cmdPieceTest[] = {'z','p','b','n','r','q','k','\0'};
	char cmdNumTest[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\0'};
    //string strTool;  //  <------ here!!! [gree]

    struct moveRecord theMove;
    struct moveRecord rawMoves[1];
    int evalScore;
    bool inCheck = false;

        
    /*--| peaCmds |-------------------------------------------- 
-    .e2e4 = Make Move e2e4.
     >e1g7 = Forced Move from e1 to g7. 
     -e2   = Delete piece at e2. 
     +wqe4 = Add White Queen at e4. 
-    ?e4   = Show moves for piece at e4.
-    !e5   = Show 'Attacked' if piece at e5 is under attack.
	 new   = New classic game
-	 :FEN  = New game starting from FEN string
	 black = Set who2move to black
	 white = Set who2move to white
	 eval  = Return a static evaluation of the current board
	 depth = Display current search depth
	 depth N = Set Depth to  [1-7]
	 perft N = Run a PERFormance diagnosTic at depth N
	 verbose = Toggle additonal info display
	 cls     = Redraw board without making a move
	 quit    = Return to shell
	 ?       = Display Help
     ---------------------------------------------------------*/

    if (cmd=="") computerMove( gBoard, false );
    
    if (cmd=="new") {
        initClassic( gBoard );
        displayBoard( gBoard );
		//cout << "num chars in new cmd: " << cmd.size() << endl;
        }
    
    // USER MOVE (example: .e2e4 - make a chess move: e2 to e4)
    //find: if (cmd.substr(0,1) == ".") {
    if (cmd[0] == '.') {
        for(a=0; a<8; a++) if (cmd[1] == cmdRowTest[a]) {x1 = a; break;}
        stringstream(cmd.substr(2,1)) >> y1;
        for (a=0; a<8; a++) if (cmd[3] == cmdRowTest[a]) {x2 = a; break;}
        stringstream(cmd.substr(4,1)) >> y2;
        
        fromSquare = (x1) + (y1-1)*8;
        toSquare = (x2) + (y2-1)*8;

        theMove.fromSquare = fromSquare;
        theMove.toSquare = toSquare;
        theMove.moveScore = 0;
		theMove.capturedPiece = board.square[ theMove.toSquare ];

        makeMove( board, theMove ); 
        
        // display the result
        rawMoves[0] = theMove;
        displayOverlay( board, rawMoves, 1 );
        
        } 
        
    // >c1f4 - forced move of piece from c1 to f4
    if (cmd.substr(0,1) == ">") {
        for(a=0; a<8; a++) if (cmd[1] == cmdRowTest[a]) {x1 = a; break;}
        stringstream(cmd.substr(2,1)) >> y1;
        for (a=0; a<8; a++) if (cmd[3] == cmdRowTest[a]) {x2 = a; break;}
        stringstream(cmd.substr(4,1)) >> y2;
        
        fromSquare = (x1) + (y1-1)*8;
        toSquare = (x2) + (y2-1)*8;
        board.square[toSquare] = board.square[fromSquare];
        board.square[fromSquare] = 0;
        cout << "moved: " << cmd[1] << cmd[2] << " to " << cmd[3] << cmd[4] << endl;
        displayBoard(board);
        } 
    
    // -e2 - remove contents of square e2
    if (cmd.substr(0,1) == "-") {
        for (a=0; a<8; a++) if (cmd[1]==cmdRowTest[a]) {x1=a;break;}
        stringstream(cmd.substr(2,1)) >> y1;
        
        board.square[x1+(y1-1)*8] = 0;
        cout << "removed: " << cmd[1] << cmd[2] << endl;
        displayBoard(board); 
        }
    
    // +wpe4 - add white pawn to e4
    if (cmd.substr(0,1) == "+") {
        for (a=0; a<7; a++) if (cmd[2]==cmdPieceTest[a]) {piece=a;break;}
        if (cmd[1]=='b') piece*=-1;
        for (a=0; a<8; a++) if (cmd[3]==cmdRowTest[a]) {x1=a;break;}
        stringstream(cmd.substr(4,1)) >> y1;
        
        board.square[x1+(y1-1)*8] = piece;
        cout << "" << cmd[1] << cmd[2] << " added to " << cmd[3] << cmd[4] << endl;
        displayBoard(board); 
        }
    
    // ?e2 - show moves for square e2
    if ( (cmd.substr(0,1) == "?") && ( cmd.length()==3 ) ) {
        for (a=0; a<8; a++) if (cmd[1]==cmdRowTest[a]) {x1=a;break;}
        stringstream(cmd.substr(2,1)) >> y1;
        n = x1+(y1-1)*8;
        cout << "query: " << cmd[1] << cmd[2] << endl;
        displaySqMoves(board, n); 
        }
    
    // !e4 - returns TRUE if enemy pieces attack square e4. 
    if (cmd.substr(0,1) == "!") {
        for(a=0; a<8; a++) if (cmd[1] == cmdRowTest[a]) {x1 = a; break;}
        stringstream(cmd.substr(2,1)) >> y1;
        
        fromSquare = (x1) + (y1-1)*8; 
        if ( isAttacked(fromSquare, board) ) { cout << "square " << cmd[1] << cmd[2] << " is ATTACKED" << endl; }
        else { cout << "square " << cmd[1] << cmd[2] << " is Not Attacked" << endl; }        
    }

    
    // MISCELLANEOUS commands

	// Depth
	if (cmd=="depth") {
		cout << "Depth = " << gDepth << endl;
		}

	if (cmd.substr(0,6) == "depth ") {
		for(a=0; a<11; a++) if (cmd[6] == cmdNumTest[a]) {x1=a; break;}
		if ( (x1+1 < 8) && (x1+1 > 0) ) {
			gDepth = x1+1;
			cout << "Depth set to " << gDepth << endl;
			}
			else {
			cout << "Depth (1-7); currently: " << gDepth << endl;
			}
		}

	// FEN :r3k2r/pppb1ppp/2np1q1n/2b1p3/2B1P3/2NPBN2/PPPQ1PPP/R3K2R w KQkq
	//if (cmd.substr(0,1) == ":") {
    if (cmd[0] == ':') {
		initFEN( board, cmd );
		displayBoard( board );
		}
		
	// FEN
	if (cmd=="fen") {
		string myFEN;
		myFEN = toFEN( gBoard );
		cout << "FEN: " << myFEN << endl;
		}

	// CLS (clear screen)	
	if (cmd=="cls") {
		displayBoard( board );
		}
        
    if (cmd=="black") {
        gBoard.who2move = -1;
        displayBoard( board );
        }
    
    if (cmd=="white") {
        gBoard.who2move = 1;
        displayBoard( board );
        }

    if (cmd=="moves") {
        displayMoves( board );
        }

    if (cmd=="movelist") {
        gBoard.who2move = 1;
        displayMovelist( board );
        }

    if (cmd=="captures") {
        displayCaptures( board );
        }

    if (cmd=="eval") {
        //displayBoard( gBoard );
        evalScore = 0;
        evalScore = staticEval( board );
        cout << "Static Eval: " << evalScore << endl;
        
        // display if side to move is in check! :-)
        inCheck = isSideToMoveInCheck(board);
        if (inCheck) cout << "CHECK!" << endl;
        if (!inCheck) cout << "not in check" << endl;
		
        displayBoard( gBoard );
		
        }

	// PERFT (and also sets global gDepth)
	/*
		Correct results from NEW:
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
	int tStart;		
	if (cmd.substr(0,6) == "perft ") {
		for(a=0; a<11; a++) if (cmd[6] == cmdNumTest[a]) {x1=a; break;}
		if ( (x1+1 < 9) && (x1+1 > 0) ) {
			gDepth = x1+1;
			cout << "Running PERFT at depth " << gDepth << endl;
			tStart = time(0);
	        evalScore = perft( board, gDepth );
    	    cout << "perft: " << evalScore << endl;
			cout << time(0) - tStart << " seconds" << endl;			
			}
			else {
			cout << "Depth (1-7); currently: " << gDepth << endl;
			}
		}


	// VERBOSE mode on|off
	if (cmd=="verbose") {
		gVerbose = !gVerbose;
        displayBoard( board );
		}


	// HELP
	if (cmd == "?") {
	
		//0black 1red 2green 3yellow 4blue 5magnta 6cyan 7white
		printf("%c[30;43m", ESC);
		printf("--| %s |-----------------", peaVersion);
		printf("%c[m", ESC);
		cout << endl;

		cout << "Copyright 2012 John Roland Penner " << endl << endl;
		cout << "ENTER with no input causes peaBrain to make a Chess Move. " << endl;
		cout << ".e2e4     Move e2e4 " << endl;
		cout << ">e1g7     Forced Move from e1 to g7 " << endl;
		cout << "-e2       Delete piece at e2 " << endl;
		cout << "+wqe4     Add White Queen at e4 " << endl;
		cout << "?e4       Show moves for piece at e4 " << endl;
		cout << "!e5       Show 'Attacked' if piece at e5 is under attack " << endl;
		cout << "new       New classic game " << endl;
		cout << ":FEN      New game from FEN string " << endl;
		cout << "fen       Return FEN string from current board position " << endl;
		cout << "black     Set who2move to black " << endl;
		cout << "white     Set who2move to white " << endl;
		cout << "moves     Display possible moves for current who2move " << endl;
		cout << "captures  Display possible captures for current who2move " << endl;
		cout << "movelist  Text listing of possible moves " << endl;
		cout << "eval      Return a static evaluation of the current baord " << endl;
		cout << "depth     Display current depth of search " << endl;
		cout << "depth N   Set Depth to N [1-7] " << endl;
		cout << "perft N   Run a PERFormance diagnosTic at depth N " << endl;
		cout << "verbose   Toggle additional info display " << endl;
		cout << "cls       Redraw board without making a move " << endl;
		cout << "quit      Return to shell " << endl;
		cout << "?         Display this Help " << endl;
		}


    return;
}

