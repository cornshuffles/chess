#include "chess.h"
#include <cstdlib>

// Board Implementation
void square::initSquare(int x, int y, piece *piece){
    this->x = x;
    this->y = y;
    this->occupyingPiece = piece;
    if(piece == NULL){
        this->isOccupied = false;
    }
    else{
        this->isOccupied = true;
    }

}




// Derived Piece Member Function Implementation
bool king::canMove(int xNew, int yNew){
    int xCurrent = getXCoord();
    int yCurrent = getYCoord();

    // Verify that the new location is a valid board location
    if(xNew <= 0 || yNew <= 0){
        return false;
    }

    //Verify that the new square is not occupied by a friendly piece


    // Verify that the new Square is within reach of the king
    if(abs(xNew - xCurrent) >= 2 || abs(yNew-yCurrent) >= 2){
        return false;
    }
}

