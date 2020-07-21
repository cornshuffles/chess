#ifndef CHESS_H
#define CHESS_H

#define BLACK 0
#define WHITE 1

// Base Piece Class
class piece{
    int x,y;
    int color; //either BLACK or WHITE
    public:
    int getXCoord(){return x;}
    int getYCoord(){return y;}
    int getColor(){return color;}
};

// Derived Piece Classes

class king: piece{
    public:
    bool canMove(int xNew, int yNew);
};

class queen: piece{
    public:
    bool canMove(int xNew, int yNew);
};

class bishop: piece{
    public:
    bool canMove(int xNew, int yNew);
};

class knight: piece{
    public:
    bool canMove(int xNew, int yNew);
};

class rook: piece{
    public:
    bool canMove(int xNew, int yNew);
};

class pawn: piece{
    public:
    bool canMove(int xNew, int yNew);
};

// Board Classes

class square{
    int x,y;
    bool isOccupied;
    piece * occupyingPiece;

    public:
    void initSquare();
};

class board{
    square squareArray[8][8];

    public:
    void initBoard();
    bool isOccupiedByColor(int x, int y, int color); // Function to return whether a given square is occupied by a specific color
};
#endif