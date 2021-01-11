#include "chess.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

// Linked List Implementation
void linkedList::insert(int piece){
    node *temp = new node;
    temp->piece = piece;
    temp->next = NULL;
    if(head == NULL){
        head = temp;
        tail = temp;
    }
    else{
        tail->next = temp;
        tail = tail->next;
    }
}


// Game Utility Functions

/*----------------------------------------------------------*
 * Function:    isSquareOnBoard                             *
 * Params:      int x - x position to check                 *
 *              int y - y position to check                 *
 * Returns: bool representing if the position is valid      *
 * Description: returns a bool reprenting whether the       *
 *              queried position is valid                   *
 * ---------------------------------------------------------*/
bool isSquareOnBoard(int x, int y){
    if((x >= 0 && x <= 7) && (y >= 0 && y <= 7)){
        return true;
    }
    else{
        return false;
    }
}

/*----------------------------------------------------------*
 * Function:    printTurn                                   *
 * Params:      int turn - BLACK or WHITE                   *
 * Returns: void                                            *
 * Description: Print's whose turn it is to stdout          *
 * ---------------------------------------------------------*/
void printTurn(int turn){
    if(turn){
        cout << "White's Turn\n";
    }
    else{
        cout << "Black's Turn\n";
    }
}

/*----------------------------------------------------------*
 * Function:    printClearBoard                             *
 * Params:      board *theBoard - pointer to the board to   *
 *                                print                     *
 * Returns: void                                            *
 * Description: Clears the terminal then prints the board   *
 * ---------------------------------------------------------*/
void printClearBoard(board *theBoard){
    cout << "\033[2J\033[1;1H";
    theBoard->printBoard();
}

/*----------------------------------------------------------*
 * Function:    getMoveSquare                               *
 * Params:      int *square - int array to store move       *
 *                             coordinates in               *
 * Returns: void                                            *
 * Description: Gets coordinates for a move from stdin.     *
 *              Supports coordinates being entered one at a *
 * time numerically, or coordinates being entered as a pair *
 * alphanumerically                                         *
 * ---------------------------------------------------------*/
bool getMoveSquare(int *square){
    string input;
    getline(cin, input);
    // verify length is less than 3
    if(input.length() > 2 || input.length() < 1){ 
        return false;
    }
    // numerical entering
    else if(input.length() == 1){
        if(input[0] < 48 || input[0] > 55){
            return false;
        }
        square[0] = input[0] - '0';
        getline(cin, input);
        if(input.length() != 1 || input[0] < 48 || input[0] > 55){
            return false;
        }
        else{
            square[1] = input[0] - '0';
            return true;
        }
    }
    // alphanumerical entering
    else{
        // verify column (capital or lower case A-H)
        if(input[0] < 65 || (input[0] > 72 && input[0] < 97) || input[0] > 104){
            return false;
        }
        // verify row (int 1-8)
        else if(input[1] < 49 || input[1] > 56) {
            return false;
        }
        else{
            switch(input[0]){
            case 'A':
            case 'a':
                square[0] = 0;
                break;
            case 'B':
            case 'b':
                square[0] = 1;
                break;
            case 'C':
            case 'c':
                square[0] = 2;
                break;
            case 'D':
            case 'd':
                square[0] = 3;
                break;
            case 'E':
            case 'e':
                square[0] = 4;
                break;
            case 'F':
            case 'f':
                square[0] = 5;
                break;
            case 'G':
            case 'g':
                square[0] = 6;
                break;
            case 'H':
            case 'h':
                square[0] = 7;
                break;
            default:
                square[0] = 8; // Out of bounds square
                break;
            }

            square[1] = (input[1] - '0') - 1;
            return true;
        }
    }

}

/*----------------------------------------------------------*
 * Function:    getMove                                     *
 * Params:      int *moveFrom - int array to store move     *
 *                              from coordinates in         *
 *              int *moveTo - int array to store move to    *
 *                            coordinates in                *
 *              int color - the color of piece to move
 * Returns: void                                            *
 * Description: Gets coordinates for a move from stdin.     *
 *              Supports coordinates being entered one at a *
 * time numerically, or coordinates being entered as a pair *
 * alphanumerically                                         *
 * ---------------------------------------------------------*/
void getMove(int *moveFrom, int *moveTo, board *theBoard, int color){
    // get moveFrom
    while(getMoveSquare(moveFrom) == false || !theBoard->isOccupiedByColor(moveFrom[0], moveFrom[1], color)){
        cout << "Invalid piece!\n";
    }

    // get moveTo
    while(getMoveSquare(moveTo) == false || !theBoard->getSquare(moveFrom[0], moveFrom[1])->getPiece()->canMove(moveTo[0], moveTo[1], theBoard)){
        cout << "Invalid move!\n";
    }
}

/*----------------------------------------------------------*
 * Function:    copyBoard                                   *
 * Params:      board* boardToCopy - pointer to the board   *
 *                                   to copy                *
 * Returns: board* - the copied board                       *
 * Description: Creates a new board object identical to the *
 *              one passed in, with new piece objects then  *
 *              returns a pointer to it                     *
 * ---------------------------------------------------------*/
board *copyBoard(board *boardToCopy){
    board *boardToReturn = new board();
    
    // Iterate over boardToCopy and create copies of its piece objects to place onto the new board object
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            if(boardToCopy->isOccupied(x,y)){
                switch(boardToCopy->getSquare(x,y)->getPiece()->getType()){
                    case PAWN:{
                            pawn *newPawn = new pawn();
                            newPawn->initPiece(boardToCopy->getSquare(x,y)->getPiece()->getColor(), x, y, PAWN);
                            boardToReturn->getSquare(x, y)->initSquare(x, y, newPawn);
                            break;}
                        case ROOK:{
                            rook *newRook = new rook();
                            newRook->initPiece(boardToCopy->getSquare(x,y)->getPiece()->getColor(), x, y, ROOK);
                            boardToReturn->getSquare(x, y)->initSquare(x, y, newRook);
                            break;}
                        case KNIGHT:{
                            knight *newKnight = new knight();
                            newKnight->initPiece(boardToCopy->getSquare(x,y)->getPiece()->getColor(), x, y, KNIGHT);
                            boardToReturn->getSquare(x, y)->initSquare(x, y, newKnight);
                            break;}
                        case BISHOP:{
                            bishop *newBishop = new bishop();
                            newBishop->initPiece(boardToCopy->getSquare(x,y)->getPiece()->getColor(), x, y, BISHOP);
                            boardToReturn->getSquare(x, y)->initSquare(x, y, newBishop);
                            break;}
                        case QUEEN:{
                            queen *newQueen = new queen();
                            newQueen->initPiece(boardToCopy->getSquare(x,y)->getPiece()->getColor(), x, y, QUEEN);
                            boardToReturn->getSquare(x, y)->initSquare(x, y, newQueen);
                            break;}
                        case KING:{
                            king *newKing = new king();
                            newKing->initPiece(boardToCopy->getSquare(x,y)->getPiece()->getColor(), x, y, KING);
                            boardToReturn->getSquare(x, y)->initSquare(x, y, newKing);
                            break;}
                        default:{
                            boardToReturn->getSquare(x, y)->initSquare(x, y, NULL);
                            break;
                        }
                }
            }
            else{
                boardToReturn->getSquare(x, y)->initSquare(x, y, NULL);
            }
        }
    }
    return boardToReturn;
}

