// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 5 Arrays and Functions

#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <SDL2/SDL_surface.h>

#define BOARD_HEIGHT 100
#define BOARD_WIDTH 200
//#define BOARD_WIDTH 40
//set BOARD_WIDTH to 40 to load factory.gol

// The state of a cell in Conway's Game of Life. (char)
enum CellAge {
  CELL_DEAD = 0,
  CELL_ALIVE = 1,
  CELL_ALIVE_MAX = 16,
};

// A board for Conway's Game of Life.
typedef union Board {
  // 2D view of board
  char board[BOARD_HEIGHT][BOARD_WIDTH];
  // flattened 1D view of board
  char board_flat[BOARD_HEIGHT * BOARD_WIDTH];
} Board;

// Initialize a `Board` to have `num_alive` alive cells randomly distributed throughout it.
// The entire board is set alive if `num_alive` is larger than the number of cells.
void init_board(Board *board, int num_alive);

// Displays a `Board` in a 2D format. Live cells marked with 'X' and dead with '-'.
void display_board(Board *board, SDL_Surface *surface);

// Counts the live neighbors of a cell at `[row][col]`.
int num_neighbors(Board *board, int row, int col);

// Returns the next state (`CellState`) of a cell at `[row][col]`.
char next_state(Board *board, int row, int col);

// Advances a `Board` to its next generation.
void next_generation(Board *board);

#endif
