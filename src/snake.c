#include "define.h"
#include "snake.h"
#include "apple.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// (Re)inicia a snake:
void snake_init()
{
    snake.head = 0;
    snake_respawn();
}

void snake_respawn()
{
    snake_destroy();
    snake.must_grow = SDL_FALSE;
    snake.head = (SnakePart *)SDL_malloc(sizeof(SnakePart *));
    snake.head->point.x = rand() % MAP_WIDTH;
    snake.head->point.y = rand() % MAP_HEIGHT;
    snake.head->next = 0;
    snake.time = SDL_GetTicks();
    snake.delay = SNAKE_INITIAL_DELAY;
    snake_set_direction(1, 0);
}

// Ajusta a direção do snake:
void snake_set_direction(int x, int y)
{
    if (snake.head->next != 0)
    {
        SDL_Point dest = {x + snake.head->point.x,
                          y + snake.head->point.y};
        SnakePart *next = snake.head->next;
        if (next->point.x == dest.x && next->point.y == dest.y)
            return;
    }
    snake.direction.x = x;
    snake.direction.y = y;
}

void snake_move(SnakePart *part, SDL_Point *dest)
{
    if (part->next != 0)
        snake_move(part->next, &part->point);
    SDL_Point tmp = {part->point.x, part->point.y};
    part->point.x = dest->x;
    part->point.y = dest->y;
    return;
}

// Atualiza a snake a cada frame:
void snake_update()
{
    // Delay:
    if (snake.time + snake.delay > SDL_GetTicks())
        return;
    snake.time = SDL_GetTicks();

    // Obtem o destino da snake:
    SDL_Point dest = {snake.head->point.x + snake.direction.x,
                      snake.head->point.y + snake.direction.y};

    // Verifica se comeu a maça e precisa crescer:
    if (apple.pos.x == dest.x && apple.pos.y == dest.y)
        snake.must_grow = SDL_TRUE;

    // Movimenta ou cresce a snake:
    if (snake.must_grow)
        _snake_grow();
    else
        snake_move(snake.head, &dest);

    // Verifica morte:
    if (snake_is_dead())
    {
        snake_respawn();
        return;
    }
}

// Renderiza a snake:
void snake_render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, SNAKE_COLOR);
    SnakePart *part = snake.head;
    while (part != 0)
    {
        SDL_Rect rect;
        rect.w = MAP_TILE_WIDTH;
        rect.h = MAP_TILE_HEIGHT;
        rect.x = rect.w * part->point.x;
        rect.y = rect.h * part->point.y;
        SDL_RenderFillRect(renderer, &rect);
        part = part->next;
    }
    part = 0;
}

// Adiciona uma parte a snake:
void _snake_grow()
{
    SnakePart *p = (SnakePart*)SDL_malloc(sizeof(SnakePart *));
    p->next = snake.head;
    p->point.x = snake.head->point.x + snake.direction.x;
    p->point.y = snake.head->point.y + snake.direction.y;
    snake.head = p;
    p = 0;
    snake.must_grow = SDL_FALSE;
}

// Aciona o crescimento da snake no próximo update:
void snake_grow()
{
    snake.must_grow = SDL_TRUE;
}

// Verifica se a snake morreu:
SDL_bool snake_is_dead()
{
    SnakePart *p = snake.head;
    if (p->point.x < 0 || p->point.y < 0 || p->point.x >= MAP_WIDTH || p->point.y >= MAP_HEIGHT)
        return SDL_TRUE;
    p = p->next;
    while (p != 0)
    {
        if (snake.head->point.x == p->point.x && snake.head->point.y == p->point.y)
            return SDL_TRUE;
        p = p->next;
    }
    return SDL_FALSE;
}

// Processa eventos de entrada:
void snake_process_event(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN)
    {
        SDL_Keycode key = event->key.keysym.sym;
        if (key == SDLK_UP)
        {
            snake_set_direction(0, -1);
        }
        else if (key == SDLK_DOWN)
        {
            snake_set_direction(0, 1);
        }
        else if (key == SDLK_LEFT)
        {
            snake_set_direction(-1, 0);
        }
        else if (key == SDLK_RIGHT)
        {
            snake_set_direction(1, 0);
        }
        else if (key == SDLK_g)
        {
            snake_grow();
        }
        else if (key == SDLK_LSHIFT)
        {
            snake.delay = 50;
        }
    }
    else if (event->type == SDL_KEYUP)
    {
        SDL_Keycode key = event->key.keysym.sym;
        if (key == SDLK_LSHIFT)
        {
            snake.delay = SNAKE_INITIAL_DELAY;
        }
    }
}

// Apaga e libera todas as partes da snake:
void snake_erase_parts(SnakePart *part)
{
    if (part == 0)
        return;
    snake_erase_parts(part->next);
    free(part);
}

// Realiza a limpeza da memória alocada:
void snake_destroy()
{
    snake_erase_parts(snake.head);
    snake.head = 0;
}