// Board Implementation

/*----------------------------------------------------------*
 * Function:    initSquare                                  *
 * Params:      int x - x position to init the square to    *
 *              int y - y position to init the square to    *
 *              piece* - pointer to piece to place on the   *
 *                   square, NULL for no piece              *
 * Returns: Void                                            *
 * Description: initializes the member data of a square     *
 *              object                                      *
 * ---------------------------------------------------------*/
void square::initSquare(int x, int y, piece *piece){
    this->x = x;
    this->y = y;
    this->occupyingPiece = piece;
    }

/*------------------------------------------------------*
 * Function:    initBoard                               *
 * Params:      None                                    *
 * Returns:     Void                                    *
 * Description: populates the member data of a board    *
 *              object                                  *
 * -----------------------------------------------------*/
void board::initBoard(){
    // Loop through each square and initialize the square with its position and starting piece
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            // White home row
            if(y == 0){
                switch(x){
                    case 0:
                    case 7:{
                    // Rooks
                        rook *whiteRook = new rook();
                        whiteRook->initPiece(WHITE, x, y, ROOK);
                        squareArray[x][y].initSquare(x, y, whiteRook);
                    break;}
                    case 1:
                    case 6:{
                    // Knights
                        knight *whiteKnight = new knight();
                        whiteKnight->initPiece(WHITE, x, y, KNIGHT);
                        squareArray[x][y].initSquare(x, y, whiteKnight);
                    break;}
                    case 2:
                    case 5:{
                    // Bishops
                        bishop *whiteBishop = new bishop();
                        whiteBishop->initPiece(WHITE, x, y, BISHOP);
                        squareArray[x][y].initSquare(x, y, whiteBishop);
                    break;}
                    case 3:{
                    // Queen
                        queen *whiteQueen = new queen();
                        whiteQueen->initPiece(WHITE, x, y, QUEEN);
                        squareArray[x][y].initSquare(x, y, whiteQueen);
                    break;}
                    case 4:{
                    // King
                        king *whiteKing = new king();
                        whiteKing->initPiece(WHITE, x, y, KING);
                        squareArray[x][y].initSquare(x, y, whiteKing);
                    break;}
                    
                }
            }
            // Black home row
            else if(y == 7){
                switch(x){
                    case 0:
                    case 7:{
                    // Rooks
                        rook *blackRook = new rook();
                        blackRook->initPiece(BLACK, x, y, ROOK);
                        squareArray[x][y].initSquare(x, y, blackRook);
                        break;}
                    case 1:
                    case 6:{
                    // Knights
                        knight *blackKnight = new knight();
                        blackKnight->initPiece(BLACK, x, y, KNIGHT);
                        squareArray[x][y].initSquare(x, y, blackKnight);
                        break;}
                    case 2:
                    case 5:{
                    // Bishops
                        bishop *blackBishop = new bishop();
                        blackBishop->initPiece(BLACK, x, y, BISHOP);
                        squareArray[x][y].initSquare(x, y, blackBishop);
                        break;}
                    case 3:{
                    // Queen
                        queen *blackQueen = new queen();
                        blackQueen->initPiece(BLACK, x, y, QUEEN);
                        squareArray[x][y].initSquare(x, y, blackQueen);
                        break;}
                    case 4:{
                    // King
                        king *blackKing = new king();
                        blackKing->initPiece(BLACK, x, y, KING);
                        squareArray[x][y].initSquare(x, y, blackKing);
                        break;}
                    
                }
            }
            // All y=1 squares get initialized with a white pawn
            else if(y == 1){
                pawn *whitePawn = new pawn();
                whitePawn->initPiece(WHITE, x, y, PAWN);
                squareArray[x][y].initSquare(x, y, whitePawn);
            }
            // All y=6 squares get initialized with a black pawn
            else if(y == 6){
                pawn *blackPawn = new pawn();
                blackPawn->initPiece(BLACK, x, y, PAWN);
                squareArray[x][y].initSquare(x, y, blackPawn);
            }
            else{
                squareArray[x][y].initSquare(x, y, NULL);
            }
        }
    }
}

/*------------------------------------------------------*
 * Function:    getSquare                               *
 * Params:      int x - x position of the square        *
 *              int y - y position of the square        *
 *                                                      *
 * Returns:     square* - Pointer to the given square   *
 *                                                      *
 * Description: returns a pointer to the square         *
 *              specified by the params                 *
 * -----------------------------------------------------*/
 square* board::getSquare(int x, int y){
    return &squareArray[x][y];
 }

/*------------------------------------------------------*
 * Function:    isOccupied                              *
 * Params:      int x - x position to search on         *
 *              int y - y position to search on         *
 *                                                      *
 * Returns:     bool - indicates whether a given square *
 *                     is occupied                      *
 * Description: returns a bool indicating if a given    *
 *              square is occupied                      *
 * -----------------------------------------------------*/
bool board::isOccupied(int x, int y){
    if(squareArray[x][y].getPiece() == NULL){
        return false;
    }
    else{
        return true;
    }        
}

/*------------------------------------------------------*
 * Function:    isOccupiedByColor                       *
 * Params:      int x - x position to search on         *
 *              int y - y position to search on         *
 *              int color - color of the piece to look  *
 *                          for                         *
 * Returns:     bool - indicates whether a given square *
 *                     is occupied by a given color     *
 * Description: returns a bool indicating if a given    *
 *              square is occupied by a given color     *
 * -----------------------------------------------------*/
bool board::isOccupiedByColor(int x, int y, int color){
    if(squareArray[x][y].getPiece() == NULL){
        return false;
    }
    else if(squareArray[x][y].getPiece()->getColor() == color){
        return true;
    }
    else{
        return false;
    }       
}

/*------------------------------------------------------*
 * Function:    isOccupiedByPiece                       *
 * Params:      int x - x position to search on         *
 *              int y - y position to search on         *
 *              int type - the type of piece to look    *
 *                         for                          *
 * Returns:     bool - indicates whether a given square *
 *                     is occupied by a given piece     *
 * Description: returns a bool indicating if a given    *
 *              square is occupied by a given piece     *
 * -----------------------------------------------------*/
bool board::isOccupiedByPiece(int x, int y, int type){
    if(squareArray[x][y].getPiece() == NULL){
        return false;
    }
    else if(squareArray[x][y].getPiece()->getType() == type){
        return true;
    }
    else{
        return false;
    }       
}

/*------------------------------------------------------*
 * Function:    isChecked                               *
 * Params:      int color - color of king to check      *
 *                                                      *
 * Returns:     bool - indicates whether the king of    *
 *                     the given color is in check on   *
 *                     the given board                  *
 * Description: returns a bool indicating if the given  *
 *              color's king is in check                *
 * -----------------------------------------------------*/
