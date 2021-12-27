/*===| peaBrain |=============================================================//
 * 
 *  peaBrain 3.4 Copyright 2021 by John Roland Penner
 *  Compile with: g++ pea34.cpp -o p34
 *  
 *  Created: April 19, 2012 (Toronto Island)
 *  Updated: April 14, 2013
 * 
 */


//---| INCLUDES |-----

#include <sstream>
#include <iostream>

// need stdio & stdlib for ubuntu compile
#include <stdio.h>      // printf()
#include <stdlib.h>     // abs()
#include <ctime>

using namespace std;

// project includes
#include "declares.cpp"
#include "moves.cpp"
#include "attacks.cpp"
#include "eval.cpp"
#include "search.cpp"
#include "tools.cpp"
#include "display.cpp"


//---| FUNCTIONS |----- 

int getWords( string myStr, string* myWords )
{
	int numWords, z, mark1, mark2;
	
	mark1=1; mark2=1;
	numWords=0;
	
	for( z=1; z<(myStr.length()+1); z++ ) {
		if ( (myStr.substr(z,1)==" ") || (z==myStr.length() ) ) {
			
			if (myStr.length()==z) {
				mark2 = z;
				myWords[numWords] = myStr.substr(mark1, mark2-mark1+1);
				numWords++;
				mark1 = mark2+1;
				}
				
				else {
				mark2 = z;
				myWords[numWords] = myStr.substr(mark1, mark2-mark1);
				numWords++;
				mark1 = mark2+1;
				}
			}
		}

	return numWords; 
}


std::string int2string( int n )
{
	string myString;
	stringstream mySteam;
	
	mySteam << n;
	myString = mySteam.str();
	return myString;
}


void initClassic( boardRecord &board )
{
    int n;
    //gMoveCount = 0;
    //gDispCount = gMoveCount; 
    board.halfMoves = 0;
    board.who2move = 1;
    board.enPassantSq = _noSuchSquare;

    // initialize castling
    board.wCastleKside = true;     //start out able to castle
    board.wCastleQside = true;     //start out able to castle
    board.bCastleKside = true;     //start out able to castle
    board.bCastleQside = true;     //start out able to castle
    board.wHasCastled = false;
    board.bHasCastled = false;
    
    // initialize classic board
    int white[] = {4,3,2,5,6,2,3,4,1,1,1,1,1,1,1,1};
    int black[] = {-1,-1,-1,-1,-1,-1,-1,-1,-4,-3,-2,-5,-6,-2,-3,-4}; 
    for (n=0;  n<16; n++) board.square[n] = white[n];
    for (n=16; n<48; n++) board.square[n] = 0;
    for (n=48; n<64; n++) board.square[n] = black[n-48];
        
    return;
}


