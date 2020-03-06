#ifndef SNAKE_H
#define SNAKE_H

#include "SDL2/SDL.h"

typedef struct _SnakePart
{
    SDL_Point point;
    struct _SnakePart *next;
} SnakePart;

typedef struct
{
    int delay;
    SDL_bool must_grow;
    Uint32 time;
    SnakePart *head;
    SDL_Point direction;
} Snake;

Snake snake;

void snake_init();
void snake_process_event(SDL_Event *event);
void snake_update();
void snake_render(SDL_Renderer *renderer);
void snake_destroy();

void snake_respawn();
void snake_erase_parts(SnakePart *part);

SDL_bool snake_is_dead();

void snake_move(SnakePart *part, SDL_Point *dest);
void snake_set_direction(int x, int y);

void _snake_grow();
void snake_grow();

#endif