bool board::isChecked(int color){
    int xCurrent, yCurrent; // Current position of the specified king
    int enemyColor = (int)(!((bool)color));
    bool breakFlag = false;
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            if(isOccupied(x, y) && squareArray[x][y].getPiece()->getType() == KING && squareArray[x][y].getPiece()->getColor() == color){
                xCurrent = x;
                yCurrent = y; 
                breakFlag = true;
            }
        }
        if(breakFlag){
            break;
        }
    }
     // First verify that the king is not threatened by knights
     if(!(xCurrent + 1 > 7 || yCurrent + 2 > 7)){
        if(isOccupiedByColor(xCurrent + 1, yCurrent + 2, enemyColor) && squareArray[xCurrent + 1][yCurrent + 2].getPiece()->getType() == KNIGHT){
            return true;
        }
    }
    if(!(xCurrent + 2 > 7 || yCurrent + 1 > 7)){
        if(isOccupiedByColor(xCurrent + 2, yCurrent + 1, enemyColor) && squareArray[xCurrent + 2][yCurrent + 1].getPiece()->getType() == KNIGHT){
            return true;
        }
    }
    if(!(xCurrent + 2 > 7 || yCurrent - 1 < 0)){
        if(isOccupiedByColor(xCurrent + 2, yCurrent - 1, enemyColor) && squareArray[xCurrent + 2][yCurrent - 1].getPiece()->getType() == KNIGHT){
            return true;
        }
    }
    if(!(xCurrent + 1 > 7 || yCurrent - 2 < 0)){
        if(isOccupiedByColor(xCurrent + 1, yCurrent - 2, enemyColor) && squareArray[xCurrent + 1][yCurrent - 2].getPiece()->getType() == KNIGHT){
            return true;
        }
    }
    if(!(xCurrent - 1 < 0 || yCurrent - 2 < 0)){
        if(isOccupiedByColor(xCurrent - 1, yCurrent - 2, enemyColor) && squareArray[xCurrent - 1][yCurrent - 2].getPiece()->getType() == KNIGHT){
            return true;
        }
    }
    if(!(xCurrent - 2 < 0 || yCurrent - 1 < 0)){
        if(isOccupiedByColor(xCurrent - 2, yCurrent - 1, enemyColor) && squareArray[xCurrent - 2][yCurrent - 1].getPiece()->getType() == KNIGHT){
            return true;
        }
    }
    if(!(xCurrent - 2 < 0 || yCurrent + 1 > 7)){
        if(isOccupiedByColor(xCurrent - 2, yCurrent + 1, enemyColor) && squareArray[xCurrent - 2][yCurrent + 1].getPiece()->getType() == KNIGHT){
            return true;
        }
    }
    if(!(xCurrent - 1 < 0 || yCurrent + 2 > 7)){
        if(isOccupiedByColor(xCurrent - 1, yCurrent + 2, enemyColor) && squareArray[xCurrent - 1][yCurrent + 2].getPiece()->getType() == KNIGHT){
            return true;
        }
    }
    
    // Verify that the king is not threatened by any other pieces
    if(!(checkLinesOfSight(xCurrent, yCurrent, enemyColor))){
        return false;
    }
    else{
        return true;
    }
}

/*------------------------------------------------------*
 * Function:    checkLinesOfSight                       *
 * Params:      int x - x position to check from        *
 *              int y - y position to check from        *
 *                                                      *
 * Returns:     bool - indicates whether the given      *
 *                     square is threatened by a        *
 *                     non-knight                       *
 * Description: returns a bool indicating whether the   *
 *              given square is threatened by a         *
*               non-knight                              *
 * -----------------------------------------------------*/
bool board::checkLinesOfSight(int x, int y, int enemyColor){
    if(this->checkNorth(x, y, enemyColor) == false
    && this->checkNorthEast(x, y, enemyColor) == false 
    && this->checkEast(x, y, enemyColor) == false 
    && this->checkSouthEast(x, y, enemyColor) == false 
    && this->checkSouth(x, y, enemyColor) == false 
    && this->checkSouthWest(x, y, enemyColor) == false 
    && this->checkWest(x, y, enemyColor) == false 
    && this->checkNorthWest(x, y, enemyColor) == false){
        return false;
    }
    else{
        return true;
    }
}

/*------------------------------------------------------*
 * Function:    checkNorth                              *
 * Params:      int x - x position to check from        *
 *              int y - y position to check from        *
 *              int enemyColor - color to look for      *
 *                                                      *
 * Returns:     bool - indicates whether the given      *
 *                     square is threatened from north  *
 * Description: returns a bool indicating whether the   *
 *              given square is threatened from north   *
 * -----------------------------------------------------*/
bool board::checkNorth(int x, int y, int enemyColor){
    if(y + 1 <= 7){
        if(squareArray[x][y + 1].getPiece() == NULL){
            return checkNorth(x, y + 1, enemyColor);
        }
        else{
            if(squareArray[x][y + 1].getPiece()->getColor() == enemyColor && squareArray[x][y + 1].getPiece()->getType() == ROOK){
                return true;
            }
            else if(squareArray[x][y + 1].getPiece()->getColor() == enemyColor && squareArray[x][y + 1].getPiece()->getType() == QUEEN){
                return true;
            }
            else{
                return false;
            }
        } 
    }
    else{
        return false;
    }
}

/*------------------------------------------------------*
 * Function:    checkNorthEast                          *
 * Params:      int x - x position to check from        *
 *              int y - y position to check from        *
 *                                                      *
 * Returns:     bool - indicates whether the given      *
 *                     square is threatened from        *
 *                     north-east                       *
 * Description: returns a bool indicating whether the   *
 *              given square is threatened  from        *
 *              north-east                              *
 * -----------------------------------------------------*/
bool board::checkNorthEast(int x, int y, int enemyColor){
    if(x + 1 <= 7 && y + 1 <= 7){
        if(squareArray[x + 1][y + 1].getPiece() == NULL){
            return checkNorthEast(x + 1, y + 1, enemyColor);
        }
        else{
            if(enemyColor == BLACK){
                if(squareArray[x + 1][y + 1].getPiece()->getColor() == enemyColor && squareArray[x + 1][y + 1].getPiece()->getType() == PAWN){
                    return true;
                }
            }
            if(squareArray[x + 1][y + 1].getPiece()->getColor() == enemyColor && squareArray[x + 1][y + 1].getPiece()->getType() == BISHOP){
                return true;
            }
            else if(squareArray[x + 1][y + 1].getPiece()->getColor() == enemyColor && squareArray[x + 1][y + 1].getPiece()->getType() == QUEEN){
                return true;
            }
            else{
                return false;
            }
        } 
    }
    else{
        return false;
    }
}

/*------------------------------------------------------*
 * Function:    checkEast                               *
 * Params:      int x - x position to check from        *
 *              int y - y position to check from        *
 *                                                      *
 * Returns:     bool - indicates whether the given      *
 *                     square is threatened from        *
 *                     east                             *
 * Description: returns a bool indicating whether the   *
 *              given square is threatened  from east   *
 * -----------------------------------------------------*/
