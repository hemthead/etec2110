// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 5 Arrays and Functions

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game_of_life.h"

void print_help(void) {
  printf("Enter in a command to control the game.\n"
         "Commands:\n"
         "<ENTER>:\tstep forward by one generation.\n"
         "r <num>:\tstep forward by <num> generations.\n"
         "[q]uit, [e]xit:\tleave the game.\n"
         "[h]elp, ?:\tshow this help.\n");
}

int main(void) {
  srand(time(NULL));
  //srand(25);

  Board board;

  init_board(&board, 300);

  char input[16];
  int current_gen = 0;
  int running = 1;
  while (running) {
    printf("\nGeneration %d:\n", current_gen);
    display_board(&board);

    printf("Next command: ");
    fflush(stdout);

    // scanf(" %15[^\n]s", input);
    if (fgets(input, 16, stdin) == NULL) {
      break;
    }

    switch (input[0]) {
    case 'q':
    case 'Q':
    case 'e':
    case 'E':
      running = 0;
      break;

    case 'r': {
      int num_gens = 0;
      sscanf(input, "r %d", &num_gens);
      // printf("generations to run: %d\n", generations);

      for (; num_gens > 0; num_gens--, current_gen++) {
        next_generation(&board);
      }
    } break;

    case '\n':
      current_gen++;
      next_generation(&board);
      break;

    case 'h':
    case '?':
    default:
      print_help();
      break;
    }
  }

  puts("Thanks for playing!");

  return 0;
}
