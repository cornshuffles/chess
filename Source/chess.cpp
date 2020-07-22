#include "chess.h"
#include <cstdlib>

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
                switch (x){
                    case 0:
                    case 7:{
                    // Rooks
                        rook whiteRook;
                        whiteRook.initPiece(WHITE, x, y, ROOK);
                        squareArray[x][y].initSquare(x, y, &whiteRook);
                    break;}
                    case 1:
                    case 6:{
                    // Knights
                        knight whiteKnight;
                        whiteKnight.initPiece(WHITE, x, y, KNIGHT);
                        squareArray[x][y].initSquare(x, y, &whiteKnight);
                    break;}
                    case 2:
                    case 5:{
                    // Bishops
                        bishop whiteBishop;
                        whiteBishop.initPiece(WHITE, x, y, BISHOP);
                        squareArray[x][y].initSquare(x, y, &whiteBishop);
                    break;}
                    case 3:{
                    // Queen
                        queen whiteQueen;
                        whiteQueen.initPiece(WHITE, x, y, QUEEN);
                        squareArray[x][y].initSquare(x, y, &whiteQueen);
                    break;}
                    case 4:{
                    // King
                        king whiteKing;
                        whiteKing.initPiece(WHITE, x, y, KING);
                        squareArray[x][y].initSquare(x, y, &whiteKing);
                    break;}
                    
                }
            }
            // Black home row
            else if(y == 7){
                switch (x){
                    case 0:
                    case 7:{
                    // Rooks
                        rook blackRook;
                        blackRook.initPiece(BLACK, x, y, ROOK);
                        squareArray[x][y].initSquare(x, y, &blackRook);
                        break;}
                    case 1:
                    case 6:{
                    // Knights
                        knight blackKnight;
                        blackKnight.initPiece(BLACK, x, y, KNIGHT);
                        squareArray[x][y].initSquare(x, y, &blackKnight);
                        break;}
                    case 2:
                    case 5:{
                    // Bishops
                        bishop blackBishop;
                        blackBishop.initPiece(BLACK, x, y, BISHOP);
                        squareArray[x][y].initSquare(x, y, &blackBishop);
                        break;}
                    case 3:{
                    // Queen
                        queen blackQueen;
                        blackQueen.initPiece(BLACK, x, y, QUEEN);
                        squareArray[x][y].initSquare(x, y, &blackQueen);
                        break;}
                    case 4:{
                    // King
                        king blackKing;
                        blackKing.initPiece(BLACK, x, y, KING);
                        squareArray[x][y].initSquare(x, y, &blackKing);
                        break;}
                    
                }
            }
            // All y=1 squares get initialized with a white pawn
            else if(y == 1){
                pawn whitePawn;
                whitePawn.initPiece(WHITE, x, y, PAWN);
                squareArray[x][y].initSquare(x, y, &whitePawn);
            }
            // All y=6 squares get initialized with a black pawn
            else if(y == 6){
                pawn blackPawn;
                blackPawn.initPiece(BLACK, x, y, PAWN);
                squareArray[x][y].initSquare(x, y, &blackPawn);
            }
            else{
                squareArray[x][y].initSquare(x, y, NULL);
            }
        }
    }
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
bool isOccupied(int x, int y){
    if(squareArray[x][y].piece == NULL){
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
bool isOccupiedByColor(int x, int y, int color){
    if(squareArray[x][y].piece == NULL){
        return false;
    }
    else if{squareArray[x][y].piece.getColor() == color){
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
bool isOccupiedByPiece(int x, int y, int type){
    if(squareArray[x][y].piece == NULL){
        return false;
    }
    else if{squareArray[x][y].piece.getType() == type){
        return true;
    }
    else{
        return false;
    }       
}

/*------------------------------------------------------*
 * Function:    isChecked                               *
 * Params:      int color - color of king to check      *
 *              board theBoard - board to check         *
 *                                                      *
 * Returns:     bool - indicates whether the king of    *
 *                     the given color is in check on   *
 *                     the given board                  *
 * Description: returns a bool indicating if the given  *
 *              color's king is in check on the given   *
 *              board                                   *
 * -----------------------------------------------------*/
bool isChecked(int color, board *theBoard){
    int xCurrent, yCurrent; // Current position of the specified king
    for(int x = 0; x < 7; x++){
        for(int y = 0; y < 7; y++){
            if(theBoard->squareArray[x][y].piece.getType() == KING && theBoard->squareArray[x][y].piece.getColor() == color){
                xCurrent = x;
                yCurrent = y; 
            }
        }
    }
     // First verify that the new square is not threatened by knights
     if(!(xCurrent + 1 > 7) || !(yCurrent + 2 > 7)){
        if(theBoard->squareArray[xCurrent + 1][yCurrent + 2].piece.getType() == KNIGHT){
            return false;
        }
    }
    if(!(xCurrent + 2 > 7) || !(yCurrent + 1 > 7)){
        if(theBoard->squareArray[xCurrent + 2][yCurrent + 1].piece.getType() == KNIGHT){
            return false;
        }
    }
    if(!(xCurrent + 2 > 7) || !(yCurrent - 1 < 0)){
        if(theBoard->squareArray[xCurrent + 2][yCurrent - 1].piece.getType() == KNIGHT){
            return false;
        }
    }
    if(!(xCurrent + 1 > 7) || !(yCurrent - 2 < 0)){
        if(theBoard->squareArray[xCurrent + 1][yCurrent - 2].piece.getType() == KNIGHT){
            return false;
        }
    }
    if(!(xCurrent - 1 < 0) || !(yCurrent - 2 < 0)){
        if(theBoard->squareArray[xCurrent - 1][yCurrent - 2].piece.getType() == KNIGHT){
            return false;
        }
    }
    if(!(xCurrent - 2 < 0) || !(yCurrent - 1 < 0)){
        if(theBoard->squareArray[xCurrent - 2][yCurrent - 1].piece.getType() == KNIGHT){
            return false;
        }
    }
    if(!(xCurrent - 2 < 0) || !(yCurrent + 1 > 7)){
        if(theBoard->squareArray[xCurrent - 2][yCurrent + 1].piece.getType() == KNIGHT){
            return false;
        }
    }
    if(!(xCurrent - 1 < 0) || !(yCurrent + 2 > 7)){
        if(theBoard->squareArray[xCurrent - 1][yCurrent + 2].piece.getType() == KNIGHT){
            return false;
        }
    }
    
    // Verify that the new square is not threatened by any other pieces
    if(checkLinesOfSight(xCurrent, yCurrent, theBoard)){
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
 *              board theBoard - the board to check     *
 *                                                      *
 * Returns:     bool - indicates whether the given      *
 *                     square is threatened by a        *
 *                     non-knight                       *
 * Description: returns a bool indicating whether the   *
 *              given square is threatened on the given *
 *              board by a non-knight                   *
 * -----------------------------------------------------*/
bool checkLinesOfSight(int x, int y, board theBoard){
    if(theBoard.checkNorth(int x, int y, board theBoard) == false 
    && theBoard.checkNorthEast(int x, int y, board theBoard) == false 
    && theBoard.checkEast(int x, int y, board theBoard) == false 
    && theBoard.checkSouthEast(int x, int y, board theBoard) == false 
    && theBoard.checkSouth(int x, int y, board theBoard) == false 
    && theBoard.checkSouthWest(int x, int y, board theBoard) == false 
    && theBoard.checkWest(int x, int y, board theBoard) == false 
    && theBoard.checkNorthWest(int x, int y, board theBoard) == false){
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
 *              board theBoard - the board to check     *
 *                                                      *
 * Returns:     bool - indicates whether the given      *
 *                     square is threatened from north  *
 * Description: returns a bool indicating whether the   *
 *              given square is threatened on the given *
 *              board from north                        *
 * -----------------------------------------------------*/
bool checkNorth(int x, int y, board *theBoard){
    if(y + 1 <= 7){
        if(theBoard->squareArray[x][y + 1].piece == NULL){
            checkLinesOfSight(x, y + 1, theBoard);
        }
        else{
            if(theBoard->squareArray[x][y + 1].piece.type == ROOK){
                return true;
            }
            else if(theBoard->squareArray[x][y + 1].piece.type == QUEEN){
                return true;
            }
            else{
                return false;
            }
        } 
    }
    else{
        return false
    }
}

/*------------------------------------------------------*
 * Function:    checkNorthEast                          *
 * Params:      int x - x position to check from        *
 *              int y - y position to check from        *
 *              board theBoard - the board to check     *
 *                                                      *
 * Returns:     bool - indicates whether the given      *
 *                     square is threatened from        *
 *                     north-east                       *
 * Description: returns a bool indicating whether the   *
 *              given square is threatened on the given *
 *              board from north-east                   *
 * -----------------------------------------------------*/
bool checkNorthEast(int x, int y, board *theBoard){
    if(theBoard->squareArray[x + 1][y + 1].piece.type != NULL){
        if(theBoard->squareArray[x + 1][y + 1].piece.type == PAWN){
            return true;
        }
    }
    if(x + 1 <= 7 && y + 1 <= 7){
        if(theBoard->squareArray[x + 1][y + 1].piece == NULL){
            checkLinesOfSight(x + 1, y + 1, theBoard);
        }
        else{
            if(theBoard->squareArray[x + 1][y + 1].piece.type == BISHOP){
                return true;
            }
            else if(theBoard->squareArray[x + 1][y + 1].piece.type == QUEEN){
                return true;
            }
            else{
                return false;
            }
        } 
    }
    else{
        return false
    }
}

/*------------------------------------------------------*
 * Function:    checkEast                               *
 * Params:      int x - x position to check from        *
 *              int y - y position to check from        *
 *              board theBoard - the board to check     *
 *                                                      *
 * Returns:     bool - indicates whether the given      *
 *                     square is threatened from        *
 *                     east                             *
 * Description: returns a bool indicating whether the   *
 *              given square is threatened on the given *
 *              board from east                         *
 * -----------------------------------------------------*/
bool checkEast(int x, int y, board *theBoard){
    if(x + 1 <= 7){
        if(theBoard->squareArray[x + 1][y].piece == NULL){
            checkLinesOfSight(x + 1, y, theBoard);
        }
        else{
            if(theBoard->squareArray[x + 1][y].piece.type == ROOK){
                return true;
            }
            else if(theBoard->squareArray[x + 1][y].piece.type == QUEEN){
                return true;
            }
            else{
                return false;
            }
        } 
    }
    else{
        return false
    }
}

/*------------------------------------------------------*
 * Function:    checkSouthEast                          *
 * Params:      int x - x position to check from        *
 *              int y - y position to check from        *
 *              board theBoard - the board to check     *
 *                                                      *
 * Returns:     bool - indicates whether the given      *
 *                     square is threatened from        *
 *                     south-east                       *
 * Description: returns a bool indicating whether the   *
 *              given square is threatened on the given *
 *              board from south-east                   *
 * -----------------------------------------------------*/
bool checkSouthEast(int x, int y, board *theBoard){
    if(x + 1 <= 7 && y - 1 >= 0){
        if(theBoard->squareArray[x + 1][y - 1].piece == NULL){
            checkLinesOfSight(x + 1, y - 1, theBoard);
        }
        else{
            if(theBoard->squareArray[x + 1][y - 1].piece.type == BISHOP){
                return true;
            }
            else if(theBoard->squareArray[x + 1][y - 1].piece.type == QUEEN){
                return true;
            }
            else{
                return false;
            }
        } 
    }
    else{
        return false
    }
}

/*------------------------------------------------------*
 * Function:    checkSouth                              *
 * Params:      int x - x position to check from        *
 *              int y - y position to check from        *
 *              board theBoard - the board to check     *
 *                                                      *
 * Returns:     bool - indicates whether the given      *
 *                     square is threatened from south  *
 * Description: returns a bool indicating whether the   *
 *              given square is threatened on the given *
 *              board from south                        *
 * -----------------------------------------------------*/
bool checkSouth(int x, int y, board *theBoard){
    if(y - 1 >= 0){
        if(theBoard->squareArray[x][y - 1].piece == NULL){
            checkLinesOfSight(x, y - 1, theBoard);
        }
        else{
            if(theBoard->squareArray[x][y - 1].piece.type == ROOK){
                return true;
            }
            else if(theBoard->squareArray[x][y - 1].piece.type == QUEEN){
                return true;
            }
            else{
                return false;
            }
        } 
    }
    else{
        return false
    }
}

/*------------------------------------------------------*
 * Function:    checkSouthWest                          *
 * Params:      int x - x position to check from        *
 *              int y - y position to check from        *
 *              board theBoard - the board to check     *
 *                                                      *
 * Returns:     bool - indicates whether the given      *
 *                     square is threatened from        *
 *                     south-west                       *
 * Description: returns a bool indicating whether the   *
 *              given square is threatened on the given *
 *              board from south-west                   *
 * -----------------------------------------------------*/
bool checkSouthWest(int x, int y, board *theBoard){
    if(x - 1 >= 0 && y - 1 >= 0){
        if(theBoard->squareArray[x - 1][y - 1].piece == NULL){
            checkLinesOfSight(x - 1, y - 1, theBoard);
        }
        else{
            if(theBoard->squareArray[x - 1][y - 1].piece.type == BISHOP){
                return true;
            }
            else if(theBoard->squareArray[x - 1][y - 1].piece.type == QUEEN){
                return true;
            }
            else{
                return false;
            }
        } 
    }
    else{
        return false
    }
}

/*------------------------------------------------------*
 * Function:    checkWest                               *
 * Params:      int x - x position to check from        *
 *              int y - y position to check from        *
 *              board theBoard - the board to check     *
 *                                                      *
 * Returns:     bool - indicates whether the given      *
 *                     square is threatened from        *
 *                     west                             *
 * Description: returns a bool indicating whether the   *
 *              given square is threatened on the given *
 *              board from west                         *
 * -----------------------------------------------------*/
bool checkWest(int x, int y, board *theBoard){
    if(x - 1 >= 0){
        if(theBoard->squareArray[x - 1][y].piece == NULL){
            checkLinesOfSight(x - 1, y, theBoard);
        }
        else{
            if(theBoard->squareArray[x - 1][y].piece.type == ROOK){
                return true;
            }
            else if(theBoard->squareArray[x - 1][y].piece.type == QUEEN){
                return true;
            }
            else{
                return false;
            }
        } 
    }
    else{
        return false
    }
}

/*------------------------------------------------------*
 * Function:    checkNorthWest                          *
 * Params:      int x - x position to check from        *
 *              int y - y position to check from        *
 *              board theBoard - the board to check     *
 *                                                      *
 * Returns:     bool - indicates whether the given      *
 *                     square is threatened from        *
 *                     north-west                       *
 * Description: returns a bool indicating whether the   *
 *              given square is threatened on the given *
 *              board from north-west                   *
 * -----------------------------------------------------*/
bool checkNorthWest(int x, int y, board *theBoard){
    if(theBoard->squareArray[x - 1][y + 1].piece.type != NULL){
        if(theBoard->squareArray[x - 1][y + 1].piece.type == PAWN){
            return true;
        }
    }
    if(x - 1 >= 0 && y + 1 <= 7){
        if(theBoard->squareArray[x - 1][y + 1].piece == NULL){
            checkLinesOfSight(x - 1, y + 1, theBoard);
        }
        else{
            if(theBoard->squareArray[x - 1][y + 1].piece.type == BISHOP){
                return true;
            }
            else if(theBoard->squareArray[x - 1][y + 1].piece.type == QUEEN){
                return true;
            }
            else{
                return false;
            }
        } 
    }
    else{
        return false
    }
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
 * Description: determines if a move is valid           *
 * -----------------------------------------------------*/
bool king::canMove(int xNew, int yNew, board *theBoard){
    int xCurrent = getXCoord();
    int yCurrent = getYCoord();

    // Verify that the new location is a valid board location
    if(xNew < 0 || yNew < 0 || xNew > 7 || yNew > 7){
        return false;
    }

    // Verify that the new square is not occupied by a friendly piece 
    if(theBoard->squareArray[xNew][yNew].piece.color == getColor()){
        return false
    }

    // Verify that the new square is not threatened by an enemy piece
   
    // Verify that the new square is within reach of the king
    int xDelta = abs(xNew - xCurrent);
    int yDelta = abs(yNew - yCurrent);
    if(xDelta == 0 && yDelta == 0){
        return false; // Cannot move to the same space 
    }
    if(xDelta >= 2 || yDelta >= 2){
        return false; // Cannot move more than one space
    }
    else{
        moved();
        return true;
    }
}

/*------------------------------------------------------*
 * Function:    queen::canMove                          *
 * Params:      int xNew - new x position to move piece *
 *                         to                           *
 *              int yNew - new y position to move piece *
 *                         to                           *
 * Returns:     bool - indicates if a piece can move to *
 *                     the given position               *
 * Description: determines if a move is valid           *
 * -----------------------------------------------------*/
bool queen::canMove(int xNew, int yNew){
    int xCurrent = getXCoord();
    int yCurrent = getYCoord();

    // Verify that the new location is a valid board location
    if(xNew < 0 || yNew < 0 || xNew > 7 || yNew > 7){
        return false;
    }

    // Verify that the new square is not occupied by a friendly piece


    // Verify that the new Square is within reach of the queen
    int xDelta = abs(xNew - xCurrent);
    int yDelta = abs(yNew - yCurrent);
    if(xDelta == 0 && yDelta == 0){
        return false; // Cannot move to the same space 
    }
    else if(xDelta != yDelta && xDelta != 0 && yDelta != 0){
        return false; // If not lateral, both deltas must have same magnitude to stay on the correct diagonal
    }
    else{
        return true;
    }
}

/*------------------------------------------------------*
 * Function:    bishop::canMove                         *
 * Params:      int xNew - new x position to move piece *
 *                         to                           *
 *              int yNew - new y position to move piece *
 *                         to                           *
 * Returns:     bool - indicates if a piece can move to *
 *                     the given position               *
 * Description: determines if a move is valid           *
 * -----------------------------------------------------*/
bool bishop::canMove(int xNew, int yNew){
    int xCurrent = getXCoord();
    int yCurrent = getYCoord();

    // Verify that the new location is a valid board location
    if(xNew < 0 || yNew < 0 || xNew > 7 || yNew > 7){
        return false;
    }

    // Verify that the new square is not occupied by a friendly piece


    // Verify that the new Square is within reach of the bishop
    int xDelta = abs(xNew - xCurrent);
    int yDelta = abs(yNew - yCurrent);
    if(xDelta == 0 || yDelta == 0){
        return false; // Cannot move to the same space or laterally
    }
    else if(xDelta != yDelta){
        return false; // Both deltas must have same magnitude to stay on the correct diagonal
    }
    else{
        return true;
    }
}

/*------------------------------------------------------*
 * Function:    knight::canMove                         *
 * Params:      int xNew - new x position to move piece *
 *                         to                           *
 *              int yNew - new y position to move piece *
 *                         to                           *
 * Returns:     bool - indicates if a piece can move to *
 *                     the given position               *
 * Description: determines if a move is valid           *
 * -----------------------------------------------------*/
bool knight::canMove(int xNew, int yNew){
    int xCurrent = getXCoord();
    int yCurrent = getYCoord();

    // Verify that the new location is a valid board location
    if(xNew < 0 || yNew < 0 || xNew > 7 || yNew > 7){
        return false;
    }

    // Verify that the new square is not occupied by a friendly piece


    // Verify that the new Square is within reach of the knight
    int xDelta = abs(xNew - xCurrent);
    int yDelta = abs(yNew - yCurrent);
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
 * Returns:     bool - indicates if a piece can move to *
 *                     the given position               *
 * Description: determines if a move is valid           *
 * -----------------------------------------------------*/
bool rook::canMove(int xNew, int yNew){
    int xCurrent = getXCoord();
    int yCurrent = getYCoord();

    // Verify that the new location is a valid board location
    if(xNew < 0 || yNew < 0 || xNew > 7 || yNew > 7){
        return false;
    }

    // Verify that the new square is not occupied by a friendly piece


    // Verify that the new Square is within reach of the rook
    int xDelta = abs(xNew - xCurrent);
    int yDelta = abs(yNew - yCurrent);
    if(xDelta == 0 && yDelta == 0){
        return false; // Cannot move to the same space 
    }
    else if(xDelta != 0 && yDelta != 0 ){
        return false; // Rook must stay on one row/column, so one of the deltas must be 0
    }
    else{
        moved();
        return true;
    }
}

/*------------------------------------------------------*
 * Function:    pawn::canMove                           *
 * Params:      int xNew - new x position to move piece *
 *                         to                           *
 *              int yNew - new y position to move piece *
 *                         to                           *
 * Returns:     bool - indicates if a piece can move to *
 *                     the given position               *
 * Description: determines if a move is valid           *
 * -----------------------------------------------------*/
bool pawn::canMove(int xNew, int yNew){
    int xCurrent = getXCoord();
    int yCurrent = getYCoord();

    // Verify that the new location is a valid board location
    if(xNew < 0 || yNew < 0 || xNew > 7 || yNew > 7){
        return false;
    }

    // Verify that the new square is not occupied by a friendly piece


    // Verify that the new Square is within reach of the pawn
    int xDelta = xNew - xCurrent;
    int yDelta = yNew - yCurrent;
    int myColor = getColor();
    if(myColor == WHITE){
        (bool)myColor;
        if(xDelta == 1 && yDelta == 1 && isOccupiedByColor(xNew,yNew,BLACK)){
            moved();
            return true; // Capturing
        }
        else if(xDelta == 0 && yDelta == 1){
            moved();
            return true; 
        }
        else if(xDelta == 0 && yDelta == 2 && !hasMoved){
            moved();
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if(xDelta == -1 && yDelta == -1 && isOccupiedByColor(xNew,yNew,WHITE)){
            moved();
            return true; // Capturing
        }
        else if(xDelta == 0 && yDelta == -1){
            moved();
            return true; 
        }
        else if(xDelta == 0 && yDelta == -2 && !hasMoved){
            moved();
            return true;
        }
        else{
            return false;
        }
    }
}