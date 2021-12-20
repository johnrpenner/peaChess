// peaBrain 3.4
// Declarations
// 
// Copyright 2012 by John Roland Penner <johnrolandpenner-at-gmail-dot-com>
// Created: April 19, 2012 (Toronto Island)
// Updated: August 30, 2013


//---| CONSTANTS |------- 

#define ESC  27
const char peaVersion[18] = "peaBrain 3.4";

const bool colourTerm = true;
const bool UTF8 = false;
const bool _gVerbose = false;
bool gVerbose = _gVerbose;

const int _gDepth = 3;
const int _maxMoves = 255;
const int _maxGameMoves = 250;
const int _maxWords = 255;
const int _noSuchSquare = 99;
const int _gFlip = 0;

const int _mateScore = 65535;
const int _iAmMateScore = -65535;
const int _iAmInCheckScore = -16383;
const int _stalemateScore = 0;
const int _infinity = 99999999;
const int _minQSearchDepth = -18;

const int _pawnWt   = 100;
const int _bishopWt = 330;
const int _knightWt = 320;
const int _rookWt   = 500;
const int _queenWt  = 900;
const int _kingWt   = 4000; //C.Shannon: king > (Sum d'otherTerms)

// Weight of Evals
const int _wtMobility = 1;		// Shannon's weight for Mobility was 1/10 pawnWt
const int _wtCastleBonus = 10;		// weight of 10 * _castleBonus
const int _wtTropism = 1;		// scale x Tropsim Scores by this amount
const int _wtKingGravity = 10;	// scale x King Gravity (of targets 2, 3)
const int _wtPassedPawn = 22;	// weight of Passed Pawn
const int _wtDoubledPawn = 11;	// Penalty for Doubled Pawn
const int _wtKingShelter = 6;	// Bonus for Each Pawn Sheltering a Castled King
const int _wtBishopPair = 40;	// Bonus for Bishop Pair


//---| GLOBALS |----- 

// squareVals: 1=Pawn 2=Bishop 3=kNight 4=Rook 5=Queen 6=King

struct boardRecord
{
    int who2move;
    int halfMoves;
    int square[64];
    bool wCastleKside; 
    bool wCastleQside;
    bool bCastleKside;
    bool bCastleQside;
    bool wHasCastled;
    bool bHasCastled;
    int enPassantSq;
    int fiftyCount;

};


struct moveRecord
{
    int fromSquare;
    int toSquare;
	int capturedPiece;
    int moveScore;
};


// GLOBAL Variables
struct boardRecord gBoard;
bool gInCheck = false;
bool gPromotion = false;
int gDepth = _gDepth;

// counters during search
int gMovesMade = 0;
int gqNodes = 0;

// fischer-related globals
bool gFischer = false;
string gameFEN = "rubadubdub";



// Initialize Board Masks and Move Vectors

int gPieceWt[7]= { 0, _pawnWt, _bishopWt, _knightWt, _rookWt, _queenWt, _kingWt };

int sq2Mask[64] = { 
    21, 22, 23, 24, 25, 26, 27, 28,
    31, 32, 33, 34, 35, 36, 37, 38,
    41, 42, 43, 44, 45, 46, 47, 48,
    51, 52, 53, 54, 55, 56, 57, 58,
    61, 62, 63, 64, 65, 66, 67, 68,
    71, 72, 73, 74, 75, 76, 77, 78,
    81, 82, 83, 84, 85, 86, 87, 88,
    91, 92, 93, 94, 95, 96, 97, 98 };

int gMaskBoard[120] = { 
    -1,-1,-1,-1,-1,-1,-1,-1,-1, -1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1, -1,
    -1, 1, 1, 1, 1, 1, 1, 1, 1, -1,
    -1, 1, 1, 1, 1, 1, 1, 1, 1, -1,
    -1, 1, 1, 1, 1, 1, 1, 1, 1, -1,
    -1, 1, 1, 1, 1, 1, 1, 1, 1, -1,
    -1, 1, 1, 1, 1, 1, 1, 1, 1, -1,
    -1, 1, 1, 1, 1, 1, 1, 1, 1, -1,
    -1, 1, 1, 1, 1, 1, 1, 1, 1, -1,
    -1, 1, 1, 1, 1, 1, 1, 1, 1, -1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1, -1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1, -1 };


int wPawnVect[6] = { 7, 9, 8, 16, -1, 1 };
int wPawnMask[6] = { 9, 11, 10, 20, -1, 1 };

int bPawnVect[6] = { -9, -7, -8, -16, 1, -1 };
int bPawnMask[6] = { -11, -9, -10, -20, 1, -1 };

int gBishopVect[5] = { 7, 9, -7, -9 };
int gBishopMask[5] = { 9, 11, -9, -11 }; 

int gKnightVect[8] = { 15, 17, 10, -6, -15, -17, -10, 6 };
int gKnightMask[8] = { 19, 21, 12, -8, -19, -21, -12, 8 };

int gRookVect[5] = { 8, 1, -1, -8 };
int gRookMask[5] = { 10, 1, -1, -10 }; 

int gQueenVect[8] = { 7, 9, -7, -9, 8, 1, -1, -8 };
int gQueenMask[8] = { 9, 11, -9, -11, 10, 1, -1, -10 };

int gKingVect[8] = { 7, 9, -7, -9, 8, -8, 1, -1 };
int gKingMask[8] = { 9, 11, -9, -11, 10, -10, 1, -1 }; 


