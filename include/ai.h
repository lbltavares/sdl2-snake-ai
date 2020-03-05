#ifndef AI_H
#define AI_H

#include "SDL2/SDL.h"

void ai_create_map(int **map);
void ai_propagate_wave(int **map, int x, int y);
int ai_get_wave_map_xy(int **wave_map, int x, int y);
void ai_verify_location(int **wave_map, int x, int y, int *menor, SDL_Point *result);

#endif