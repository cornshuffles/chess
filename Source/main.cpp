#include <iostream>
#include <stdio.h>
#include "chess.h"
  
using namespace std; 
  
int main(){ 
    board theBoard;
    theBoard.initBoard();
    cout << "\n                                  CHESS\n\n";
    theBoard.printBoard();
    theBoard = *(theBoard.move(3,1,3,3));
    theBoard.printBoard();
    cout << theBoard.getSquare(3,3)->getPiece()->canMove(3,5, &theBoard);


    return 0;
} 