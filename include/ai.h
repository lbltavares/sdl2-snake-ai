#ifndef AI_H
#define AI_H

#include "define.h"
#include "SDL2/SDL.h"

void ai_create_map(int (*)[MAP_HEIGHT]);
void ai_propagate_wave(int (*)[MAP_HEIGHT], SDL_Point *p);

int ai_get_wave_map_xy(int (*)[MAP_HEIGHT], int x, int y);
void ai_verify_location(int (*)[MAP_HEIGHT], int x, int y, int *menor, SDL_Point *result);

SDL_Point ai_get_next_move(int (*)[MAP_HEIGHT], int x, int y);

#endif