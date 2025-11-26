// Name: [redacted]
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 7 More SDL Graphics in C

#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>

#include "game_of_life.h"

// Initialize `board` with `num_alive` live cells.
void GOL_init_board(GOL_Board *board, unsigned int num_alive) {
  // clear the board
  memset(board, GOL_CELL_DEAD, sizeof(GOL_Board));

  // just fill the board with live cells if more are requested than can fit
  if (num_alive >= sizeof(GOL_Board)) {
    memset(board, GOL_CELL_ALIVE, sizeof(GOL_Board));
    return;
  }

  // setup board with requested number of live cells and Fisher-Yates shuffle to
  // randomize distribution

  memset(board, GOL_CELL_ALIVE, num_alive);

  for (int i = (BOARD_WIDTH * BOARD_HEIGHT) - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    char tmp = board->board_flat[i];
    board->board_flat[i] = board->board_flat[j];
    board->board_flat[j] = tmp;
  }
}

void GOL_place_cells(GOL_Board *board, unsigned int num_cells) {

  // generate the initial list of indexes
  int indexes[sizeof(GOL_Board)];
  for (int i = 0; i < sizeof(GOL_Board); i++) {
    indexes[i] = i;
  }

  // shuffle indexes to get random permutation
  for (int i = sizeof(GOL_Board) - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    int tmp = indexes[i];
    indexes[i] = indexes[j];
    indexes[j] = tmp;
  }

  // use permuted indexes to pick cells until there are either no more cells to
  // pick or we've hit our quota
  for (int i = 0; num_cells > 0 && i < sizeof(GOL_Board); i++) {
    int idx = indexes[i];

    if (board->board_flat[idx] != GOL_CELL_DEAD)
      continue;

    board->board_flat[idx] = GOL_CELL_ALIVE;
    num_cells -= 1;
  }
}

void GOL_display_board(const GOL_Board *board, SDL_Surface *surface) {
  for (int row = 0; row < BOARD_HEIGHT; row++) {
    for (int col = 0; col < BOARD_WIDTH; col++) {
      // 4x4px squares separated by a 1px gap
      SDL_Rect cell_rect = {col * 5, row * 5, 4, 4};

      char cell_age = board->board[row][col];

      Uint32 color;
      if (cell_age == GOL_CELL_DEAD) {
        // black if dead cell
        color = SDL_MapRGB(surface->format, 0x00, 0x00, 0x00);
      } else {
        // starts dim-blue, gets redder as cell_age increases;
        // CELL_ALIVE_MAX steps.
        color = SDL_MapRGB(
            surface->format, (cell_age - 1) * (0xFF / (GOL_CELL_ALIVE_MAX - 1)),
            0x00, 0xB0 - ((cell_age - 1) * (0xB0 / (GOL_CELL_ALIVE_MAX - 1))));
      }

      SDL_FillRect(surface, &cell_rect, color);
    }
  }
}

int GOL_num_neighbors(const GOL_Board *board, unsigned int row,
                      unsigned int col) {
  int neighbors = 0;

  for (int i = row - 1; i <= row + 1; i++) {
    for (int j = col - 1; j <= col + 1; j++) {
      if (0 <= i && i < BOARD_HEIGHT && // i within bounds
          0 <= j && j < BOARD_WIDTH &&  // j within bounds
          !(i == row && j == col)       // skip self
      ) {
        neighbors += board->board[i][j] != GOL_CELL_DEAD;
      }
    }
  }

  return neighbors;
}

char GOL_next_state(const GOL_Board *board, unsigned int row,
                    unsigned int col) {
  switch (GOL_num_neighbors(board, row, col)) {
  // underpopulation
  case 0:
  case 1:
    return GOL_CELL_DEAD;

  // stability
  case 2: {
    char cell_state = board->board[row][col];
    if (cell_state == GOL_CELL_DEAD) {
      // dead stays dead
      return GOL_CELL_DEAD;
    } else {
      // increment the cell's age if it's not already the max
      return cell_state + (cell_state < GOL_CELL_ALIVE_MAX);
    }
  }

  // reproduction
  case 3:
    // increment age of live cell, bounded by CELL_ALIVE_MAX
    return board->board[row][col] +
           (board->board[row][col] < GOL_CELL_ALIVE_MAX);

  // overpopulation or invalid
  default:
    return GOL_CELL_DEAD;
  }
}

void GOL_next_generation(GOL_Board *board) {
  GOL_Board tmp;

  for (int row = 0; row < BOARD_HEIGHT; row++) {
    for (int col = 0; col < BOARD_WIDTH; col++) {
      tmp.board[row][col] = GOL_next_state(board, row, col);
    }
  }

  memcpy(board->board, tmp.board, sizeof(GOL_Board));
}