bool board::checkEast(int x, int y, int enemyColor){
    if(x + 1 <= 7){
        if(squareArray[x + 1][y].getPiece() == NULL){
            return checkEast(x + 1, y, enemyColor);
        }
        else{
            if(squareArray[x + 1][y].getPiece()->getColor() == enemyColor && squareArray[x + 1][y].getPiece()->getType() == ROOK){
                return true;
            }
            else if(squareArray[x + 1][y].getPiece()->getColor() == enemyColor && squareArray[x + 1][y].getPiece()->getType() == QUEEN){
                return true;
            }
            else{
                return false;
            }
        } 
    }
    else{
        return false;
    }
}

/*------------------------------------------------------*
 * Function:    checkSouthEast                          *
 * Params:      int x - x position to check from        *
 *              int y - y position to check from        *
 *                                                      *
 * Returns:     bool - indicates whether the given      *
 *                     square is threatened from        *
 *                     south-east                       *
 * Description: returns a bool indicating whether the   *
 *              given square is threatened from         *
 *              south-east                              *
 * -----------------------------------------------------*/
bool board::checkSouthEast(int x, int y, int enemyColor){
    if(x + 1 <= 7 && y - 1 >= 0){
        if(squareArray[x + 1][y - 1].getPiece() == NULL){
            return checkSouthEast(x + 1, y - 1, enemyColor);
        }
        else{
            if(enemyColor == WHITE){
                if(squareArray[x + 1][y - 1].getPiece()->getColor() == enemyColor && squareArray[x + 1][y - 1].getPiece()->getType() == PAWN){
                    return true;
                }
            }
            if(squareArray[x + 1][y - 1].getPiece()->getColor() == enemyColor && squareArray[x + 1][y - 1].getPiece()->getType() == BISHOP){
                return true;
            }
            else if(squareArray[x + 1][y - 1].getPiece()->getColor() == enemyColor && squareArray[x + 1][y - 1].getPiece()->getType() == QUEEN){
                return true;
            }
            else{
                return false;
            }
        } 
    }
    else{
        return false;
    }
}

/*------------------------------------------------------*
 * Function:    checkSouth                              *
 * Params:      int x - x position to check from        *
 *              int y - y position to check from        *
 *                                                      *
 * Returns:     bool - indicates whether the given      *
 *                     square is threatened from south  *
 * Description: returns a bool indicating whether the   *
 *              given square is threatened from south   *
 * -----------------------------------------------------*/
bool board::checkSouth(int x, int y, int enemyColor){
    if(y - 1 >= 0){
        if(squareArray[x][y - 1].getPiece() == NULL){
            return checkSouth(x, y - 1, enemyColor);
        }
        else{
            if(squareArray[x][y - 1].getPiece()->getColor() == enemyColor && squareArray[x][y - 1].getPiece()->getType() == ROOK){
                return true;
            }
            else if(squareArray[x][y - 1].getPiece()->getColor() == enemyColor && squareArray[x][y - 1].getPiece()->getType() == QUEEN){
                return true;
            }
            else{
                return false;
            }
        } 
    }
    else{
        return false;
    }
}

/*------------------------------------------------------*
 * Function:    checkSouthWest                          *
 * Params:      int x - x position to check from        *
 *              int y - y position to check from        *
 *                                                      *
 * Returns:     bool - indicates whether the given      *
 *                     square is threatened from        *
 *                     south-west                       *
 * Description: returns a bool indicating whether the   *
 *              given square is threatened from         *
 *              south-west                              *
 * -----------------------------------------------------*/
bool board::checkSouthWest(int x, int y, int enemyColor){
    if(x - 1 >= 0 && y - 1 >= 0){
        if(squareArray[x - 1][y - 1].getPiece() == NULL){
            return checkSouthWest(x - 1, y - 1, enemyColor);
        }
        else{
            if(enemyColor == WHITE){
                if(squareArray[x - 1][y - 1].getPiece()->getColor() == enemyColor && squareArray[x - 1][y - 1].getPiece()->getType() == PAWN){
                    return true;
                }
            }
            if(squareArray[x - 1][y - 1].getPiece()->getColor() == enemyColor && squareArray[x - 1][y - 1].getPiece()->getType() == BISHOP){
                return true;
            }
            else if(squareArray[x - 1][y - 1].getPiece()->getColor() == enemyColor && squareArray[x - 1][y - 1].getPiece()->getType() == QUEEN){
                return true;
            }
            else{
                return false;
            }
        } 
    }
    else{
        return false;
    }
}

/*------------------------------------------------------*
 * Function:    checkWest                               *
 * Params:      int x - x position to check from        *
 *              int y - y position to check from        *
 *                                                      *
 * Returns:     bool - indicates whether the given      *
 *                     square is threatened from        *
 *                     west                             *
 * Description: returns a bool indicating whether the   *
 *              given square is threatened from west    *
 * -----------------------------------------------------*/
bool board::checkWest(int x, int y, int enemyColor){
    if(x - 1 >= 0){
        if(squareArray[x - 1][y].getPiece() == NULL){
            return checkWest(x - 1, y, enemyColor);
        }
        else{
            if(squareArray[x - 1][y].getPiece()->getColor() == enemyColor && squareArray[x - 1][y].getPiece()->getType() == ROOK){
                return true;
            }
            else if(squareArray[x - 1][y].getPiece()->getColor() == enemyColor && squareArray[x - 1][y].getPiece()->getType() == QUEEN){
                return true;
            }
            else{
                return false;
            }
        } 
    }
    else{
        return false;
    }
}

/*------------------------------------------------------*
 * Function:    checkNorthWest                          *
 * Params:      int x - x position to check from        *
 *              int y - y position to check from        *
 *                                                      *
 * Returns:     bool - indicates whether the given      *
 *                     square is threatened from        *
 *                     north-west                       *
 * Description: returns a bool indicating whether the   *
 *              given square is threatened from         *
 *              north-west                              *
 * -----------------------------------------------------*/
bool board::checkNorthWest(int x, int y, int enemyColor){
    if(x - 1 >= 0 && y + 1 <= 7){
        if(squareArray[x - 1][y + 1].getPiece() == NULL){
            return checkNorthWest(x - 1, y + 1, enemyColor);
        }
        else{
            if(enemyColor == BLACK){
                if(squareArray[x - 1][y + 1].getPiece()->getColor() == enemyColor && squareArray[x - 1][y + 1].getPiece()->getType() == PAWN){
                    return true;
                }
            }
            if(squareArray[x - 1][y + 1].getPiece()->getColor() == enemyColor && squareArray[x - 1][y + 1].getPiece()->getType() == BISHOP){
                return true;
            }
            else if(squareArray[x - 1][y + 1].getPiece()->getColor() == enemyColor && squareArray[x - 1][y + 1].getPiece()->getType() == QUEEN){
                return true;
            }
            else{
                return false;
            }
        } 
    }
    else{
        return false;
    }
}

