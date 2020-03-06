#ifndef DEFINE_H
#define DEFINE_H

#define BACKGROUND_COLOR 20, 20, 20, 0

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define MAP_WIDTH 5
#define MAP_HEIGHT 5
#define MAP_TILE_WIDTH (SCREEN_WIDTH / MAP_WIDTH)
#define MAP_TILE_HEIGHT (SCREEN_HEIGHT / MAP_HEIGHT)

#define SNAKE_COLOR 70, 70, 70, 255
#define APPLE_COLOR 90, 90, 90, 255

#define FPS 60
#define SNAKE_DELAY 500 // millis
#define SNAKE_INITIAL_DELAY 200

#define MAX(x, y) x > y ? x : y
#define MIN(x, y) x < y ? x : y

#endif