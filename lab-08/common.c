// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 8 Linked Lists & Dynamic Memory Allocation in C

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <math.h>

#include "blockhead.h"

void BLKHD_blockhead_update(BLKHD_Blockhead *blockhead,
                            const SDL_Rect *bounds) {
  // add velocity vector
  blockhead->x += blockhead->dx;
  blockhead->y += blockhead->dy;

  // Reverse vector components upon collision
  if (blockhead->x <= bounds->x ||
      blockhead->x >= bounds->x + bounds->w - blockhead->size) {
    blockhead->dx = -blockhead->dx;
  }
  if (blockhead->y <= bounds->y ||
      blockhead->y >= bounds->y + bounds->h - blockhead->size) {
    blockhead->dy = -blockhead->dy;
  }

  // bound coordinates inside rectangle
  blockhead->x = fmax(blockhead->x, bounds->x);
  blockhead->x = fmin(blockhead->x, bounds->x + bounds->w - blockhead->size);

  blockhead->y = fmax(blockhead->y, bounds->y);
  blockhead->y = fmin(blockhead->y, bounds->y + bounds->h - blockhead->size);
}

void BLKHD_blockhead_render(const BLKHD_Blockhead *blockhead,
                            SDL_Renderer *renderer) {
  // Blockhead:
  //   <--size-->
  // A ##########
  // | ##  ##  ##
  // s ##########
  // | ##      ##
  // V ########## ]
  //   []         |
  //     \ one fifth of size

  // rectangles to use for face
  SDL_FRect rects[3] = {};

  // background / base color
  rects[0].x = blockhead->x;
  rects[0].y = blockhead->y;
  rects[0].w = blockhead->size;
  rects[0].h = blockhead->size;
  SDL_SetRenderDrawColor(renderer, blockhead->color.r, blockhead->color.g,
                         blockhead->color.b, blockhead->color.a);
  SDL_RenderFillRect(renderer, &rects[0]);

  // start drawing face features

  const float step = blockhead->size / 5.0;

  // offset face toward direction of travel!
  rects[0].x += (fmax(-step / 2, fmin(blockhead->dx, step / 2)));
  rects[0].y += (fmax(-step / 2, fmin(blockhead->dy, step / 2)));

  // left eye
  rects[0].x += step;
  rects[0].y += step;
  rects[0].w = step;
  rects[0].h = step;

  // right eye
  rects[1].x = rects[0].x + 2 * step;
  rects[1].y = rects[0].y;
  rects[1].w = step;
  rects[1].h = step;

  // mouth
  rects[2].x = rects[0].x;
  rects[2].y = rects[0].y + 2 * step;
  rects[2].w = 3 * step;
  rects[2].h = step;

  // render face rects together
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRects(renderer, rects, 3);
}
