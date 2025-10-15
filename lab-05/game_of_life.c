// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 5 Arrays and Functions

#include "game_of_life.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_board(Board *board, int num_alive) {
  // clear the board
  memset(board->board_flat, CELL_DEAD, sizeof(Board));

  if (num_alive <= 0) {
    return;
  }

  // just fill the board with live cells if more than that are requested
  if (num_alive > sizeof(Board)) {
    memset(board->board_flat, CELL_ALIVE, sizeof(Board));
    return;
  }

  // setup board with requested number of live cells and Fisher-Yates shuffle to
  // randomize distribution

  memset(board, CELL_ALIVE, num_alive);

  for (int i = (BOARD_WIDTH * BOARD_HEIGHT) - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    char tmp = board->board_flat[i];
    board->board_flat[i] = board->board_flat[j];
    board->board_flat[j] = tmp;
  }
}

void display_board(Board *board) {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    fwrite(board->board[i], sizeof(char), BOARD_WIDTH, stdout);
    puts("");
  }
}

int num_neighbors(Board *board, int row, int col) {
  int neighbors = 0;

  for (int i = row - 1; i <= row + 1; i++) {
    for (int j = col - 1; j <= col + 1; j++) {
      if (0 <= i && i < BOARD_HEIGHT && // i within bounds
          0 <= j && j < BOARD_WIDTH &&  // j within bounds
          !(i == row && j == col)       // skip self
      ) {
        neighbors += board->board[i][j] == CELL_ALIVE;
      }
    }
  }

  return neighbors;
}

char next_state(Board *board, int row, int col) {
  switch (num_neighbors(board, row, col)) {
  // underpopulation
  case 0:
  case 1:
    return CELL_DEAD;

  // stability
  case 2:
    return board->board[row][col];

  // reproduction
  case 3:
    return CELL_ALIVE;

  // overpopulation or invalid
  default:
    return CELL_DEAD;
  }
}

void next_generation(Board *board) {
  Board tmp;

  for (int row = 0; row < BOARD_HEIGHT; row++) {
    for (int col = 0; col < BOARD_WIDTH; col++) {
      tmp.board[row][col] = next_state(board, row, col);
    }
  }

  memcpy(board->board, tmp.board, sizeof(Board));
}
