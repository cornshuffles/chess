#include <iostream>
#include <stdio.h>
#include <fstream>
#include <chrono>
#include <thread>
#include <string>
#include "chess.h"
  
using namespace std; 
  
int main(){ 

// Logo Sequence
ifstream logoReader ("logo.txt");

char c = logoReader.get();

// Clear Screen
cout << "\033[2J\033[1;1H";

// Logo
if(logoReader.good() == false){
    cout << "CHESSBOY 9000";
}
while(logoReader.good()){
    cout << c;
    c = logoReader.get();
}

// Newlines
for(int i = 0; i < 5; i++){
    cout << endl;
    this_thread::sleep_until(chrono::system_clock::now() + chrono::milliseconds(150));
}
logoReader.close();

// Game Sequence
string escape;
while(true){

    cout << "\t\t\tNew Game? (Y/N)\n\t\t\t\t";
    // Sanitize input
    while(escape != "Y" && escape != "y" && escape != "N" && escape != "n"){
        cin >> escape;
    }

    // Break if no new game desired
    if(escape != "Y" && escape != "y"){
        break;
    }

    // Initialize the board
    board theBoard;
    theBoard.initBoard();
    theBoard.printBoard();
    int turn = WHITE;
    int movefrom[2];
    int moveto[2];

    while(theBoard.isCheckmate(WHITE) == false && theBoard.isCheckmate(BLACK) == false){
        // Print who's turn it is.
        if(turn == WHITE){
            cout << "White's Turn\n";
        }
        else{
            cout << "Black's Turn\n";
        }
        cout << "Enter coordinates to move from (x then y)" << endl;
        cin >> movefrom[0] >> movefrom[1];
        cout << "Enter coordinates to move to (x then y)" << endl;
        cin >> moveto[0] >> moveto[1];
        theBoard.move(movefrom[0], movefrom[1], moveto[0], moveto[1]);

        if(turn == WHITE){
            turn = BLACK;
        }
        else{
            turn = WHITE;
        }
        theBoard.printBoard();
    }

}

return 0;
} 