// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 7

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_of_life.h"

// returns a random color, according to format.
Uint32 rand_color(const SDL_PixelFormat *format) {
  return SDL_MapRGB(format, rand() % 0x100, rand() % 0x100, rand() % 0x100);
}

int main(int argc, char **argv) {
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 600;

  SDL_Window *window = NULL;
  SDL_Surface *screen_surf = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    // notify and bail
    printf("SDL not initialized. SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    // notify, clean up, and bail
    printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  screen_surf = SDL_GetWindowSurface(window);
  if (!screen_surf) {
    // notify, clean up, and bail
    printf("Surface could not be accessed. SDL_Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  Uint32 background_color = SDL_MapRGB(screen_surf->format, 0x33, 0x33, 0x33);

  // initialize window
  SDL_FillRect(screen_surf, NULL, background_color);
  SDL_UpdateWindowSurface(window);

  // char mouse_button_state[2] = {0};

  Board gol_board;
  int initial_cells = 2000;
  int sim_active = 1;
  init_board(&gol_board, initial_cells);

  int running = 1;
  SDL_Event event;
  while (running) {
    while (running && SDL_PollEvent(&event)) {
      switch (event.type) {

      case SDL_QUIT:
        running = 0;
        continue; // eventloop

      case SDL_KEYDOWN: {
        switch (event.key.keysym.sym) {

        case SDLK_a: {
          // place 100 new live cells
          /*
          for (int rem_attempts = 1000, rem_cells = 100;
               rem_attempts && rem_cells; rem_attempts--) {
            rem_cells -= (gol_board.board_flat[rand() % sizeof(Board)] =
                              CELL_ALIVE) != CELL_DEAD;
          }
          */

          unsigned int indexes[sizeof(Board)];
          for (int i = 0; i < sizeof(Board); i++) {
            indexes[i] = i;
          }
          // shuffle
          for (int i = sizeof(Board) - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            int tmp = indexes[i];
            indexes[i] = indexes[j];
            indexes[j] = tmp;
          }

          for (int i = 0, rem_cells = 100; rem_cells > 0 && i < sizeof(Board);
               i++) {
            int idx = indexes[i];
            if (gol_board.board_flat[idx] != CELL_DEAD)
              continue;

            gol_board.board_flat[idx] = CELL_ALIVE;
            rem_cells -= 1;
          }
        } break;

        case SDLK_p:
          sim_active = !sim_active;
          break;

        case SDLK_r:
          init_board(&gol_board, initial_cells);
          break;

        case SDLK_s:
          if (!sim_active)
            next_generation(&gol_board);
          break;

        case SDLK_q:
        case SDLK_ESCAPE:
          running = 0;
          continue; // eventloop

        default:
          break;
        }
      } // SDL_KEYDOWN
      break;

      case SDL_WINDOWEVENT: {
        switch (event.window.event) {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
          screen_surf = SDL_GetWindowSurface(window);
          SDL_FillRect(screen_surf, NULL, background_color);
          break;
        }
      } break;

      case SDL_MOUSEBUTTONDOWN: {
        if (event.button.x > BOARD_WIDTH * 5 ||
            event.button.y > BOARD_HEIGHT * 5)
          break;

        if (event.button.button == SDL_BUTTON_LEFT) {
          gol_board.board[event.button.y / 5][event.button.x / 5] = CELL_ALIVE;
        } else if (event.motion.state == SDL_BUTTON_RIGHT) {
          gol_board.board[event.button.y / 5][event.button.x / 5] = CELL_DEAD;
        }
      } break;

      case SDL_MOUSEMOTION: {
        if (event.motion.x > BOARD_WIDTH * 5 ||
            event.motion.y > BOARD_HEIGHT * 5)
          break;

        if (event.motion.state & SDL_BUTTON_LMASK) {
          gol_board.board[event.motion.y / 5][event.motion.x / 5] = CELL_ALIVE;
        } else if (event.motion.state & SDL_BUTTON_RMASK) {
          gol_board.board[event.motion.y / 5][event.motion.x / 5] = CELL_DEAD;
        }
      } break;

      default:
        break;
      }
    }

    display_board(&gol_board, screen_surf);

    if (sim_active)
      next_generation(&gol_board);

    SDL_UpdateWindowSurface(window);
    SDL_Delay(20);
  }

  // clean up and exit
  SDL_DestroyWindow(window);
  SDL_Quit();
}
