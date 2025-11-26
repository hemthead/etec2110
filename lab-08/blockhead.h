// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 8 Linked Lists & Dynamic Memory Allocation in C

#ifndef BLKHD_BLOCKHEAD_H
#define BLKHD_BLOCKHEAD_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>

#define BLKHD_GROWTH_FACTOR 2

// A little bouncy guy.
typedef struct BLKHD_Blockhead {
  // Pointer to next `BLKHD_Blockhead` in linked list. Not used by dynamic array.
  struct BLKHD_Blockhead *next;
  // Position.
  float x, y;
  // Velocity.
  float dx, dy;
  // Color, as returned by `SDL_MapRGB`.
  Uint32 color;
  // Size in px.
  int size;
} BLKHD_Blockhead;

// A list of `BLKHD_Blockhead`s
typedef struct BLKHD_List {
  BLKHD_Blockhead *data; // Used to hold initial pointer in linked list,
                         // data-array in dynamic array
  size_t cap, len; // Only used by dynamic array
} BLKHD_List;

// Append an empty `BLKHD_Blockhead` to `list`, returning a pointer to the new
// item. The returned pointer may be invalidated on any later BLKHD function
// call involving non-const `list`.
BLKHD_Blockhead *BLKHD_add_to_list(BLKHD_List *list);

// Remove the `BLKHD_Blockhead` at a given index from `list`.
void BLKHD_remove_from_list(BLKHD_List *list, int index);

// Free `list` of `BLKHD_Blockhead`.
void BLKHD_free_list(BLKHD_List *list);

// Get the number of `BLKHD_Blockhead` in `list`.
int BLKHD_list_get_len(BLKHD_List list);

// Update position of `blockhead` based on velocity and `bounds`. `blockhead`
// will bounce off of the walls of the bounding `SDL_Rect`.
void BLKHD_move_blockhead(BLKHD_Blockhead *blockhead, const SDL_Rect *bounds);

// Update position of `list` of `BLKHD_Blockhead` based on velocity and
// `bounds`. `blockhead` will bounce off of the walls of the bounding
// `SDL_Rect`.
void BLKHD_move_list(BLKHD_List list, const SDL_Rect *bounds);

// Render `blockhead` to `surface`.
void BLKHD_render_blockhead(const BLKHD_Blockhead *blockhead,
                            SDL_Surface *surface);

// Render `list` of `BLKHD_Blockhead` to `surface`.
void BLKHD_render_list(const BLKHD_List list, SDL_Surface *surface);

#endif
