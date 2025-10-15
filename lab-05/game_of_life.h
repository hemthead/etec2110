// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 5 Arrays and Functions

#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#define BOARD_HEIGHT 20
#define BOARD_WIDTH 30

// The state of a cell in Conway's Game of Life. (char)
enum CellState {
  CELL_DEAD = '-',
  CELL_ALIVE = 'X',
};

// A board for Conway's Game of Life.
typedef union Board {
  // 2D view of board
  char board[BOARD_HEIGHT][BOARD_WIDTH];
  // flattened 1D view of board
  char board_flat[BOARD_HEIGHT * BOARD_WIDTH];
} Board;

// Initialize a `Board` to have `num_alive` alive cells randomly distributed throughout it.
// The entire board is alive if `num_alive` is larger than the number of cells.
void init_board(Board *board, int num_alive);

// Displays a `Board` in a 2D format. Live cells marked with 'X' and dead with '-'.
void display_board(Board *board);

// Counts the live neighbors of a cell at `[row][col]`.
int num_neighbors(Board *board, int row, int col);

// Returns the next state (`CellState`) of a cell at `[row][col]`.
char next_state(Board *board, int row, int col);

// Advances a `Board` to its next generation.
void next_generation(Board *board);

#endif
