#include <iostream>
#include <stdio.h>
#include "chess.h"
  
using namespace std; 
  
int main(){ 
    board theBoard;
    theBoard.initBoard();
    cout << "\n                                  CHESS\n\n";
    theBoard.printBoard();

    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            cout << "X: " << x << " Y: " << y; 
            cout << "\t" << theBoard.getSquare(4,0)->getPiece()->canMove(x,y,&theBoard) << endl;
        }
    }
    return 0;
} 