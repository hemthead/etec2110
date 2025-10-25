// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 5 Arrays and Functions

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "game_of_life.h"

#define INPUT_SIZE 256

void print_help(void) {
  printf(
      "\nEnter in a command to control the game.\n"
      "Commands arbitrarily limited to %d characters of input.\n"
      "Commands:\n"
      "<ENTER>:        step forward by one generation.\n"
      "r <num>:        step forward by <num> generations.\n"
      "s <seed> <num>: set the random seed and reinitialize the board with "
      "<num> live cells.\n"
      "l <path>:       load a board from a file (formatted same as output).\n"
      "[d]isplay:      show current generation.\n"
      "[q]uit, [e]xit: leave the game.\n"
      "[h]elp, ?:      show this help.\n\n",
      INPUT_SIZE - 1);
}

int load_board(char *path, Board *board) {
  FILE *board_file = fopen(path, "r");
  if (!board_file) {
    perror("Failed to load board");
    return -1;
  }

  // temporary board in case there's a formatting error
  Board tmp_board;
  char buffer[BOARD_WIDTH + 1];

  for (int row = 0; row < BOARD_HEIGHT; row++) {
    if (fread(buffer, sizeof(char), BOARD_WIDTH + 1, board_file) !=
            BOARD_WIDTH + 1 ||         // couldn't read full stride, or
        buffer[BOARD_WIDTH] != '\n') { // stride didn't end with newline
      fprintf(stderr, "Failed to load board: Bad Formatting\n");
      return -1;
    }
    // copy stride
    memcpy(tmp_board.board[row], buffer, BOARD_WIDTH);
  }

  memcpy(board, &tmp_board, sizeof(Board));
  fclose(board_file);

  return 0;
}

int main(void) {
  unsigned int rand_seed = time(NULL);
  srand(rand_seed);

  int initial_live_cells = 300;

  Board board;

  init_board(&board, initial_live_cells);
  int current_gen = 0;

  // print initial generation
  printf("\nGeneration %d:\n", current_gen);
  display_board(&board);

  // input/game loop
  char input[INPUT_SIZE];
  bool running = true;
  while (running) {
    printf("Next command: ");
    fflush(stdout);

    if (fgets(input, INPUT_SIZE, stdin) == NULL) {
      break;
    }

    switch (input[0]) {
    case 'q':
    case 'Q':
    case 'e':
    case 'E':
      running = false;
      continue; // while (running) ; skip printing board

    case 'r': {
      // number of generations to run, default to 0
      int num_gens = 0;
      sscanf(input, "r %d", &num_gens);

      current_gen += num_gens;
      for (; num_gens > 0; num_gens--) {
        next_generation(&board);
      }
    } break;

    case '\n':
      current_gen++;
      next_generation(&board);
      break;

    case 's': {
      sscanf(input, "s %u %d", &rand_seed, &initial_live_cells);
      srand(rand_seed);
      printf("Seed: %u\n", rand_seed);
      init_board(&board, initial_live_cells);
      current_gen = 0;
    } break;

    case 'l': {
      sscanf(input, "l %s", input);
      if (load_board(input, &board) == -1) {
        continue; // while (running) ; skip printing board
      }
      rand_seed = 0;
      initial_live_cells = 0;
      current_gen = 0;
    } break;

    case 'd':
      break;

    case 'h':
    case '?':
    default:
      print_help();
      continue; // while (running) ; skip printing board
    }

    printf("\nGeneration %d:\n", current_gen);
    display_board(&board);
  }

  puts("Thanks for playing!");

  return 0;
}
