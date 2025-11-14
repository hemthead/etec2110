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

  window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED,
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

  Board gol_board;
  int sim_active = 1;
  init_board(&gol_board, 1000);

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

        case SDLK_r:
          // SDL_FillRect(screen_surf, NULL, rand_color(screen_surf->format));
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
      }

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
