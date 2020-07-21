#ifndef CHESS_H
#define CHESS_H

#define BLACK 0
#define WHITE 1

// Base Piece Class
class piece{
    int x,y;
    int color; //either BLACK or WHITE
    public:
    void initPiece(int color, int x, int y);
    int getXCoord(){return x;}
    int getYCoord(){return y;}
    int getColor(){return color;}
};

// Derived Piece Classes

class king:public piece{
    public:
    bool canMove(int xNew, int yNew);
};

class queen:public piece{
    public:
    bool canMove(int xNew, int yNew);
};

class bishop:public piece{
    public:
    bool canMove(int xNew, int yNew);
};

class knight:public piece{
    public:
    bool canMove(int xNew, int yNew);
};

class rook:public piece{
    public:
    bool canMove(int xNew, int yNew);
};

class pawn:public piece{
    public:
    bool canMove(int xNew, int yNew);
};

// Board Classes

class square{
    int x,y;
    bool isOccupied;
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
};
#endif