/*------------------------------------------------------*
 * Function:    move                                    *
 * Params:      int xCurrent - current x position to    *
 *                             move from                *
 *              int yCurrent - current y position to    *
 *                             move from                *
 *              int xNew - new x position to move to    *
 *              int yNew - new y position to move to    *
 *                                                      *
 * Returns:     board* - pointer to the board with the  *
 *                       potential move made            *
 * Description: returns a pointer to a board on which a *
 *              move has been made                      *
 * -----------------------------------------------------*/
board *board::move(int xCurrent, int yCurrent, int xNew, int yNew){
    bool myColor = squareArray[xCurrent][yCurrent].getPiece()->getColor();
    if(this->isOccupiedByColor(xNew, yNew, !myColor)){
        this->capture(xCurrent, yCurrent, xNew, yNew);
    }
    squareArray[xCurrent][yCurrent].getPiece()->setCoords(xNew, yNew);
    squareArray[xNew][yNew].setPiece(squareArray[xCurrent][yCurrent].getPiece());
    squareArray[xCurrent][yCurrent].setPiece(NULL);
    if (this->getSquare(xNew, yNew)->getPiece()->getType() == PAWN ||
        this->getSquare(xNew, yNew)->getPiece()->getType() == KING ||
        this->getSquare(xNew, yNew)->getPiece()->getType() == ROOK){
            this->getSquare(xNew, yNew)->getPiece()->moved();
        }
    return this;
}

/*------------------------------------------------------*
 * Function:    capture                                 *
 * Params:      int xCurrent - current x position to    *
 *                             move from                *
 *              int yCurrent - current y position to    *
 *                             move from                *
 *              int xNew - new x position to move to    *
 *              int yNew - new y position to move to    *
 *                                                      *
 * Returns:     void                                    *
 * Description: adds the piece being captured to the    *
 *              list of captured pieces                 *
 * -----------------------------------------------------*/
void board::capture(int xCurrent, int yCurrent, int xNew, int yNew){
    int myColor = squareArray[xCurrent][yCurrent].getPiece()->getColor();
    int pieceBeingCaptured = squareArray[xNew][yNew].getPiece()->getType();

    // Insert piece being captured into the list of captured pieces
    if(myColor){
        whiteCaptures.insert(pieceBeingCaptured);
    }
    else{
        blackCaptures.insert(pieceBeingCaptured);
    }
}

/*------------------------------------------------------*
 * Function:    isCheckmate                             *
 * Params:      int color - color of king to check      *
 *                                                      *
 * Returns:     bool - indicates whether the king of    *
 *                     the given color is checkmated    *
 * Description: returns a bool indicating if the given  *
 *              color's king is in a checkmate position *
 * -----------------------------------------------------*/
