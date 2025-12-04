// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 8 Linked Lists & Dynamic Memory Allocation in C _ I

#include <stdlib.h>

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>

#include "blockhead.h"

BLKHD_Blockhead *BLKHD_list_add(BLKHD_List *list) {
  // allocate new blockhead
  BLKHD_Blockhead *next = malloc(sizeof(BLKHD_Blockhead));
  if (next == NULL) {
    // early return if we can't allocate more, save user-list
    return NULL;
  }

  // put it in the front of the list
  next->next = list->data;

  // point the user-given list to new blockhead
  list->data = next;

  // return ptr to new blockhead
  return next;
}

void BLKHD_list_remove(BLKHD_List *list, unsigned int index) {
  if (list->data == NULL) {
    return;
  }

  BLKHD_Blockhead *head = list->data;

  // special case: remove from the front of the list
  if (index == 0) {
    list->data = head->next;
    free(head);
    return;
  }

  // navigate to index-1 or end of list
  for (; index > 1 && head->next != NULL; index--, head = head->next) {
    ;
  }

  // couldn't get to index-1 / list was too short
  if (index != 1 || head->next == NULL) {
    return;
  }

  BLKHD_Blockhead *match = head->next;

  // point the index-1 blockhead to the index+1 blockhead (or NULL if there was
  // no index+1)
  head->next = match->next;

  // free the old blockhead
  free(match);
}

void BLKHD_list_free(BLKHD_List *list) {
  BLKHD_Blockhead *bh = list->data;
  // walk through list freeing each blockhead
  for (BLKHD_Blockhead *next; bh != NULL; bh = next) {
    next = bh->next;
    free(bh);
  }

  list->data = NULL;
}

int BLKHD_list_len(BLKHD_List list) {
  int i = 1;
  if (list.data == NULL) {
    return 0;
  }

  for (; list.data->next != NULL; i++, list.data = list.data->next) {
    ;
  }

  return i;
}

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
  for (; list.data != NULL; list.data = list.data->next) {
    BLKHD_blockhead_update(list.data, bounds);
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

void BLKHD_list_render(BLKHD_List list, SDL_Renderer *renderer) {
  for (; list.data != NULL; list.data = list.data->next) {
    BLKHD_blockhead_render(list.data, renderer);
  }
}
