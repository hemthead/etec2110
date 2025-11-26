// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 6 SDL Graphics in C

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "blockhead.h"

void randomize_blockhead(BLKHD_Blockhead *blockhead, SDL_Rect *bounds) {
  blockhead->color = rand() % 0x1000000;
  blockhead->size = (rand() % 11) + 10; // 10..=20
  blockhead->x = (rand() % (bounds->w - blockhead->size)) + bounds->x;
  blockhead->y = (rand() % (bounds->h - blockhead->size)) + bounds->y;
  blockhead->dx = ((rand() % 2000) - 1000) / 100.0;
  blockhead->dy = ((rand() % 2000) - 1000) / 100.0;
}

int main(int argc, char **argv) {
  srand(time(NULL));

  int screen_width = 800;
  int screen_height = 600;

  SDL_Window *window = NULL;
  SDL_Surface *screen_surf = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    // notify and bail
    printf("SDL not initialized. SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, screen_width,
                            screen_height, SDL_WINDOW_RESIZABLE);
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

  // initialize background
  Uint32 background_color = SDL_MapRGB(screen_surf->format, 0x33, 0x33, 0x33);
  SDL_FillRect(screen_surf, NULL, background_color);

  SDL_Rect bounds = {0, 0, screen_width, screen_height};
  bool sim_active = true;
  // initialize blockheads
  BLKHD_List blockheads = {NULL};
  for (int i = 0; i < 30; i++) {
    BLKHD_Blockhead *bh = BLKHD_add_to_list(&blockheads);
    randomize_blockhead(bh, &bounds);
  }
  /*
  BLKHD_add_to_list(&blockheads);
  blockheads->color = 0x000000;
  blockheads->size = 50;
  blockheads->x = 0;
  blockheads->y = 0;
  blockheads->dx = 10;
  blockheads->dy = 1;
  BLKHD_add_to_list(&blockheads);
  blockheads->color = 0xFF0000;
  blockheads->size = 12;
  blockheads->x = 10;
  blockheads->y = 5;
  blockheads->dx = 4;
  blockheads->dy = 8;
  */

  // SDL_UpdateWindowSurface(window);

  // keep track of position of last mousedown
  SDL_MouseButtonEvent mouse_down = {0};

  // simple, blocking eventloop
  bool running = true;
  SDL_Event event;
  while (running) {
    while (running && SDL_PollEvent(&event)) {
      switch (event.type) {

      case SDL_QUIT:
        running = false;
        continue; // eventloop

      case SDL_KEYDOWN: {
        switch (event.key.keysym.sym) {

        case SDLK_a:
          for (int i = 0; i < 10; i++) {
            BLKHD_Blockhead *bh = BLKHD_add_to_list(&blockheads);
            randomize_blockhead(bh, &bounds);
          }
          break;

        case SDLK_p:
          sim_active = !sim_active;
          break;

        case SDLK_r: {
          int len = BLKHD_list_get_len(blockheads);

          for (int i = 0; i < len; i++) {
            if (rand() % 10 == 0) {
              BLKHD_remove_from_list(&blockheads, i);
              len -= 1; // removing 1
            }
          }
        } break;

        case SDLK_q:
        case SDLK_ESCAPE:
          running = false;
          continue; // eventloop

        default:
          continue;
        } // key symbol
      } break; // SDL_KEYDOWN

      case SDL_WINDOWEVENT: {
        switch (event.window.event) {

        case SDL_WINDOWEVENT_RESIZED:
          screen_surf = SDL_GetWindowSurface(window);
          screen_width = event.window.data1;
          screen_height = event.window.data2;

          // reset background color each time and draw it
          background_color = SDL_MapRGB(screen_surf->format, 0x33, 0x33, 0x33);
          SDL_FillRect(screen_surf, NULL, background_color);
          break;

        default:
          continue;
        } // window.event
      } break; // SDL_WINDOWEVENT

      case SDL_MOUSEBUTTONDOWN: {
        // set hovered cells alive/dead based on button pressed
        if (event.button.button == SDL_BUTTON_LEFT) {
          mouse_down = event.button;
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
        }
      } break;

      case SDL_MOUSEBUTTONUP: {
        // set hovered cells alive/dead based on button pressed
        if (event.button.button == SDL_BUTTON_LEFT &&
            mouse_down.type == SDL_MOUSEBUTTONDOWN) {
          BLKHD_Blockhead *bh = BLKHD_add_to_list(&blockheads);
          randomize_blockhead(bh, &bounds);
          bh->x = mouse_down.x - (bh->size / 2.0);
          bh->y = mouse_down.y - (bh->size / 2.0);
          bh->dx = (mouse_down.x - event.button.x) / 10.0;
          bh->dy = (mouse_down.y - event.button.y) / 10.0;

          mouse_down = event.button;
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
        }
      } break;

      case SDL_MOUSEMOTION: {
        if (event.motion.state & SDL_BUTTON_LMASK && mouse_down.type == SDL_MOUSEBUTTONDOWN) {
            // TODO: draw a line showing direction and magnitude (velocity) and stuff!
        } else if (event.motion.state & SDL_BUTTON_RMASK) {
        }
      } break;

      default:
        continue; // eventloop
      } // event.type
    }

    SDL_FillRect(screen_surf, NULL, background_color);

    bounds.w = screen_width;
    bounds.h = screen_height;

    if (sim_active)
      BLKHD_move_list(blockheads, &bounds);

    BLKHD_render_list(blockheads, screen_surf);

    // update screen
    SDL_UpdateWindowSurface(window);

    SDL_Delay(20);
  }

  // clean up and exit
  SDL_DestroyWindow(window);
  SDL_Quit();
}
