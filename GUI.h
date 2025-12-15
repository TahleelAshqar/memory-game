#ifndef GUI_H
#define GUI_H

#include <stdbool.h>

void DrawCard(int x, int y, int w, int h, int value, bool isRevealed);

int MouseToCell(int mx, int my,
                int gridX, int gridY,
                int cellW, int cellH,
                int size,
                int* outRow, int* outCol);

#endif
