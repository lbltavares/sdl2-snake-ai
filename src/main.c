#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "define.h"
#include "main.h"
#include "snake.h"
#include "ai.h"
#include "apple.h"

int pause = SDL_FALSE;
int mouse_pressed = 0, key_pressed = 0;
int running = 0;
long ticks = 0;

void init()
{
    snake_init();
    apple_init();
}

void update()
{
    if (pause)
        return;
    snake_update();
    apple_update();

    SDL_Point *ap = (SDL_Point *)SDL_malloc(sizeof(SDL_Point *));
    ap->x = apple.pos.x;
    ap->y = apple.pos.y;
    int wave_map[MAP_WIDTH][MAP_HEIGHT];
    ai_create_map(wave_map);
    ai_propagate_wave(wave_map, ap);
    

}

void render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR);
    SDL_RenderClear(renderer);

    apple_render(renderer);
    snake_render(renderer);

    SDL_RenderPresent(renderer);
}

void destroy()
{
    snake_destroy();
    apple_destroy();
}

void parse_events(SDL_Event *event)
{
    while (SDL_PollEvent(event))
    {
        if (event->type == SDL_QUIT)
            running = 0;
        else if (event->type == SDL_KEYUP)
        {
            SDL_Keycode key = event->key.keysym.sym;
            if (key == SDLK_p)
                pause = !pause;
        }
        snake_process_event(event);
        apple_process_event(event);
    }
}

int main(int argv, char *args[])
{
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL, &window, &renderer);
    init();
    running = 1;
    SDL_Event event;
    while (running)
    {
        if (ticks + 1000 / FPS > SDL_GetTicks())
            continue;
        ticks = SDL_GetTicks();
        parse_events(&event);
        update();
        render(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}