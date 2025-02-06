#pragma once

#include "snake.h"

typedef struct {
    int x;
    int y;
    char d;
    int cycles;
} food_t;

void update_food(food_t* food);

void is_food_eaten(food_t* food, snake_t* snake);

void kill_food(food_t* food);

food_t* create_food();

void place_food(food_t* food);

void print_food(food_t* food, int place);