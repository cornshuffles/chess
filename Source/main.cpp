#include <iostream>
#include "stdio.h"
#include <string>  
#include "chess.h"
  
using namespace std; 
  
int main() 
{ 
    int playersTurn = BLACK; 
    printf("Chess\n");
    void initBoard();
    // display board
    printf("Moves should be entered in the following format:\n");
    // move input format
    string move;

    while(!(theBoard->isChecked(playersTurn))){
        // Change turns
        if(playersTurn == WHITE){
			playersTurn = BLACK;
        }
		else{
			playersTurn = WHITE;
        }
        printf("Enter move\n");
        cin>>move;
        
        
    }
} 