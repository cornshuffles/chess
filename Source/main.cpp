#include <iostream>
#include <stdio.h>
#include "chess.h"
  
using namespace std; 
  
int main(){ 
    board theBoard;
    theBoard.initBoard();
    cout << "\n                                  CHESS\n\n";
    theBoard.printBoard();

    return 0;
} 