void initFEN( boardRecord &theBoard, string fen )
{
	struct boardRecord board;
	//char a, bf, kq, colour2move;
	int x, y, z;
	int n, n2, numWords;
	string* myWords;					//allocate an arbitrary handle
	myWords = new string[_maxWords];	//then allocate as an array of strings

	// Fischer Variables	
	//int wKingSq, bKingSq;
	//int wRookCounter, bRookCounter;
	//int wRook[64], bRook[64];
	
	// initialize game states
	//gPromotion = false;
	gameFEN = fen;
	gFischer = true;
	
	//Fischer FEN detection variables :: initialize
	//bKingSq = _noSuchSquare; wKingSq = _noSuchSquare;
	//wRook[0] = _noSuchSquare; wRook[1] = _noSuchSquare;
	//bRook[0] = _noSuchSquare; bRook[1] = _noSuchSquare;
	//wRookCounter = 0 : bRookCounter = 0;
	
	// disable opening book
	//gUseBook = false;
	
	// clear out first move
	//gMoveList.fromSquare[0] = _noSuchSquare;
	
	board.who2move = 1;
	board.halfMoves = 0;
	board.enPassantSq = _noSuchSquare;
	board.fiftyCount = 0;
	//board.hashCode = 0
	//board.fischer = _true
	//board.rookSq1 = _noSuchSquare
	//board.rookSq2 = _noSuchSquare
	
	board.wCastleKside = false;     // cant castle unless FEN allows it
	board.wCastleQside = false;
	board.wHasCastled = true;
	board.bCastleKside = false;
	board.bCastleQside = false;
	board.bHasCastled = true;

	// declare temp FEN variables
	string a = "";
	string bf = "";
	string colour2move = "";
	int valA, bCount;
	string kq = "";
	
	// break down the FEN into word elements
	numWords = getWords( fen, myWords );

	// debug: display the words
	//for( z=0; z<numWords; z++ ) { cout << z << ": " << myWords[z] << endl; }

	// and expand word[0] into the raw FEN
	for( z=1; z<(myWords[0].length()+1); z++ ) {
		// extract character to examine
		a = fen.substr(z,1);
		valA = atoi(a.c_str());
		// expand numbers as dashes (e.g. '5' becomes "-----")
		if( valA > 0 ) {
			for( bCount=0; bCount<valA; bCount++ ) {
				bf += '-';
				}
			}
		// otherwise just append the character
		else bf += a;
		}

	// catch invalid FEN constructs
	//if (bf.length()!=71) return false;
	if (bf.length()!=71) cout << "FEN Error: " << bf.length() << "/71 " << bf << endl;

	// drop the raw FEN into the boardRecord
	z = 0;
	for ( y=8; y>0; y-- ) {
		for ( x=1; x<9; x++ ) {
			
			a = bf[z];
			n = ( y*8 - (9-x) );
			
			if (a=="-") board.square[n] = 0;
			if (a=="P") board.square[n] = 1;
			if (a=="B") board.square[n] = 2;
			if (a=="N") board.square[n] = 3;
			if (a=="R") board.square[n] = 4;
			if (a=="Q") board.square[n] = 5;
			if (a=="K") board.square[n] = 6;
			
			if (a=="p") board.square[n] = -1;
			if (a=="b") board.square[n] = -2;
			if (a=="n") board.square[n] = -3;
			if (a=="r") board.square[n] = -4;
			if (a=="q") board.square[n] = -5;
			if (a=="k") board.square[n] = -6;

			z++;
			}
			
		z++;
		}
	
	// use info garnered above to setup for FISCHER FEN decoding
	//if (wRookCounter > 0) and (wRook(0) < wKingSq) then board.rookSq1 = wRook(0) else board.rookSq2 = wRook(0)
	//if (wRookCounter > 1) and (wRook(wRookCounter-1) > wKingSq) then board.rookSq2 = wRook(wRookCounter-1) else board.rookSq1 = wRook(wRookCounter-1)
	//if (bRookCounter > 0) and (bRook(0) < bKingSq) then board.rookSq1 = bRook(0) - 56 else board.rookSq2 = bRook(0) - 56
	//if (bRookCounter > 1) and (bRook(bRookCounter-1) > bKingSq) then board.rookSq2 = bRook(bRookCounter-1) - 56 else board.rookSq1 = bRook(bRookCounter-1) - 56
	
	// set colour to move
	if (numWords >= 1) {
		colour2move = myWords[1];
		if (colour2move=="w" || colour2move=="W") board.who2move = 1;
		if (colour2move=="b" || colour2move=="B") board.who2move = -1;
		}
		
	// set castling options
	if (numWords >=2) {
		
		kq = myWords[2];
		
		// no castling
		if (kq=="-") {
			board.wCastleKside = false;
			board.wCastleQside = false;
			board.bCastleKside = false;
			board.bCastleQside = false;
			board.wHasCastled = true;
			board.bHasCastled = true;
			}
			
		// classic castling assignments
		for( z=0; z<kq.length()+1; z++) {
			a = kq[z];
			if (a=="K") { board.wCastleKside = true; board.wHasCastled = false; }
			if (a=="Q") { board.wCastleQside = true; board.wHasCastled = false; }
			if (a=="k") { board.bCastleKside = true; board.bHasCastled = false; }
			if (a=="q") { board.bCastleQside = true; board.bHasCastled = false; }
			}
		
			// fischer castling assignments
			// rook squares relative to king determined from above FEN
			// FEN: bqnbrnkr/pppppppp/8/8/8/8/PPPPPPPP/BQNBRNKR w Eh -
			/*
			dim as str255 wRookAside, wRookHside, bRookAside, bRookHside
			wRookAside = "" : wRookHside = "" : bRookAside = "" : bRookHside = ""

			// set the column identifiers against which we match castling-status bits.
			if (board.rookSq1 <> _noSuchSquare) then wRookAside = chr$(65+board.rookSq1)
			if (board.rookSq2 <> _noSuchSquare) then wRookHside = chr$(65+board.rookSq2)
			if (board.rookSq1 <> _noSuchSquare) then bRookAside = chr$(97+board.rookSq1)
			if (board.rookSq2 <> _noSuchSquare) then bRookHside = chr$(97+board.rookSq2)

			for z = 1 to len(kq)
				if mid$(kq, z, 1) = wRookAside then board.wCastleQside = _true : board.wHasCastled = _false
				if mid$(kq, z, 1) = wRookHside then board.wCastleKside = _true : board.wHasCastled = _false
				if mid$(kq, z, 1) = bRookAside then board.bCastleQside = _true : board.bHasCastled = _false
				if mid$(kq, z, 1) = bRookHside then board.bCastleKside = _true : board.bHasCastled = _false
			next z
			*/
		
		}
		
	// decode enPassant square
	// For example, Pawn at c4 should have 2 possible moves:
	// 8/7p/p5pb/4k3/P1pPn3/8/P5PP/1rB2RK1 b - d3
	if (numWords >=2) {
		if (myWords[3]=="-") board.enPassantSq = _noSuchSquare;

		if (myWords[3]=="a3") board.enPassantSq = 24;
		if (myWords[3]=="b3") board.enPassantSq = 25;
		if (myWords[3]=="c3") board.enPassantSq = 26;
		if (myWords[3]=="d3") board.enPassantSq = 27;
		if (myWords[3]=="e3") board.enPassantSq = 28;
		if (myWords[3]=="f3") board.enPassantSq = 29;
		if (myWords[3]=="g3") board.enPassantSq = 30;
		if (myWords[3]=="h3") board.enPassantSq = 31;
		
		if (myWords[3]=="a6") board.enPassantSq = 32;
		if (myWords[3]=="b6") board.enPassantSq = 33;
		if (myWords[3]=="c6") board.enPassantSq = 34;
		if (myWords[3]=="d6") board.enPassantSq = 35;
		if (myWords[3]=="e6") board.enPassantSq = 36;
		if (myWords[3]=="f6") board.enPassantSq = 37;
		if (myWords[3]=="g6") board.enPassantSq = 38;
		if (myWords[3]=="h6") board.enPassantSq = 39;
		}
		
	// assign and return the board
	theBoard = board;
	
	// make initial entry into history and display
	//gMoveCount = 0 : gDispCount = 0
	//gameBoards(gMoveCount) = gBoard

	// remember to set the gameFEN if there was one
	//gGame.gameFEN = fen
	//gGame.variant = "[Variant " + chr$(34) + "fischerandom" + chr$(34) + "]"

	// this has not yet been saved
	//gDirtyFlag = _true

	return;
}


