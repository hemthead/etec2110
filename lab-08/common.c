// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 8 Linked Lists & Dynamic Memory Allocation in C

#include <SDL2/SDL_surface.h>
#include <math.h>

#include "blockhead.h"

void BLKHD_move_blockhead(BLKHD_Blockhead *blockhead, const SDL_Rect *bounds) {
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

void BLKHD_render_blockhead(const BLKHD_Blockhead *blockhead,
                            SDL_Surface *surface) {
  // background / base color
  SDL_Rect rect = {blockhead->x, blockhead->y, blockhead->size,
                   blockhead->size};
  SDL_FillRect(surface, &rect, blockhead->color);

  const int step = blockhead->size / 5;

  // help center the face, also offset toward direction of travel!
  rect.x += (blockhead->size % 5) / 2 +
            (int)ceil(fmax(-step + 2, fmin(blockhead->dx, step - 2)));
  rect.y += (blockhead->size % 5) / 2 +
            (int)ceil(fmax(-step + 2, fmin(blockhead->dy, step - 2)));

  // left eye
  rect.x += step;
  rect.y += step;
  rect.w = step;
  rect.h = step;
  SDL_FillRect(surface, &rect, 0x000000);

  // right eye
  rect.x += 2 * step;
  SDL_FillRect(surface, &rect, 0x000000);

  // mouth
  rect.x -= 2 * step;
  rect.y += 2 * step;
  rect.w = 3 * step;
  SDL_FillRect(surface, &rect, 0x000000);
}
