// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 8 Linked Lists & Dynamic Memory Allocation in C _ II

// #include <math.h>
#include <stddef.h>
#include <stdlib.h>

#include "blockhead.h"

BLKHD_Blockhead *BLKHD_list_add(BLKHD_List *list) {
  // if we've already got the memory, increment the length and return the last
  if (list->len < list->cap) {
    return &list->data[list->len++];
  }

  BLKHD_List new = {
      list->data,
      (list->cap + 1) * BLKHD_GROWTH_FACTOR,
      list->len,
  };

  new.data = reallocarray(new.data, new.cap, sizeof(BLKHD_Blockhead));

  if (new.data == NULL) {
    return NULL;
  }

  // update the list, increment the length, and return the last element
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

int BLKHD_list_len(const BLKHD_List *list) { return list->len; }

void BLKHD_list_update(const BLKHD_List *list, const SDL_Rect *bounds) {
  for (size_t i = 0; i < list->len; i++) {
    BLKHD_blockhead_update(&list->data[i], bounds);
  }
}

void BLKHD_list_render(const BLKHD_List *list, SDL_Renderer *renderer) {
  for (size_t i = 0; i < list->len; i++) {
    BLKHD_blockhead_render(&list->data[i], renderer);
  }
}
