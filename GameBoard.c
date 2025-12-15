#include <stdio.h>
#include <stdlib.h>
#include "GameBoard.h"

static int isValidCell(GameBoard* gb, int r, int c) {
    return (gb && r >= 0 && c >= 0 && r < gb->size && c < gb->size);
}

GameBoard* initBoard(const int* predefinedValues, int size)
{
    GameBoard* gb = (GameBoard*)malloc(sizeof(GameBoard));
    if (!gb) return NULL;

    gb->size = size;

    gb->values = (int**)malloc(sizeof(int*) * size);
    gb->revealed = (int**)malloc(sizeof(int*) * size);
    if (!gb->values || !gb->revealed) {
        freeBoard(gb);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        gb->values[i] = (int*)malloc(sizeof(int) * size);
        gb->revealed[i] = (int*)malloc(sizeof(int) * size);
        if (!gb->values[i] || !gb->revealed[i]) {
            freeBoard(gb);
            return NULL;
        }
    }

    // Initialize from predefined 1D array (row-major)
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            gb->values[r][c] = predefinedValues[r * size + c];
            gb->revealed[r][c] = 0; // all hidden initially
        }
    }

    return gb;
}

void printBoard(GameBoard* gb)
{
    for (int r = 0; r < gb->size; r++) {
        for (int c = 0; c < gb->size; c++) {
            if (gb->revealed[r][c] == 0) {
                printf("* ");
            } else {
                // requirement: print 2 spaces after each number
                printf("%d  ", gb->values[r][c]);
            }
        }
        printf("\n");
    }
}

int playTurn(GameBoard* gb, int row1, int col1, int row2, int col2)
{
    if (!isValidCell(gb, row1, col1) || !isValidCell(gb, row2, col2))
        return -1;

    // same cell is not a valid "two picks"
    if (row1 == row2 && col1 == col2)
        return -1;

    // avoid selecting already revealed cards (common memory-game rule)
    if (gb->revealed[row1][col1] == 1 || gb->revealed[row2][col2] == 1)
        return -1;

    // reveal both
    gb->revealed[row1][col1] = 1;
    gb->revealed[row2][col2] = 1;

    // per assignment: playTurn prints the board
    printBoard(gb);

    // compare
    if (gb->values[row1][col1] == gb->values[row2][col2]) {
        return 1; // keep revealed
    }

    // hide again
    gb->revealed[row1][col1] = 0;
    gb->revealed[row2][col2] = 0;
    return 0;
}

int checkVictory(GameBoard* gb)
{
    for (int r = 0; r < gb->size; r++) {
        for (int c = 0; c < gb->size; c++) {
            if (gb->revealed[r][c] == 0)
                return 0;
        }
    }
    return 1;
}

void freeBoard(GameBoard* gb)
{
    if (!gb) return;

    if (gb->values) {
        for (int i = 0; i < gb->size; i++) {
            free(gb->values[i]);
        }
        free(gb->values);
    }

    if (gb->revealed) {
        for (int i = 0; i < gb->size; i++) {
            free(gb->revealed[i]);
        }
        free(gb->revealed);
    }

    free(gb);
}