// WHITE PAWN TROPISM
// as per: Tomasz Michniewski (Progszach)
// ChessWiki > Simplified Evaluation Function
int gWhitePawnTropism[64] = { 
    0,  0,  0,  0,  0,  0,  0,  0, 
    5, 10, 10,-20,-20, 10, 10,  5,
    5, -5,-10,  0,  0,-10, -5,  5,
    0,  0,  0, 20, 20,  0,  0,  0,
    5,  5, 10, 25, 25, 10,  5,  5,
    10, 10, 20, 30, 30, 20, 10, 10,
    50, 50, 50, 50, 50, 50, 50, 50,
    0,  0,  0,  0,  0,  0,  0,  0 };


// BLACK PAWN TROPSIM
int gBlackPawnTropism[64] = {
    0,  0,  0,  0,  0,  0,  0,  0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
    5,  5, 10, 25, 25, 10,  5,  5,
    0,  0,  0, 20, 20,  0,  0,  0,
    5, -5,-10,  0,  0,-10, -5,  5,
    5, 10, 10,-20,-20, 10, 10,  5,
    0,  0,  0,  0,  0,  0,  0,  0 }; 


// WHITE KNIGHT TROPISM
// as per: Tomasz Michniewski (Progszach)
// ChessWiki > Simplified Evaluation Function
int gWhiteKnightTropism[64] = { 
    -40,-20,  0,  5,  5,  0,-20, -40,
    -30,  5, 10, 15, 15, 10,  5, -30,
    -30,  0, 15, 20, 20, 15,  0, -30,
    -30,  5, 15, 20, 20, 15,  5, -30,
    -30,  0, 10, 15, 15, 10,  0, -30,
    -30,  0, 10, 15, 15, 10,  0, -30,
    -40,-20,  0,  0,  0,  0,-20, -40,
    -50,-40,-30,-30,-30,-30,-40, -50 };

// BLACK KNIGHT TROPSIM
int gBlackKnightTropism[64] = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -40,-20,  0,  5,  5,  0,-20,-40 };



//---| INTERFACE DECLARATIONS |----- 

// main.cpp
int getWords( string myStr, string *myWords );
void initClassic( boardRecord &board );
void initFEN( boardRecord &theBoard, string fen );
std::string toFEN( boardRecord &theBoard );
bool computerMove( boardRecord &theBoard, bool useBookOpenings );
//void initBoard( boardRecord &board );
//void initMasks( int sq2Mask[] );


// tools.cpp
void convert2XYandPrint( int square );
int mod( int square );
void displayMovelist( boardRecord board );
void parseMove( boardRecord &board, string cmd );


// display.cpp
void cls();
void gotoxy(int x, int y); 
void displayBoard( boardRecord board );
void displayOverlay( boardRecord &theBoard, moveRecord theMoves[], int numMoves );
void displayMoves( boardRecord board );
void displaySqMoves( boardRecord board, int querySquare );


// moves.cpp
int sq2X( int index );
int sq2Y( int index ); 
int wPawnMoves( boardRecord board, moveRecord moves[], int numMoves, int querySquare );
int bPawnMoves( boardRecord board, moveRecord moves[], int numMoves, int querySquare );
int bishopMoves( boardRecord theBoard, moveRecord moves[], int numMoves, int querySquare, int pieceColour );
int knightMoves( boardRecord theBoard, moveRecord moves[], int numMoves, int querySquare, int pieceColour );
int rookMoves( boardRecord theBoard, moveRecord moves[], int numMoves, int querySquare, int pieceColour );
int queenMoves( boardRecord theBoard, moveRecord moves[], int numMoves, int querySquare, int pieceColour );
int wKingMoves( boardRecord theBoard, moveRecord moves[], int numMoves, int querySquare );
int bKingMoves( boardRecord theBoard, moveRecord moves[], int numMoves, int querySquare );
int pieceTree( boardRecord theBoard, moveRecord moves[], int numMoves, int querySquare ); 
int attacks2moves( int sq, boardRecord &theBoard, int numCaptureMoves, int attackedSquares[], int numMoves, moveRecord moves[] );
int generateRawMoves(boardRecord &board, moveRecord moves[]);
int generateLegalMoves( boardRecord &board, moveRecord moves[] );
int attacks2moves( int sq, boardRecord &theBoard, int numCaptures, int attackedSquares[], int numMoves, moveRecord moves[] );
int generateCaptureMoves( boardRecord &board, moveRecord moves[] );


// attacks.cpp
int wPawnAttacks( boardRecord theBoard, int attackedSquares[], int numMoves, int querySquare );
int bPawnAttacks( boardRecord theBoard, int attackedSquares[], int numMoves, int querySquare );
int bishopAttacks( boardRecord theBoard, int attackedSquares[], int numMoves, int querySquare, int pieceColour );
int knightAttacks( boardRecord theBoard, int attackedSquares[], int numMoves, int querySquare, int pieceColour );
int rookAttacks( boardRecord theBoard, int attackedSquares[], int numMoves, int querySquare, int pieceColour );
int queenAttacks( boardRecord theBoard, int attackedSquares[], int numMoves, int querySquare, int pieceColour );
int wKingAttacks( boardRecord theBoard, int attackedSquares[], int numMoves, int querySquare );
int bKingAttacks( boardRecord theBoard, int attackedSquares[], int numMoves, int querySquare );


// eval.cpp
int staticEval( boardRecord &theBoard );


// search.cpp
void makeMove( boardRecord &theBoard, moveRecord theMove ); 
void sortMoves( moveRecord moves[], int numMoves );
bool isAttacked( int querySquare, boardRecord &theBoard );
bool isSideToMoveInCheck( boardRecord &theBoard );
bool isLegalPosition( boardRecord &theBoard ); 
int negaSearch( boardRecord &board, int alphaScore, int betaScore, int depth, int ply);
moveRecord computerSearch( boardRecord &theBoard, int depth );
int perft( boardRecord &inBoard, int depth );

