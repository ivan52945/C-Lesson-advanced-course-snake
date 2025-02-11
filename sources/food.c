#include "food.h"
#include "snake.h"
#include <ncurses.h>
#include "config.h"
#include <stdlib.h>

void update_food(food_t* food)
{
    if(!food->cycles)
        return;

    if(food->cycles > FOOD_CYCLES){
        kill_food(food);
        return;
    }

    ++food->cycles;
    print_food(food, 1);
}

void is_food_eaten(food_t* food, snake_t* snake)
{
    point_t* head = get_head(snake);

    if((head->x != food->x) || (head->y != food->y))
        return;

    snake->hungry = 0;
    kill_food(food);
}

void place_food(food_t* food, snake_t* snake)
{
    if(food == NULL)
        return;

    food->d = '&';
    food->cycles = 1;
    do {
        food->y = (rand() % (HEIGHT - 2)) + 2;
        food->x = (rand() % (WIDTH - 2)) + 2;
    } while(is_filled(snake, food->x, food->y));
}

food_t* create_food(snake_t* snake)
{
    food_t* food = malloc(sizeof(food_t));
    place_food(food, snake);
    return  food;
}

void kill_food(food_t* food)
{
    print_food(food, 0);
    food->x = 0;
    food->y = 0;
    food->cycles = 0;
}

void print_food(food_t* food, int place)
{
    if(place)
        mvaddch(food->y, food->x, food->d);
    else
        mvaddch(food->y, food->x, ' ');
}