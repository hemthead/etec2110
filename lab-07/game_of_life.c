// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 5 Arrays and Functions

#include "game_of_life.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <stdlib.h>
#include <string.h>

void init_board(Board *board, int num_alive) {
  // clear the board
  memset(board, CELL_DEAD, sizeof(Board));

  if (num_alive <= 0) {
    return;
  }

  // just fill the board with live cells if more are requested than can fit
  if (num_alive >= sizeof(Board)) {
    memset(board, CELL_ALIVE, sizeof(Board));
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

/*
void display_board(Board *board) {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    fwrite(board->board[i], sizeof(char), BOARD_WIDTH, stdout);
    puts("");
  }
}
*/

void display_board(Board *board, SDL_Surface *surface) {
  for (int row = 0; row < BOARD_HEIGHT; row++) {
    for (int col = 0; col < BOARD_WIDTH; col++) {
      SDL_Rect rect = {col * 5, row * 5, 4, 4};

      // TODO: Fix this mess!!!
      SDL_FillRect(surface, &rect,
                   SDL_MapRGB(surface->format, board->board[row][col] * 0x0F, 0,
                              (0xFF * board->board[row][col] != CELL_DEAD) -
                                  board->board[row][col] * 0x0F));
    }
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
        neighbors += board->board[i][j] != CELL_DEAD;
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
  case 2: {
    char cell_state = board->board[row][col];
    if (cell_state == CELL_DEAD) {
      // dead stays dead
      return CELL_DEAD;
    } else {
      return cell_state + (cell_state < CELL_ALIVE_MAX);
    }
  }

  // reproduction
  case 3:
    // return CELL_ALIVE;
    // increment age of live cell, bounded by CELL_ALIVE_MAX
    return board->board[row][col] + (board->board[row][col] < CELL_ALIVE_MAX);

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
