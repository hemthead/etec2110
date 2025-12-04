// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 6 SDL Graphics in C

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "blockhead.h"

void randomize_blockhead(BLKHD_Blockhead *blockhead, SDL_Rect *bounds) {
  // Random opaque color
  BLKHD_Color color;
  color.r = SDL_rand(256);
  color.g = SDL_rand(256);
  color.b = SDL_rand(256);
  color.a = SDL_ALPHA_OPAQUE;

  // Keep colors light, to contrast better with darker background
  // if (avg_val < 100) invert color;
  if (color.r + color.g + color.b < 100 * 3) {
    color.r = 255 - color.r;
    color.g = 255 - color.g;
    color.b = 255 - color.b;
  }

  blockhead->color = color;

  // size \in [10, 20]
  blockhead->size = SDL_rand(11) + 10;

  // randomize position in bounding rect
  blockhead->x = SDL_rand(bounds->w - blockhead->size) + bounds->x;
  blockhead->y = SDL_rand(bounds->h - blockhead->size) + bounds->y;

  // 1D-velocities \in (-6, 6)
  blockhead->dx = (SDL_randf() - 0.5) * 12.0;
  blockhead->dy = (SDL_randf() - 0.5) * 12.0;
}

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Rect bounds;

// NOTE: These are no longer needed
#define INIT_SCREEN_WIDTH 800
#define INIT_SCREEN_HEIGHT 600
#define INIT_BLOCKHEAD_COUNT 30

BLKHD_List blockheads = {0};

bool sim_active = true;
bool vsync_enabled = false;

