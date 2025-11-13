// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 6 SDL Graphics in C

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

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

  // initialize window
  SDL_FillRect(screen_surf, NULL, rand_color(screen_surf->format));
  SDL_UpdateWindowSurface(window);

  int running = 1;
  SDL_Event event;
  while (running && SDL_WaitEvent(&event)) {
    switch (event.type) {

    case SDL_QUIT:
      running = 0;
      continue; // eventloop

    case SDL_KEYDOWN: {
      switch (event.key.keysym.sym) {

      case SDLK_r:
        SDL_FillRect(screen_surf, NULL, rand_color(screen_surf->format));
        SDL_UpdateWindowSurface(window);
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

    default:
      break;
    }
  }

  // clean up and exit
  SDL_DestroyWindow(window);
  SDL_Quit();
}
