#ifndef DEFINE_H
#define DEFINE_H


#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define MAP_TILE_WIDTH (SCREEN_WIDTH / MAP_WIDTH)
#define MAP_TILE_HEIGHT (SCREEN_HEIGHT / MAP_HEIGHT)

#define SOMBRAS 0
#define BACKGROUND_COLOR 30, 30, 30, 255
#define SNAKE_COLOR 32, 32, 32, 255
#define APPLE_COLOR SNAKE_COLOR

#define FPS 60
#define SNAKE_DELAY 500 // millis
#define SNAKE_INITIAL_DELAY 200

#define MAX(x, y) x > y ? x : y
#define MIN(x, y) x < y ? x : y

#endif