struct {
  float x, y;
  bool active;
} mouse_down;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    // notify and bail
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "SDL could not be initialized: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!SDL_CreateWindowAndRenderer("Blockheads!", INIT_SCREEN_WIDTH,
                                   INIT_SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE,
                                   &window, &renderer)) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "Window or Renderer could not be created: %s",
                    SDL_GetError());
    return SDL_APP_FAILURE;
  }

  SDL_srand(time(NULL));

  // vsync_enabled = SDL_SetRenderVSync(renderer, SDL_RENDERER_VSYNC_ADAPTIVE);
  SDL_SetRenderLogicalPresentation(renderer, INIT_SCREEN_WIDTH,
                                   INIT_SCREEN_HEIGHT,
                                   SDL_LOGICAL_PRESENTATION_DISABLED);

  bounds = (SDL_Rect){0, 0, INIT_SCREEN_WIDTH, INIT_SCREEN_WIDTH};

  // initialize blockheads
  for (int i = 0; i < INIT_BLOCKHEAD_COUNT; i++) {
    BLKHD_Blockhead *bh = BLKHD_list_add(&blockheads);
    randomize_blockhead(bh, &bounds);
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  switch (event->type) {

  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;

  case SDL_EVENT_KEY_DOWN: {
    switch (event->key.key) {

    case SDLK_A:
      // spawn 10 new blockheads
      for (int i = 0; i < 10; i++) {
        BLKHD_Blockhead *bh = BLKHD_list_add(&blockheads);
        randomize_blockhead(bh, &bounds);
      }
      break;

    case SDLK_SPACE:
    case SDLK_P:
      // pause sim
      sim_active = !sim_active;
      break;

    case SDLK_R: {
      int len = BLKHD_list_len(blockheads);

      for (int i = 0; i < len; i++) {
        if (SDL_rand(10) == 0) {
          BLKHD_list_remove(&blockheads, i);
          len -= 1; // removing 1
        }
      }
    } break;

    case SDLK_Q:
    case SDLK_ESCAPE:
      return SDL_APP_SUCCESS;

    default:
      return SDL_APP_CONTINUE;
    } // key symbol
  } break; // SDL_KEYDOWN

  case SDL_EVENT_MOUSE_BUTTON_DOWN: {
    if (event->button.button == SDL_BUTTON_LEFT) {
      SDL_ConvertEventToRenderCoordinates(renderer, event);
      mouse_down.active = true;
      mouse_down.x = event->button.x;
      mouse_down.y = event->button.y;
    }
  } break;

  case SDL_EVENT_MOUSE_BUTTON_UP: {
    if (event->button.button == SDL_BUTTON_LEFT && mouse_down.active) {
      SDL_ConvertEventToRenderCoordinates(renderer, event);

      // add new blockhead centered on initial click position, with velocity
      // based on vector to that position
      BLKHD_Blockhead *bh = BLKHD_list_add(&blockheads);
      randomize_blockhead(bh, &bounds);
      bh->x = mouse_down.x - (bh->size / 2.0);
      bh->y = mouse_down.y - (bh->size / 2.0);
      bh->dx = (mouse_down.x - event->button.x) / 10.0;
      bh->dy = (mouse_down.y - event->button.y) / 10.0;

      // no longer clicking
      mouse_down.active = false;
    }
  } break;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  Uint64 frame_start = SDL_GetTicksNS();

  // draw background (grey)
  SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  // update bounds based to be what's visible
  SDL_GetRenderViewport(renderer, &bounds);

  // get state of mouse this frame
  float mouse_x, mouse_y;
  SDL_MouseButtonFlags mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);
  SDL_RenderCoordinatesFromWindow(renderer, mouse_x, mouse_y, &mouse_x,
                                  &mouse_y);

  // remove blockheads under mouse when right clicking
  if (mouse_state & SDL_BUTTON_RMASK && blockheads.data != NULL) {
    // NOTE: Right now this has a separate implementation for each type of list,
    // which is kinda antithetical to my personal goal of making a single
    // interface...

    BLKHD_Blockhead *bh;

    // having cap of 0 means that this either isn't an array or isn't
    // initialized anyway (in which case the NULL check will have already
    // skipped
    if (blockheads.cap == 0) {
      // WARNING: LList implementation only
      // walk through list freeing each blockhead that fits criteria
      for (BLKHD_Blockhead *prev = blockheads.data; prev->next != NULL;
           prev = prev->next) {
        bh = prev->next;
        if ((bh->x < mouse_x && mouse_x < bh->x + bh->size) &&
            (bh->y < mouse_y && mouse_y < bh->y + bh->size)) {
          prev->next = bh->next;
          free(bh);
        }
      }
    } else {
      // WARNING: Array implementation only
      // walk through list freeing each blockhead that fits criteria
      for (int i = 0; i < blockheads.len; i++) {
        bh = &blockheads.data[i];
        if ((bh->x < mouse_x && mouse_x < bh->x + bh->size) &&
            (bh->y < mouse_y && mouse_y < bh->y + bh->size)) {
          BLKHD_list_remove(&blockheads, i);
        }
      }
    }
  }

  if (sim_active) {
    BLKHD_list_update(blockheads, &bounds);
  }

  BLKHD_list_render(blockheads, renderer);

  // if the mouse is held, render line showing dv of pending blockhead, and a
  // nice animation indicating where the blockhead will spawn
  if (mouse_down.active) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);

    // render line
    SDL_RenderLine(renderer, mouse_down.x, mouse_down.y, mouse_x, mouse_y);

    // render box where boxhead will show up
    // s = SDL_GetTicks() / 1000;
    // Period sin(s) = 2PI
    // Period sin(2s) = PI
    // Period sin(2PI * s) = 1
    // 2PI * s = SDL_GetTicks / (500/PI)
    float size = sin(SDL_GetTicks() / (500.0 / M_PI)) * 5 + 15; // period of 1s
    SDL_FRect rect;
    rect.x = mouse_down.x - size / 2.0;
    rect.y = mouse_down.y - size / 2.0;
    rect.w = size;
    rect.h = size;
    SDL_RenderRect(renderer, &rect);
  }

  SDL_RenderPresent(renderer);

  // run at 60fps max
  Uint64 elapsed_time = SDL_GetTicksNS() - frame_start;
  Uint64 nsPerFrame = 1000000000 / 60;
  if (elapsed_time < nsPerFrame) {
    SDL_DelayNS(nsPerFrame - elapsed_time);
  }

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  // clean up and exit
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  BLKHD_list_free(&blockheads);
}
