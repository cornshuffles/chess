#ifndef CHESS_H
#define CHESS_H

#define BLACK 0
#define WHITE 1

#define ROOK    2
#define KNIGHT  3
#define BISHOP  4
#define QUEEN   5
#define KING    6
#define PAWN    7

// Board Classes

class square{
    int x,y;
    piece * occupyingPiece;

    public:
    void initSquare(int x, int y, piece *piece);
};

class board{
    square squareArray[8][8];

    public:
    void initBoard();
    square* getSquare(int x, int y);
    bool isOccupiedByColor(int x, int y, int color); // Function to return whether a given square is occupied by a specific color
    bool isOccupied(int x, int y); // Function to return whether a given square is occupied
    bool isOccupiedByPiece(int x, int y, int type); // Function to return whether a given square is occupied by a given piece
    bool isChecked(int color, board *theBoard); // Function returning a bool indicating whether the given color is in check
    bool checkLinesOfSight(int x, int y, board *theBoard); // Function recursively checks lines of sight from given point for non-knight threats
    bool checkNorth(int x, int y, board *theBoard); // Function recursively checks north line of sight for threats
    bool checkNorthEast(int x, int y, board *theBoard); // Function recursively checks north-east line of sight for threats
    bool checkEast(int x, int y, board *theBoard); // Function recursively checks east line of sight for threats
    bool checkSouthEast(int x, int y, board *theBoard); // Function recursively checks south-east line of sight for threats
    bool checkSouth(int x, int y, board *theBoard); // Function recursively checks south line of sight for threats
    bool checkSouthWest(int x, int y, board *theBoard); // Function recursively checks south-west line of sight for threats
    bool checkWest(int x, int y, board *theBoard); // Function recursively checks west line of sight for threats
    bool checknorthWest(int x, int y, board *theBoard); // Function recursively checks north-west line of sight for threats
};

// Base Piece Class
class piece{
    int x,y;
    int color; // either BLACK or WHITE
    int type; // either ROOK, KNIGHT, BISHOP, QUEEN, KING, or PAWN
    public:
    void initPiece(int color, int x, int y);
    int getXCoord(){return x;}
    int getYCoord(){return y;}
    int getColor(){return color;}
    int getPiece(){return type;}
};

// Derived Piece Classes

class king:public piece{
    bool hasMoved = false;
    public:
    bool canMove(int xNew, int yNew, board *theBoard);
    void moved(){hasMoved = true;}
};

class queen:public piece{
    public:
    bool canMove(int xNew, int yNew, board *theBoard);
};

class bishop:public piece{
    public:
    bool canMove(int xNew, int yNew, board *theBoard);
};

class knight:public piece{
    public:
    bool canMove(int xNew, int yNew, board *theBoard);
};

class rook:public piece{
    bool hasMoved = false;
    public:
    bool canMove(int xNew, int yNew, board *theBoard);
    void moved(){hasMoved = true;}
};

class pawn:public piece{
    bool hasMoved = false;
    public:
    bool canMove(int xNew, int yNew);
    void moved(){hasMoved = true;}
};


#endif