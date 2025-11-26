// Name: [redacted]
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 5 Arrays and Functions

#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <SDL2/SDL_surface.h>

#define BOARD_HEIGHT 100
#define BOARD_WIDTH 200

// The state of a cell in Conway's Game of Life. (char)
enum GOL_CellState {
  GOL_CELL_DEAD = 0,
  GOL_CELL_ALIVE = 1,
  GOL_CELL_ALIVE_MAX = 16,
};

// A board for Conway's Game of Life.
typedef union GOL_Board {
  // 2D view of board
  char board[BOARD_HEIGHT][BOARD_WIDTH];
  // flattened 1D view of board
  char board_flat[BOARD_HEIGHT * BOARD_WIDTH];
} GOL_Board;

// Initialize a `Board` to have `num_alive` alive cells randomly distributed
// throughout it. The entire board is set alive if `num_alive` is larger than
// the number of cells.
void GOL_init_board(GOL_Board *board, unsigned int num_alive);

// Randomly distribute `num_cells` new live cells on a board.
void GOL_place_cells(GOL_Board *board, unsigned int num_cells);

// Displays a `Board` in a 2D format. Live cells marked with 'X' and dead with
// '-'.
void GOL_display_board(const GOL_Board *board, SDL_Surface *surface);

// Counts the live neighbors of a cell at `[row][col]`.
int GOL_num_neighbors(const GOL_Board *board, unsigned int row,
                      unsigned int col);

// Returns the next state (`CellState`) of a cell at `[row][col]`.
char GOL_next_state(const GOL_Board *board, unsigned int row, unsigned int col);

// Advances a `Board` to its next generation.
void GOL_next_generation(GOL_Board *board);

#endif
