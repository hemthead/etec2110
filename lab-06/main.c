#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_scancode.h>
#include <stdio.h>

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

Uint32 rand_color(const SDL_PixelFormat *format) {
  return SDL_MapRGB(format, rand() % 0x100, rand() % 0x100, rand() % 0x100);
}

int main(int argc, char **argv) {
  SDL_Window *window = NULL;
  SDL_Surface *screen_surf = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL not initialized. SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  screen_surf = SDL_GetWindowSurface(window);
  if (screen_surf == NULL) {
    printf("Surface could not be accessed. SDL_Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_FillRect(screen_surf, NULL, rand_color(screen_surf->format));

  int running = 1;
  while (running && SDL_WaitEvent(NULL)) {
    SDL_Event event;
    while (running && SDL_PollEvent(&event)) {
      switch (event.type) {

      case SDL_QUIT:
        running = 0;
        continue;

      case SDL_KEYDOWN: {
        switch (event.key.keysym.sym) {
        case SDLK_r:
          puts("random color");
          SDL_FillRect(screen_surf, NULL, rand_color(screen_surf->format));
          break;

        case SDLK_q:
        case SDLK_ESCAPE:
          puts("quit");
          running = 0;
          continue;
        }
        break;
      }

      default:
        break;
      }
    }

    SDL_UpdateWindowSurface(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
}
