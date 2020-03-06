#ifndef DEFINE_H
#define DEFINE_H

#define BACKGROUND_COLOR 255, 255, 255, 255

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define MAP_TILE_WIDTH (SCREEN_WIDTH / MAP_WIDTH)
#define MAP_TILE_HEIGHT (SCREEN_HEIGHT / MAP_HEIGHT)

#define SNAKE_COLOR 245, 245, 245, 255
#define APPLE_COLOR 245, 245, 245, 255

#define FPS 60
#define SNAKE_DELAY 500 // millis
#define SNAKE_INITIAL_DELAY 200

#define MAX(x, y) x > y ? x : y
#define MIN(x, y) x < y ? x : y

#endif