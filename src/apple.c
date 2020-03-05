#include "define.h"
#include "apple.h"
#include "snake.h"

#include <stdlib.h>
#include <time.h>

void apple_init()
{
    apple_respawn();
}

void apple_find_place(SDL_Point *livres, int *qnt)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            SnakePart *tmp = snake.head;
            SDL_bool livre = SDL_TRUE;
            while (tmp != 0)
            {
                if (tmp->point.x == x && tmp->point.y == y)
                {
                    livre = SDL_FALSE;
                    break;
                }
                tmp = tmp->next;
            }
            if (livre)
            {
                livres[*qnt].x = x;
                livres[*qnt].y = y;
                (*qnt)++;
            }
        }
    }
}

void apple_respawn()
{
    SDL_Point livres[MAP_WIDTH * MAP_HEIGHT];
    int qnt = 0;
    apple_find_place(livres, &qnt);
    SDL_Point p = livres[rand() % qnt];
    apple.pos = p;
}

void apple_process_event(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN)
    {
        SDL_Keycode key = event->key.keysym.sym;
        if (key == SDLK_r)
        {
            apple_respawn();
        }
    }
}

void apple_update()
{
    if (apple.pos.x == snake.head->point.x && apple.pos.y == snake.head->point.y)
        apple_respawn();
}

void apple_render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, APPLE_COLOR);
    SDL_Rect rect;
    rect.w = MAP_TILE_WIDTH;
    rect.h = MAP_TILE_HEIGHT;
    rect.x = rect.w * apple.pos.x;
    rect.y = rect.h * apple.pos.y;
    SDL_RenderFillRect(renderer, &rect);
}

void apple_destroy()
{
}