#ifndef WAVEMAP_H
#define WAVEMAP_H

#include "define.h"
#include "snake.h"
#include "SDL2/SDL.h"

typedef enum _types
{
    SOLID = -1,
    PATH = 0,
    SOURCE = 1,
} types;

void wm_prepare_map(int (*map)[MAP_HEIGHT]);
void wm_propagate(int (*map)[MAP_HEIGHT]);

void wm_print_map(int (*map)[MAP_HEIGHT]);

void wm_pick_path(int (*map)[MAP_HEIGHT], Snake *snake);

#endif