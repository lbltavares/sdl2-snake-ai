#ifndef DEFINE_H
#define DEFINE_H

#define BACKGROUND_COLOR 20, 20, 20, 0

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define MAP_WIDTH 50
#define MAP_HEIGHT 50
#define MAP_TILE_WIDTH (SCREEN_WIDTH / MAP_WIDTH)
#define MAP_TILE_HEIGHT (SCREEN_HEIGHT / MAP_HEIGHT)

#define FPS 60
#define SNAKE_DELAY 500 // millis

#define MAX(x, y) x > y ? x : y
#define MIN(x, y) x < y ? x : y

#endif