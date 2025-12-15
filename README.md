# memory-game
Classic NxN memory game in C: dynamic GameBoard logic (structs/pointers) plus a Raylib GUI wrapper.

# Memory Game (C + Raylib)

This project implements a classic **Memory Game** on an **N x N** board (N is even).

It includes:
- **Part A (Logic):** a dynamically allocated `GameBoard` using `int**` for values and revealed-state.
- **Part B (GUI):** a Raylib-based graphical wrapper that draws the board, handles mouse clicks, and shows matches/mismatches with a short delay.

## Project Structure

### Part A (Submission files for VPL)
- `GameBoard.h` — `GameBoard` struct and function declarations
- `GameBoard.c` — implementation of:
  - `initBoard`
  - `printBoard`
  - `playTurn`
  - `checkVictory`
  - `freeBoard`

### Part B (GUI submission files)
- `GUI.h` — GUI function declarations
- `GUI.c` — implementation of:
  - `DrawCard`
  - `MouseToCell`
- `GUIsMain.c` — Raylib main loop (gameplay with mouse clicks)
- `README.txt` — short notes about the GUI implementation (as required)

## Notes
- The board is allocated dynamically and fully freed at the end.
- `printBoard` prints hidden cards as `*` and revealed cards as numbers (with spacing requirements).
- The GUI uses Raylib rectangles and text to visualize cards and supports a 1-second reveal pause on mismatches.

## Build (GUI)
You need Raylib installed.

Example compile command (may vary by your environment):
```bash
gcc GUIsMain.c GUI.c GameBoard.c -o memory_game -lraylib -lm
