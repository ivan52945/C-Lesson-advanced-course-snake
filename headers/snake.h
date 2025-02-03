#pragma once

#include "config.h"

#define N (WIDTH * HEIGHT)

typedef enum{
  LIVE = 1,
  DEAD = 0,
} status_t;

typedef enum {
  UP = 0,
  DOWN = 2,
  RIGHT = 1,
  LEFT = 3,
  WRONG = 4,
} dir_t;

typedef struct {
    int x;
    int y;
    char p;
} point_t;

typedef struct {
    int l;
    dir_t dir;
    point_t body[N];
    int hungry;
    status_t stats;
} snake_t;

snake_t* create_snake();

void check_death(snake_t* snake);

void update_direction(snake_t* snake, dir_t new_dir);

void move_or_grow_snake(snake_t* snake);

void grow_snake(snake_t* snake);

point_t* get_head(snake_t* snake);