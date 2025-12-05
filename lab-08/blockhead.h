// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 8 Linked Lists & Dynamic Memory Allocation in C

#ifndef BLKHD_BLOCKHEAD_H
#define BLKHD_BLOCKHEAD_H

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>

// greedy allocation growth factor for dynamic array
#define BLKHD_GROWTH_FACTOR 2

// Simple rgba color.
typedef struct BLKHD_Color {
  Uint8 r, g, b, a;
} BLKHD_Color;

// A little bouncy guy.
typedef struct BLKHD_Blockhead {
  // Pointer to next `BLKHD_Blockhead` in linked list. Not used by dynamic
  // array.
  struct BLKHD_Blockhead *next;

  // Position and velocity.
  float x, y;
  float dx, dy;

  // Size in px.
  unsigned int size;

  // Color.
  BLKHD_Color color;
} BLKHD_Blockhead;

// A list of `BLKHD_Blockhead`s
typedef struct BLKHD_List {
  BLKHD_Blockhead *data; // Used to hold initial pointer in linked list,
                         // data-array in dynamic array

  size_t cap, len; // Only used by dynamic array
} BLKHD_List;

// Append an empty blockhead to `list`, returning a pointer to the new
// item. The returned pointer may be invalidated on any later BLKHD function
// call involving non-const `list`.
BLKHD_Blockhead *BLKHD_list_add(BLKHD_List *list);

// Remove the blockhead at a given index from `list`.
void BLKHD_list_remove(BLKHD_List *list, unsigned int index);

// Free blockheads in `list`.
void BLKHD_list_free(BLKHD_List *list);

// Get the number of blockheads in `list`.
int BLKHD_list_len(const BLKHD_List *list);

// Update position of `blockhead` based on velocity and `bounds`. `blockhead`
// will bounce off of the walls of the bounding `SDL_Rect`.
void BLKHD_blockhead_update(BLKHD_Blockhead *blockhead, const SDL_Rect *bounds);

// Update position of each blockhead in `list`.
void BLKHD_list_update(const BLKHD_List *list, const SDL_Rect *bounds);

// Render `blockhead`.
void BLKHD_blockhead_render(const BLKHD_Blockhead *blockhead,
                            SDL_Renderer *renderer);

// Render each blockhead in `list`.
void BLKHD_list_render(const BLKHD_List *list, SDL_Renderer *renderer);

#endif
