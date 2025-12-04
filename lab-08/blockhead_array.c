// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 8 Linked Lists & Dynamic Memory Allocation in C _ II

// #include <math.h>
#include <stddef.h>
#include <stdlib.h>

#include <SDL3/SDL_surface.h>

#include "blockhead.h"

BLKHD_Blockhead *BLKHD_list_add(BLKHD_List *list) {
  if (list->len < list->cap) {
    return &list->data[list->len++];
  }

  BLKHD_List new = {list->data, (list->cap + 1) * BLKHD_GROWTH_FACTOR,
                    list->len};

  new.data = reallocarray(new.data, new.cap, sizeof(BLKHD_Blockhead));

  if (new.data == NULL) {
    return NULL;
  }

  *list = new;
  return &list->data[list->len++];
}

void BLKHD_list_remove(BLKHD_List *list, unsigned int index) {
  if (list->len < 2) {
    list->len = 0;
    return;
  }

  // unordered swap
  list->data[index] = list->data[--list->len];
}

void BLKHD_list_free(BLKHD_List *list) { free(list->data); }

inline int BLKHD_list_len(BLKHD_List list) { return list.len; }

/*
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

  blockhead->x = fmax(blockhead->x, bounds->x);
  blockhead->x = fmin(blockhead->x, bounds->x + bounds->w - blockhead->size);

  blockhead->y = fmax(blockhead->y, bounds->y);
  blockhead->y = fmin(blockhead->y, bounds->y + bounds->h - blockhead->size);
}
*/

void BLKHD_list_update(BLKHD_List list, const SDL_Rect *bounds) {
  for (size_t i = 0; i < list.len; i++) {
    BLKHD_blockhead_update(&list.data[i], bounds);
  }
}

/*
void BLKHD_render_blockhead(const BLKHD_Blockhead *blockhead,
                            SDL_Surface *surface) {
  SDL_Rect rect = {blockhead->x, blockhead->y, blockhead->size,
                   blockhead->size};
  SDL_FillRect(surface, &rect, blockhead->color);
}
*/

void BLKHD_list_render(BLKHD_List list, // SDL_Surface *surface) {
                       SDL_Renderer *renderer) {
  for (size_t i = 0; i < list.len; i++) {
    BLKHD_blockhead_render(&list.data[i], renderer);
  }
}
