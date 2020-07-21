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
    if(piece == NULL){
        this->isOccupied = false;
    }
    else{
        this->isOccupied = true;
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
                    case 7:
                    // Rooks
                        rook whiteRook;
                        whiteRook.initPiece(WHITE, x, y);
                        squareArray[x][y].initSquare(x, y, &whiteRook);
                        break;
                    case 1:
                    case 6:
                    // Knights
                        knight whiteKnight;
                        whiteKnight.initPiece(WHITE, x, y);
                        squareArray[x][y].initSquare(x, y, &whiteKnight);
                        break;
                    case 2:
                    case 5:
                    // Bishops
                        bishop whiteBishop;
                        whiteBishop.initPiece(WHITE, x, y);
                        squareArray[x][y].initSquare(x, y, &whiteBishop);
                        break;
                    case 3:
                    // Queen
                        queen whiteQueen;
                        whiteQueen.initPiece(WHITE, x, y);
                        squareArray[x][y].initSquare(x, y, &whiteQueen);
                        break;
                    case 4:
                    // King
                        king whiteKing;
                        whiteKing.initPiece(WHITE, x, y);
                        squareArray[x][y].initSquare(x, y, &whiteKing);
                        break;
                    
                }
            }
            // Black home row
            else if(y == 7){
                switch (x){
                    case 0:
                    case 7:
                    // Rooks
                        rook blackRook;
                        blackRook.initPiece(BLACK, x, y);
                        squareArray[x][y].initSquare(x, y, &blackRook);
                        break;
                    case 1:
                    case 6:
                    // Knights
                        knight blackKnight;
                        blackKnight.initPiece(BLACK, x, y);
                        squareArray[x][y].initSquare(x, y, &blackKnight);
                        break;
                    case 2:
                    case 5:
                    // Bishops
                        bishop blackBishop;
                        blackBishop.initPiece(BLACK, x, y);
                        squareArray[x][y].initSquare(x, y, &blackBishop);
                        break;
                    case 3:
                    // Queen
                        queen blackQueen;
                        blackQueen.initPiece(BLACK, x, y);
                        squareArray[x][y].initSquare(x, y, &blackQueen);
                        break;
                    case 4:
                    // King
                        king blackKing;
                        blackKing.initPiece(BLACK, x, y);
                        squareArray[x][y].initSquare(x, y, &blackKing);
                        break;
                    
                }
            }
            // All y=1 squares get initialized with a white pawn
            else if(y == 1){
                pawn whitePawn;
                whitePawn.initPiece(WHITE, x, y);
                squareArray[x][y].initSquare(x, y, &whitePawn);
            }
            // All y=6 squares get initialized with a black pawn
            else if(y == 6){
                pawn blackPawn;
                blackPawn.initPiece(BLACK, x, y);
                squareArray[x][y].initSquare(x, y, &blackPawn);
            }
            else{
                squareArray[x][y].initSquare(x, y, NULL);
            }
        }
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
void piece::initPiece(int color, int x, int y){
    this->color = color;
    this->x = x;
    this->y = y;
}

// Derived Piece Implementation

/*------------------------------------------------------*
 * Function:    canMove                                 *
 * Params:      int xNew - new x position to move piece *
 *                         to                           *
 *              int yNew - new y position to move piece *
 *                         to                           *
 * Returns:     Void                                    *
 * Description: populates the member data of a board    *
 *              object                                  *
 * -----------------------------------------------------*/
bool king::canMove(int xNew, int yNew){
    int xCurrent = getXCoord();
    int yCurrent = getYCoord();

    // Verify that the new location is a valid board location
    if(xNew < 0 || yNew < 0 || xNew > 7 || yNew > 7){
        return false;
    }

    //Verify that the new square is not occupied by a friendly piece

    // Verify that the new Square is within reach of the king
    if(abs(xNew - xCurrent) >= 2 || abs(yNew-yCurrent) >= 2){
        return false;
    }
}

