#include "GUI.h"
#include "raylib.h"

void DrawCard(int x, int y, int w, int h, int value, bool isRevealed)
{
    Rectangle rect = (Rectangle){ (float)x, (float)y, (float)w, (float)h };

    if (!isRevealed) {
        DrawRectangleRec(rect, DARKGRAY);
        DrawRectangleLines(x, y, w, h, BLACK);
    } else {
        DrawRectangleRec(rect, RAYWHITE);
        DrawRectangleLines(x, y, w, h, BLACK);

        char buf[32];
        TextFormat("%d", value); // Raylib helper (not used directly)
        snprintf(buf, sizeof(buf), "%d", value);

        int fontSize = h / 3;
        int tw = MeasureText(buf, fontSize);
        DrawText(buf, x + (w - tw) / 2, y + (h - fontSize) / 2, fontSize, BLACK);
    }
}

int MouseToCell(int mx, int my,
                int gridX, int gridY,
                int cellW, int cellH,
                int size,
                int* outRow, int* outCol)
{
    int gridW = cellW * size;
    int gridH = cellH * size;

    if (mx < gridX || my < gridY || mx >= gridX + gridW || my >= gridY + gridH)
        return 0;

    int col = (mx - gridX) / cellW;
    int row = (my - gridY) / cellH;

    if (row < 0 || col < 0 || row >= size || col >= size)
        return 0;

    *outRow = row;
    *outCol = col;
    return 1;
}
