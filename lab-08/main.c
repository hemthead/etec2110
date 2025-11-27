// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 6 SDL Graphics in C

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "blockhead.h"

void randomize_blockhead(BLKHD_Blockhead *blockhead, SDL_Rect *bounds) {
  // Random opaque color
  blockhead->color.r = SDL_rand(256);
  blockhead->color.g = SDL_rand(256);
  blockhead->color.b = SDL_rand(256);
  blockhead->color.a = SDL_ALPHA_OPAQUE;

  // size \in [10, 20]
  blockhead->size = SDL_rand(11) + 10;

  // randomize position in bounding rect
  blockhead->x = SDL_rand(bounds->w - blockhead->size) + bounds->x;
  blockhead->y = SDL_rand(bounds->h - blockhead->size) + bounds->y;

  // 1D-velocities \in (-10, 10)
  blockhead->dx = (SDL_randf() - 0.5) * 20.0;
  blockhead->dy = (SDL_randf() - 0.5) * 20.0;
}

int main(int argc, char **argv) {
  int screen_width = 800;
  int screen_height = 600;

  SDL_Window *window = NULL;
  // SDL_Surface *screen_surf = NULL;
  SDL_Renderer *renderer = NULL;

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    // notify and bail
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "SDL could not be initialized: %s", SDL_GetError());
    return 1;
  }

  if (!SDL_CreateWindowAndRenderer("Blockheads!", screen_width, screen_height,
                                   SDL_WINDOW_RESIZABLE, &window, &renderer)) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "Window or Renderer could not be created: %s",
                    SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Rect bounds = {0, 0, screen_width, screen_height};
  bool sim_active = true;
  // initialize blockheads
  BLKHD_List blockheads = {0};
  for (int i = 0; i < 1000; i++) {
    BLKHD_Blockhead *bh = BLKHD_add_to_list(&blockheads);
    randomize_blockhead(bh, &bounds);
  }

  // keep track of position of last mousedown
  SDL_MouseButtonEvent mouse_down = {0};

  // simple, blocking eventloop
  bool running = true;
  SDL_Event event;
  while (running) {
    SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xFF);
    SDL_RenderFillRect(renderer, NULL);

    while (running && SDL_PollEvent(&event)) {
      switch (event.type) {

      case SDL_EVENT_QUIT:
        running = false;
        continue; // eventloop

      case SDL_EVENT_KEY_DOWN: {
        switch (event.key.key) {

        case SDLK_A:
          for (int i = 0; i < 10; i++) {
            BLKHD_Blockhead *bh = BLKHD_add_to_list(&blockheads);
            randomize_blockhead(bh, &bounds);
          }
          break;

        case SDLK_P:
          sim_active = !sim_active;
          break;

        case SDLK_R: {
          int len = BLKHD_list_get_len(blockheads);

          for (int i = 0; i < len; i++) {
            if (rand() % 10 == 0) {
              BLKHD_remove_from_list(&blockheads, i);
              len -= 1; // removing 1
            }
          }
        } break;

        case SDLK_Q:
        case SDLK_ESCAPE:
          running = false;
          continue; // eventloop

        default:
          continue;
        } // key symbol
      } break; // SDL_KEYDOWN

      case SDL_EVENT_WINDOW_RESIZED: {
        // screen_surf = SDL_GetWindowSurface(window);
        screen_width = event.window.data1;
        screen_height = event.window.data2;

        // reset background color each time and draw it
        // background_color = SDL_MapRGB(screen_surf->format, 0x33, 0x33,
        // 0x33); SDL_FillRect(screen_surf, NULL, background_color);
      } break;

      case SDL_EVENT_MOUSE_BUTTON_DOWN: {
        // set hovered cells alive/dead based on button pressed
        if (event.button.button == SDL_BUTTON_LEFT) {
          mouse_down = event.button;
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
        }
      } break;

      case SDL_EVENT_MOUSE_BUTTON_UP: {
        // set hovered cells alive/dead based on button pressed
        if (event.button.button == SDL_BUTTON_LEFT &&
            mouse_down.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
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

      default:
        continue; // eventloop
      } // event.type
    }

    // draw background (grey)
    SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // if the mouse is held, render line showing dv of pending block
    if (mouse_down.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      float x, y;
      SDL_GetMouseState(&x, &y);
      SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);

      // render line
      SDL_RenderLine(renderer, mouse_down.x, mouse_down.y, x, y);

      // render box where boxhead will show up
      // s = SDL_GetTicks() / 1000;
      // Period sin(s) = 2PI
      // Period sin(2s) = PI
      // Period sin(2PI * s) = 1
      // 2PI * s = SDL_GetTicks / (500/PI)
      const double PI = 3.14159;
      int size = sin(SDL_GetTicks() / (500.0/PI))*5 + 15; // period of 1s
      SDL_FRect rect;
      rect.x = mouse_down.x - size/2.0;
      rect.y = mouse_down.y - size/2.0;
      rect.w = size;
      rect.h = size;
      SDL_RenderRect(renderer, &rect);
    }

    bounds.w = screen_width;
    bounds.h = screen_height;

    if (sim_active)
      BLKHD_move_list(blockheads, &bounds);

    BLKHD_render_list(blockheads, renderer);

    // update screen
    // SDL_UpdateWindowSurface(window);
    SDL_RenderPresent(renderer);

    SDL_Delay(20);
  }

  // clean up and exit
  SDL_DestroyWindow(window);
  SDL_Quit();
}
