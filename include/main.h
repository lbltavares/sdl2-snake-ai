#ifndef MAIN_H
#define MAIN_H

#include "SDL2/SDL.h"

void render(SDL_Renderer *renderer);
void parse_events(SDL_Event *event);
void update();
void destroy();
void ai_play();
void init();

#endif