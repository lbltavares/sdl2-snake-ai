#ifndef APPLE_H
#define APPLE_H

#include "SDL2/SDL.h"

#define APPLE_COLOR 240, 40, 40, 255

typedef struct
{
    SDL_Point pos;
} Apple;

Apple apple;

void apple_init();
void apple_process_event(SDL_Event *event);
void apple_update();
void apple_render(SDL_Renderer *renderer);
void apple_destroy();
void apple_respawn();

void apple_find_place(SDL_Point *livres, int *qnt);

#endif