std::string toFEN( boardRecord &theBoard )
{
	string fen = "";
	string bf="", a="", kq="";
	int x, y, z, rep;
	int n = 0;
	int thePiece;
	boardRecord fenBoard;
	//string wRookAside, wRookHside, bRookAside, bRookHside;
	
	fenBoard = theBoard;
	
	// generate the raw FEN
	for ( y=8; y>0; y-- ) {
		for ( x=1; x<9; x++ ) {
		
			n = ( y*8 - (9-x) );
			thePiece = fenBoard.square[n];
			
			if ( thePiece==0 ) bf += "-";
			
			if ( thePiece == 1 ) bf += "P";
			if ( thePiece == 2 ) bf += "B";
			if ( thePiece == 3 ) bf += "N";
			if ( thePiece == 4 ) bf += "R";
			if ( thePiece == 5 ) bf += "Q";
			if ( thePiece == 6 ) bf += "K";
			
			if ( thePiece == -1 ) bf += "p";
			if ( thePiece == -2 ) bf += "b";
			if ( thePiece == -3 ) bf += "n";
			if ( thePiece == -4 ) bf += "r";
			if ( thePiece == -5 ) bf += "q";
			if ( thePiece == -6 ) bf += "k";
						
			}
			
		if (y>1) bf += "/";
		}
	
	// compact the raw FEN to regular FEN
	z=0; rep=0;
	while ( z < bf.length() ) {
		rep = 0;
		z++;
		a = bf[z-1];
		
		if (a=="-") {
			rep = 0;
			while ( bf[z+rep]=='-') {
				rep++;
				}
			z += rep;
			fen += int2string( rep+1 );
			}
		else {
			fen += a;
			}
		
		}
	
	// set colour to move
	if ( fenBoard.who2move == 1 ) {
		fen += " w";
		}
	else {
		fen += " b";
		}
		
	// set castling options
	if ( fenBoard.wCastleKside ) kq += "K";
	if ( fenBoard.wCastleQside ) kq += "Q";
	if ( fenBoard.bCastleKside ) kq += "k";
	if ( fenBoard.bCastleQside ) kq += "q";
	if ( kq == "" ) kq = "-";
	fen = fen + " " + kq;
	
	// set fischer castling options
	/* if (fenBoard.fischer == _true)

		wRookAside = "" : wRookHside = "" : bRookAside = "" : bRookHside = ""

		// set the column identifiers against which we match castling-flags
		if (fenBoard.rookSq1 <> _noSuchSquare) then wRookAside = chr$(65+fenBoard.rookSq1)
		if (fenBoard.rookSq2 <> _noSuchSquare) then wRookHside = chr$(65+fenBoard.rookSq2)
		if (fenBoard.rookSq1 <> _noSuchSquare) then bRookAside = chr$(97+fenBoard.rookSq1)
		if (fenBoard.rookSq2 <> _noSuchSquare) then bRookHside = chr$(97+fenBoard.rookSq2)

		// set the actual FEN flags
		if fenBoard.wCastleQside = _true then kq = kq + wRookAside
		if fenBoard.wCastleKside = _true then kq = kq + wRookHside
		if fenBoard.bCastleQside = _true then kq = kq + bRookAside
		if fenBoard.bCastleKside = _true then kq = kq + bRookHside

		if kq="" then kq="-"
		fen = fen + " " + kq

	end if
	*/
	
	// set enPassant square
	if ( fenBoard.enPassantSq == _noSuchSquare ) fen += " -";

	if ( fenBoard.enPassantSq == 24 ) fen += " a3";
	if ( fenBoard.enPassantSq == 25 ) fen += " b3";
	if ( fenBoard.enPassantSq == 26 ) fen += " c3";
	if ( fenBoard.enPassantSq == 27 ) fen += " d3";
	if ( fenBoard.enPassantSq == 28 ) fen += " e3";
	if ( fenBoard.enPassantSq == 29 ) fen += " f3";
	if ( fenBoard.enPassantSq == 30 ) fen += " g3";
	if ( fenBoard.enPassantSq == 31 ) fen += " h3";
	
	if ( fenBoard.enPassantSq == 32 ) fen += " a6";
	if ( fenBoard.enPassantSq == 33 ) fen += " b6";
	if ( fenBoard.enPassantSq == 34 ) fen += " c6";
	if ( fenBoard.enPassantSq == 35 ) fen += " d6";
	if ( fenBoard.enPassantSq == 36 ) fen += " e6";
	if ( fenBoard.enPassantSq == 37 ) fen += " f6";
	if ( fenBoard.enPassantSq == 38 ) fen += " g6";
	if ( fenBoard.enPassantSq == 39 ) fen += " h6";
	
	
	return fen;

}


bool computerMove( boardRecord &theBoard, bool useBookOpenings )
{
	bool validMoveMade = true;
    struct moveRecord theMove, rawMoves[1];
	
    cout << "NegaMax evaluating";
	
	theMove = computerSearch( theBoard, gDepth );
	
	if (theMove.fromSquare == _noSuchSquare) validMoveMade = false;
    if (validMoveMade) {
        
		makeMove( theBoard, theMove );
		
		if (isSideToMoveInCheck(theBoard)) cout << "CHECK!" << endl; 
        
		rawMoves[0] = theMove;
		displayOverlay( theBoard, rawMoves, 1 );
    	
		}
	
    return validMoveMade;
}

  
//--| MAIN |-----------------------------------------------

int main ()
{
    string cmd;

    // INITIALIZE
    initClassic( gBoard );
    displayBoard( gBoard );
    
    // MAIN COMMAND LOOP
    do {
        cout << endl << "peaCmd: ";
        getline( cin, cmd );
        parseMove( gBoard, cmd );
        
        } while(cmd!="quit");
    
    return 0;
}