bool board::isCheckmate(int color){
    piece *king;
    int xIter, yIter, xCurrent, yCurrent;
    bool breakFlag = false;
    // Iterate over the board and find the king to inspect
    if(isChecked(color)){
        for(int x = 0; x < 8; x++){
            for(int y = 0; y < 8; y++){
                if(isOccupiedByPiece(x, y, KING) && isOccupiedByColor(x, y, color)){
                    king = this->getSquare(x,y)->getPiece();
                    xCurrent = x;
                    yCurrent = y;
                    breakFlag = true;
                }
            }
            if(breakFlag){
                break;
            }
        }
    // Iterate over kings adjacent squares to see if he can move to any of them
    for(xIter = xCurrent - 1; xIter < (xCurrent + 2); xIter++){
        for(yIter = yCurrent - 1; yIter < (yCurrent + 2); yIter++){
            if(king->canMove(xIter, yIter, this)){
                return false;
            }
        }
    }
    // Brute force check if theres a way to block
    // Iterate over the board
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            // Find all squares with friendly pieces
            if(isOccupiedByColor(x, y, color) && this->getSquare(x,y)->getPiece()->getType() != KING){
                // Iterate over the board
                for(int i = 0; i < 8; i++){
                    for(int j = 0; j < 8; j++){
                        // See if they can move to any of the other squares
                        if(this->getSquare(x,y)->getPiece()->canMove(i, j, this)){
                            board *testBoard;
                            testBoard = copyBoard(this);
                            testBoard->move(x, y, i, j);
                            // If they can see if check goes away
                            if(!(testBoard->isChecked(color))){
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
    }
    else{
        return false;
    }
}

/*------------------------------------------------------*
 * Function:    printBoard                              *
 * Params:      board theBoard - pointer to the current *
 *                               board                  *
 * Returns:     string - string to visually represent   *
 *                       the board's current state      *
 * Description: returns a string of ASCII characters to *
 *              enable display of the board
 * -----------------------------------------------------*/
void board::printBoard(){
    string stringToPrint;

    string pieces[8][8];
    // Iterate over the board and populate the pieces array with appropriate strings
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            if(this->getSquare(x,y)->getPiece() != NULL){
                if(this->getSquare(x,y)->getPiece()->getColor() == WHITE){
                    pieces[x][y] = "W";
                }
                else{
                    pieces[x][y] = "B";
                }
                    switch(this->getSquare(x,y)->getPiece()->getType()){
                        case PAWN:
                            pieces[x][y] += "P";
                            break;
                        case ROOK:
                            pieces[x][y] += "R";
                            break;
                        case KNIGHT:
                            pieces[x][y] += "N";
                            break;
                        case BISHOP:
                            pieces[x][y] += "B";
                            break;
                        case QUEEN:
                            pieces[x][y] += "Q";
                            break;
                        case KING:
                            pieces[x][y] += "K";
                            break;
                    }
            }
            else{
                pieces[x][y] = "  "; // empty squares get 2 space characters to hold the space
            }
        }
    }

    stringToPrint =  "#########################################################################\n";
    stringToPrint += "#        #        #        #        #        #        #        #        #\n";
    stringToPrint += "8   " + pieces[0][7] + "   #   " + pieces[1][7] + "   #   " + pieces[2][7] + "   #   " + pieces[3][7] + "   #   " + pieces[4][7] + "   #   " + pieces[5][7] + "   #   " + pieces[6][7] + "   #   " + pieces[7][7] + "   #\n";
    stringToPrint += "#        #        #        #        #        #        #        #        #\n";
    stringToPrint += "#########################################################################\n";
    stringToPrint += "#        #        #        #        #        #        #        #        #\n";
    stringToPrint += "7   " + pieces[0][6] + "   #   " + pieces[1][6] + "   #   " + pieces[2][6] + "   #   " + pieces[3][6] + "   #   " + pieces[4][6] + "   #   " + pieces[5][6] + "   #   " + pieces[6][6] + "   #   " + pieces[7][6] + "   #\n";
    stringToPrint += "#        #        #        #        #        #        #        #        #\n";
    stringToPrint += "#########################################################################\n";
    stringToPrint += "#        #        #        #        #        #        #        #        #\n";
    stringToPrint += "6   " + pieces[0][5] + "   #   " + pieces[1][5] + "   #   " + pieces[2][5] + "   #   " + pieces[3][5] + "   #   " + pieces[4][5] + "   #   " + pieces[5][5] + "   #   " + pieces[6][5] + "   #   " + pieces[7][5] + "   #\n";
    stringToPrint += "#        #        #        #        #        #        #        #        #\n";
    stringToPrint += "#########################################################################\n";
    stringToPrint += "#        #        #        #        #        #        #        #        #\n";
    stringToPrint += "5   " + pieces[0][4] + "   #   " + pieces[1][4] + "   #   " + pieces[2][4] + "   #   " + pieces[3][4] + "   #   " + pieces[4][4] + "   #   " + pieces[5][4] + "   #   " + pieces[6][4] + "   #   " + pieces[7][4] + "   #\n";
    stringToPrint += "#        #        #        #        #        #        #        #        #\n";
    stringToPrint += "#########################################################################\n";
    stringToPrint += "#        #        #        #        #        #        #        #        #\n";
    stringToPrint += "4   " + pieces[0][3] + "   #   " + pieces[1][3] + "   #   " + pieces[2][3] + "   #   " + pieces[3][3] + "   #   " + pieces[4][3] + "   #   " + pieces[5][3] + "   #   " + pieces[6][3] + "   #   " + pieces[7][3] + "   #\n";
    stringToPrint += "#        #        #        #        #        #        #        #        #\n";
    stringToPrint += "#########################################################################\n";
    stringToPrint += "#        #        #        #        #        #        #        #        #\n";
    stringToPrint += "3   " + pieces[0][2] + "   #   " + pieces[1][2] + "   #   " + pieces[2][2] + "   #   " + pieces[3][2] + "   #   " + pieces[4][2] + "   #   " + pieces[5][2] + "   #   " + pieces[6][2] + "   #   " + pieces[7][2] + "   #\n";
    stringToPrint += "#        #        #        #        #        #        #        #        #\n";
    stringToPrint += "#########################################################################\n";
    stringToPrint += "#        #        #        #        #        #        #        #        #\n";
    stringToPrint += "2   " + pieces[0][1] + "   #   " + pieces[1][1] + "   #   " + pieces[2][1] + "   #   " + pieces[3][1] + "   #   " + pieces[4][1] + "   #   " + pieces[5][1] + "   #   " + pieces[6][1] + "   #   " + pieces[7][1] + "   #\n";
    stringToPrint += "#        #        #        #        #        #        #        #        #\n";
    stringToPrint += "#########################################################################\n";
    stringToPrint += "#        #        #        #        #        #        #        #        #\n";
    stringToPrint += "1   " + pieces[0][0] + "   #   " + pieces[1][0] + "   #   " + pieces[2][0] + "   #   " + pieces[3][0] + "   #   " + pieces[4][0] + "   #   " + pieces[5][0] + "   #   " + pieces[6][0] + "   #   " + pieces[7][0] + "   #\n";
    stringToPrint += "#        #        #        #        #        #        #        #        #\n";
    stringToPrint += "####A########B########C########D########E########F########G########H#####\n";
                            
    cout << stringToPrint << endl;
}
// Piece Implementation

/*------------------------------------------------------*
 * Function:    initPiece                               *
 * Params:      int color - color to init the piece to  *
 *              int x - x position to init the piece to *
 *              int y - y position to init the piece to *
 * Returns:     Void                                    *
 * Description: populates the member data of a piece    *
 *              object                                  *
 * -----------------------------------------------------*/
void piece::initPiece(int color, int x, int y, int type){
    this->color = color;
    this->x = x;
    this->y = y;
    this->type = type;
}

// Derived Piece Implementation

/*------------------------------------------------------*
 * Function:    king::canMove                           *
 * Params:      int xNew - new x position to move piece *
 *                         to                           *
 *              int yNew - new y position to move piece *
 *                         to                           *
 *              board theBoard - the board object to    *
 *                               check on               *
 * Returns:     bool - indicates if a piece can move to *
 *                     the given position               *
 * Description: checks if a given move can be made by   *
 *              the king                                *
 * -----------------------------------------------------*/
bool king::canMove(int xNew, int yNew, board *theBoard){
    int xCurrent = getXCoord();
    int yCurrent = getYCoord();
    int xDelta = abs(xNew - xCurrent);
    int yDelta = abs(yNew - yCurrent);

    // Verify that the new location is a valid board location
    if(xNew < 0 || yNew < 0 || xNew > 7 || yNew > 7){
        return false;
    }
    // Verify that the new square is not occupied by a friendly piece 
    if(theBoard->getSquare(xNew, yNew)->getPiece() != NULL){
        if(theBoard->getSquare(xNew, yNew)->getPiece()->getColor() == getColor()){
            return false;
        }
    }
    // Verify that the new square is within reach of the king
    if(xDelta == 0 && yDelta == 0){
        return false; // Cannot move to the same space 
    }
    if(xDelta >= 2 || yDelta >= 2){
        return false; // Cannot move more than one space
    }
    // If nothing else has returned false check if the new location puts the king in check
    else{
        board *testBoard = copyBoard(theBoard);
        testBoard->move(xCurrent,yCurrent, xNew, yNew);

        // Verify that the new square is not threatened by an enemy piece
        if(testBoard->isChecked(theBoard->getSquare(xCurrent,yCurrent)->getPiece()->getColor())){
            return false;
        }
    }

    // If the move hasn't been invalidated by now then it must be valid
    return true;
}

/*------------------------------------------------------*
 * Function:    queen::canMove                          *
 * Params:      int xNew - new x position to move piece *
 *                         to                           *
 *              int yNew - new y position to move piece *
 *                         to                           *
 *              board theBoard - the board object to    *
 *                               check on               *
 * Returns:     bool - indicates if a piece can move to *
 *                     the given position               *
 * Description: checks if a given move can be made by   *
 *              the queen                               *
 * -----------------------------------------------------*/
bool queen::canMove(int xNew, int yNew, board *theBoard){
    int xCurrent = getXCoord();
    int yCurrent = getYCoord();
    int xDelta = abs(xNew - xCurrent);
    int yDelta = abs(yNew - yCurrent);

    // Verify that the new location is a valid board location
    if(xNew < 0 || yNew < 0 || xNew > 7 || yNew > 7){
        return false;
    }
    // Verify that the new location does not place the friendly king in check
    board *testBoard = copyBoard(theBoard);
    testBoard->move(xCurrent,yCurrent, xNew, yNew);
    if(testBoard->isChecked(theBoard->getSquare(xCurrent, yCurrent)->getPiece()->getColor())){
        return false;
    }
    // Verify that the new square is not occupied by a friendly piece
    if(theBoard->getSquare(xNew, yNew)->getPiece() != NULL){
        if(theBoard->getSquare(xNew, yNew)->getPiece()->getColor() == getColor()){
            return false;
        }
    }
    // Verify that the new Square is within reach of the queen
    if(xDelta == 0 && yDelta == 0){
        return false; // Cannot move to the same space 
    }
    if(xDelta != yDelta && xDelta != 0 && yDelta != 0){
        return false; // If not lateral, both deltas must have same magnitude to stay on the correct diagonal
    }
    // Verify that no pieces are in the path of movement between the current and new squares
    if(xNew - xCurrent > 0 && yNew - yCurrent == 0){ // moving east
        for(int x = xCurrent + 1; x < xNew; x++){
            if(theBoard->getSquare(x, yCurrent)->getPiece() != NULL){
                return false;
            }
        }
    }
    if(xNew - xCurrent < 0 && yNew - yCurrent == 0){ // moving west
        for(int x = xCurrent - 1; x > xNew; x--){
            if(theBoard->getSquare(x, yCurrent)->getPiece() != NULL){
                return false;
            }
        }
    }
    if(xNew - xCurrent == 0 && yNew - yCurrent > 0){ // moving north
        for(int y = yCurrent + 1; y < yNew; y++){
            if(theBoard->getSquare(xCurrent, y)->getPiece() != NULL){
                return false;
            }
        }
    }
    if(xNew - xCurrent == 0 && yNew - yCurrent < 0){ // moving south
        for(int y = yCurrent - 1; y > yNew; y--){
            if(theBoard->getSquare(xCurrent, y)->getPiece() != NULL){
                return false;
            }
        }
    }
    if(xNew - xCurrent > 0 && yNew - yCurrent > 0){ // moving northeast
        int x = xCurrent + 1;
        int y = yCurrent + 1;
        for(int it = 0; it < xDelta; it++){
            if(theBoard->getSquare(x, y)->getPiece() != NULL){
                return false;
            }
            xCurrent++;
            yCurrent++;
        }
    }
    if(xNew - xCurrent > 0 && yNew - yCurrent < 0){ // moving southeast
        int x = xCurrent + 1;
        int y = yCurrent - 1;
        for(int it = 0; it < xDelta; it++){
            if(theBoard->getSquare(x, y)->getPiece() != NULL){
                return false;
            }
            xCurrent++;
            yCurrent--;
        }
    }
    if(xNew - xCurrent < 0 && yNew - yCurrent > 0 && xDelta == yDelta){ // moving northwest
        int x = xCurrent - 1;
        int y = yCurrent + 1;
        for(int it = 0; it < xDelta; it++){
            if(theBoard->getSquare(x, y)->getPiece() != NULL){
                return false;
            }
            xCurrent--;
            yCurrent++;
        }
    }
    if(xNew - xCurrent < 0 && yNew - yCurrent < 0 && xDelta == yDelta){ // moving southwest
        int x = xCurrent - 1;
        int y = yCurrent - 1;
        for(int it = 0; it < xDelta; it++){
            if(theBoard->getSquare(x, y)->getPiece() != NULL){
                return false;
            }
            xCurrent--;
            yCurrent--;
        }
    }    
    
    // If the move hasn't been invalidated by now then it must be valid
    return true;
}

/*------------------------------------------------------*
 * Function:    bishop::canMove                         *
 * Params:      int xNew - new x position to move piece *
 *                         to                           *
 *              int yNew - new y position to move piece *
 *                         to                           *
 *              board theBoard - the board object to    *
 *                               check on               *
 * Returns:     bool - indicates if a piece can move to *
 *                     the given position               *
 * Description: checks if a given move can be made by   *
 *              the bishop                              *
 * -----------------------------------------------------*/
bool bishop::canMove(int xNew, int yNew, board *theBoard){
    int xCurrent = getXCoord();
    int yCurrent = getYCoord();
    int xDelta = abs(xNew - xCurrent);
    int yDelta = abs(yNew - yCurrent);

    // Verify that the new location is a valid board location
    if(xNew < 0 || yNew < 0 || xNew > 7 || yNew > 7){
        return false;
    }
    // Verify that the new location does not place the friendly king in check
    board *testBoard = copyBoard(theBoard);
    testBoard->move(xCurrent,yCurrent, xNew, yNew);
    if(testBoard->isChecked(theBoard->getSquare(xCurrent, yCurrent)->getPiece()->getColor())){
        return false;
    }
    // Verify that the new square is not occupied by a friendly piece
    if(theBoard->getSquare(xNew, yNew)->getPiece() != NULL){
        if(theBoard->getSquare(xNew, yNew)->getPiece()->getColor() == getColor()){
            return false;
        }
    }
    // Verify that the new Square is within reach of the bishop
    if(xDelta == 0 || yDelta == 0){
        return false; // Cannot move to the same space or laterally
    }
    // Both deltas must have same magnitude to stay on the correct diagonal
    if(xDelta != yDelta){
        return false;
    }
    // Verify that there is not another piece obstructing the path between the current and new squares
    if(xNew - xCurrent > 0 && yNew - yCurrent > 0){ // moving northeast
        int x = xCurrent + 1;
        int y = yCurrent + 1;
        for(int it = 0; it < xDelta; it++){
            if(theBoard->getSquare(x, y)->getPiece() != NULL){
                return false;
            }
            xCurrent++;
            yCurrent++;
        }
    }
    if(xNew - xCurrent > 0 && yNew - yCurrent < 0){ // moving southeast
        int x = xCurrent + 1;
        int y = yCurrent - 1;
        for(int it = 0; it < xDelta; it++){
            if(theBoard->getSquare(x, y)->getPiece() != NULL){
                return false;
            }
            xCurrent++;
            yCurrent--;
        }
    }
    if(xNew - xCurrent < 0 && yNew - yCurrent > 0 && xDelta == yDelta){ // moving northwest
        int x = xCurrent - 1;
        int y = yCurrent + 1;
        for(int it = 0; it < xDelta; it++){
            if(theBoard->getSquare(x, y)->getPiece() != NULL){
                return false;
            }
            xCurrent--;
            yCurrent++;
        }
    }
    if(xNew - xCurrent < 0 && yNew - yCurrent < 0 && xDelta == yDelta){ // moving southwest
        int x = xCurrent - 1;
        int y = yCurrent - 1;
        for(int it = 0; it < xDelta; it++){
            if(theBoard->getSquare(x, y)->getPiece() != NULL){
                return false;
            }
            xCurrent--;
            yCurrent--;
        }
    }
    // If the move hasn't been invalidated by now then it must be valid
    return true;
}

/*------------------------------------------------------*
 * Function:    knight::canMove                         *
 * Params:      int xNew - new x position to move piece *
 *                         to                           *
 *              int yNew - new y position to move piece *
 *                         to                           *
 *              board theBoard - the board object to    *
 *                               check on               *
 * Returns:     bool - indicates if a piece can move to *
 *                     the given position               *
 * Description: checks if a given move can be made by   *
 *              the knight                              *
 * -----------------------------------------------------*/
bool knight::canMove(int xNew, int yNew, board *theBoard){
    int xCurrent = getXCoord();
    int yCurrent = getYCoord();
    int xDelta = abs(xNew - xCurrent);
    int yDelta = abs(yNew - yCurrent);

    // Verify that the new location is a valid board location
    if(xNew < 0 || yNew < 0 || xNew > 7 || yNew > 7){
        return false;
    }
    // Verify that the new location does not place the friendly king in check
    board *testBoard = copyBoard(theBoard);
    testBoard->move(xCurrent,yCurrent, xNew, yNew);
    if(testBoard->isChecked(theBoard->getSquare(xCurrent, yCurrent)->getPiece()->getColor())){
        return false;
    }
    // Verify that the new square is not occupied by a friendly piece
    if(theBoard->getSquare(xNew, yNew)->getPiece() != NULL){
        if(theBoard->getSquare(xNew, yNew)->getPiece()->getColor() == getColor()){
            return false;
        }
    }
    // Verify that the new Square is within reach of the knight
    if(xDelta == 0 || yDelta == 0){
        return false; // Cannot move to the same space or laterally
    }
    if(xDelta == 2 && yDelta == 1){
        return true;
    }
    else if(xDelta == 1 && yDelta == 2){
        return true;
    }
    else{
        return false;
    }
}

/*------------------------------------------------------*
 * Function:    rook::canMove                           *
 * Params:      int xNew - new x position to move piece *
 *                         to                           *
 *              int yNew - new y position to move piece *
 *                         to                           *
 *              board theBoard - the board object to    *
 *                               check on               *
 * Returns:     bool - indicates if a piece can move to *
 *                     the given position               *
 * Description: checks if a given move can be made by   *
 *              the rook                                *
 * -----------------------------------------------------*/
bool rook::canMove(int xNew, int yNew, board *theBoard){
    int xCurrent = getXCoord();
    int yCurrent = getYCoord();
    int xDelta = abs(xNew - xCurrent);
    int yDelta = abs(yNew - yCurrent);

    // Verify that the new location is a valid board location
    if(xNew < 0 || yNew < 0 || xNew > 7 || yNew > 7){
        return false;
    }
    // Verify that the new location does not place the friendly king in check
    board *testBoard = copyBoard(theBoard);
    testBoard->move(xCurrent,yCurrent, xNew, yNew);
    if(testBoard->isChecked(theBoard->getSquare(xCurrent, yCurrent)->getPiece()->getColor())){
        return false;
    }
    // Verify that the new square is not occupied by a friendly piece
    if(theBoard->getSquare(xNew, yNew)->getPiece() != NULL){
        if(theBoard->getSquare(xNew, yNew)->getPiece()->getColor() == getColor()){
            return false;
        }
    }
    // Verify that the new Square is within reach of the rook
    if(xDelta == 0 && yDelta == 0){
        return false; // Cannot move to the same space 
    }
    else if(xDelta != 0 && yDelta != 0){
        return false; // Rook must stay on one row/column, so one of the deltas must be 0
    }
    // Verify that there is not another piece obstructing the path between the current and new squares
    if(xNew - xCurrent > 0 && yNew - yCurrent == 0){ // moving east
        for(int x = xCurrent + 1; x < xNew; x++){
            if(theBoard->getSquare(x, yCurrent)->getPiece() != NULL){
                return false;
            }
        }
    }
    if(xNew - xCurrent < 0 && yNew - yCurrent == 0){ // moving west
        for(int x = xCurrent - 1; x > xNew; x--){
            if(theBoard->getSquare(x, yCurrent)->getPiece() != NULL){
                return false;
            }
        }
    }
    if(xNew - xCurrent == 0 && yNew - yCurrent > 0){ // moving north
        for(int y = yCurrent + 1; y < yNew; y++){
            if(theBoard->getSquare(xCurrent, y)->getPiece() != NULL){
                return false;
            }
        }
    }
    if(xNew - xCurrent == 0 && yNew - yCurrent < 0){ // moving south
        for(int y = yCurrent - 1; y > yNew; y--){
            if(theBoard->getSquare(xCurrent, y)->getPiece() != NULL){
                return false;
            }
        }
    }
    // If the move hasn't been invalidated by now then it must be valid
    return true;
}

/*------------------------------------------------------*
 * Function:    pawn::canMove                           *
 * Params:      int xNew - new x position to move piece *
 *                         to                           *
 *              int yNew - new y position to move piece *
 *                         to                           *
 *              board theBoard - the board to check on  *
 * Returns:     bool - indicates if a piece can move to *
 *                     the given position               *
 * Description: checks if a given move can be made by   *
 *              the pawn                                *
 * -----------------------------------------------------*/
bool pawn::canMove(int xNew, int yNew, board *theBoard){
    int xCurrent = getXCoord();
    int yCurrent = getYCoord();
    int xDelta = xNew - xCurrent;
    int yDelta = yNew - yCurrent;

    // Verify that the new location is a valid board location
    if(xNew < 0 || yNew < 0 || xNew > 7 || yNew > 7){
        return false;
    }
    // Verify that the new location does not place the friendly king in check
    board *testBoard = copyBoard(theBoard);
    testBoard->move(xCurrent,yCurrent, xNew, yNew);
    if(testBoard->isChecked(theBoard->getSquare(xCurrent, yCurrent)->getPiece()->getColor())){
        return false;
    }
    // Verify that the new square is not occupied by a friendly piece
    if(theBoard->getSquare(xNew, yNew)->getPiece() != NULL){
        if(theBoard->getSquare(xNew, yNew)->getPiece()->getColor() == getColor()){
            return false;
        }
    }
    if(xDelta == 0 && yDelta == 0){
        return false; // Cannot move to the same space or laterally
    }
    // Verify that the new Square is within reach of the pawn
    int myColor = getColor();
    if(myColor == WHITE){
        if(xDelta == 1 && yDelta == 1 && theBoard->isOccupiedByColor(xNew,yNew,BLACK)){
            return true; // Capturing
        }
        else if(xDelta == -1 && yDelta == 1 && theBoard->isOccupiedByColor(xNew,yNew,BLACK)){
            return true; // Capturing
        }
        else if(xDelta == 0 && yDelta == 1 && !(theBoard->isOccupied(xNew, yNew))){
            return true; 
        }
        else if(xDelta == 0 && yDelta == 2 && !hasMoved && !(theBoard->isOccupied(xNew, yNew)) && !(theBoard->isOccupied(xNew, yNew - 1))){
            return true; // First move allows the pawn to move 2 squares
        }
        else{
            return false;
        }
    }
    else{
        if(xDelta == -1 && yDelta == -1 && theBoard->isOccupiedByColor(xNew,yNew,WHITE)){
            return true; // Capturing
        }
        else if(xDelta == 1 && yDelta == -1 && theBoard->isOccupiedByColor(xNew,yNew,WHITE)){
            return true; // Capturing
        }
        else if(xDelta == 0 && yDelta == -1 && !(theBoard->isOccupied(xNew, yNew))){
            return true; 
        }
        else if(xDelta == 0 && yDelta == -2 && !hasMoved && !theBoard->isOccupied(xNew, yNew) && !theBoard->isOccupied(xNew, yNew + 1)){
            return true; // First move allows the pawn to move 2 squares
        }
        else{
            return false;
        }
    }
}