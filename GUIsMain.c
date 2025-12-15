#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "raylib.h"
#include "GameBoard.h"
#include "GUI.h"

int main(void)
{
    // Example predefined board (size=4). Replace if your checker provides values differently.
    int size = 4;
    int predefinedValues[] = {1,2,3,4,5,6,7,8,8,1,2,3,4,5,6,7};

    GameBoard* gb = initBoard(predefinedValues, size);
    if (!gb) return 1;

    const int screenW = 800;
    const int screenH = 600;
    InitWindow(screenW, screenH, "Memory Game - Raylib");
    SetTargetFPS(60);

    int padding = 20;
    int cellW = (screenW - 2 * padding) / size;
    int cellH = (screenH - 2 * padding) / size;
    int gridX = padding;
    int gridY = padding;

    int firstRow = -1, firstCol = -1;
    int secondRow = -1, secondCol = -1;

    bool waitingToHide = false;
    double hideAtTime = 0.0;

    while (!WindowShouldClose())
    {
        // If mismatch timer expired, hide the two cards
        if (waitingToHide && GetTime() >= hideAtTime) {
            gb->revealed[firstRow][firstCol] = 0;
            gb->revealed[secondRow][secondCol] = 0;

            firstRow = firstCol = -1;
            secondRow = secondCol = -1;
            waitingToHide = false;
        }

        // Handle mouse click only if not in delay phase
        if (!waitingToHide && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int r, c;
            if (MouseToCell(GetMouseX(), GetMouseY(), gridX, gridY, cellW, cellH, size, &r, &c)) {

                // ignore clicks on already revealed cards
                if (gb->revealed[r][c] == 0) {
                    if (firstRow == -1) {
                        firstRow = r; firstCol = c;
                        gb->revealed[r][c] = 1;
                    } else if (secondRow == -1 && !(r == firstRow && c == firstCol)) {
                        secondRow = r; secondCol = c;
                        gb->revealed[r][c] = 1;

                        // Compare
                        if (gb->values[firstRow][firstCol] == gb->values[secondRow][secondCol]) {
                            // match: keep revealed, reset selection
                            firstRow = firstCol = -1;
                            secondRow = secondCol = -1;
                        } else {
                            // mismatch: show for 1 second then hide
                            waitingToHide = true;
                            hideAtTime = GetTime() + 1.0;
                        }
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground((Color){ 30, 30, 30, 255 });

        // Draw board
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                int x = gridX + c * cellW;
                int y = gridY + r * cellH;
                DrawCard(x, y, cellW - 2, cellH - 2, gb->values[r][c], gb->revealed[r][c] == 1);
            }
        }

        // Victory
        if (checkVictory(gb)) {
            DrawText("Victory! All cards are revealed.", 20, screenH - 40, 20, GREEN);
        } else {
            DrawText("Click two cards to find matching pairs.", 20, screenH - 40, 20, RAYWHITE);
        }

        EndDrawing();
    }

    freeBoard(gb);
    CloseWindow();
    return 0;
}
