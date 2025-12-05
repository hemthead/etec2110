// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 8 Linked Lists & Dynamic Memory Allocation in C _ I

#include <stdlib.h>

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

  // point the user-given list to start at new blockhead
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

int BLKHD_list_len(const BLKHD_List *list) {
  int i = 1;
  if (list->data == NULL) {
    return 0;
  }

  for (BLKHD_Blockhead *bh = list->data; bh->next != NULL; i++, bh = bh->next) {
    ;
  }

  return i;
}

void BLKHD_list_update(const BLKHD_List *list, const SDL_Rect *bounds) {
  for (BLKHD_Blockhead *bh = list->data; bh != NULL; bh = bh->next) {
    BLKHD_blockhead_update(bh, bounds);
  }
}

void BLKHD_list_render(const BLKHD_List *list, SDL_Renderer *renderer) {
  for (BLKHD_Blockhead *bh = list->data; bh != NULL; bh = bh->next) {
    BLKHD_blockhead_render(bh, renderer);
  }
}
