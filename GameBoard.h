#ifndef GAMEBOARD_H
#define GAMEBOARD_H

// Structure to represent the game board
typedef struct {
    int** values;    // Stores the card values
    int** revealed;  // Stores the state of each card (0 = hidden, 1 = revealed)
    int size;        // board size is size * size
} GameBoard;

GameBoard* initBoard(const int* predefinedValues, int size);
void printBoard(GameBoard* gb);
int playTurn(GameBoard* gb, int row1, int col1, int row2, int col2);
int checkVictory(GameBoard* gb);
void freeBoard(GameBoard* gb);

#endif
