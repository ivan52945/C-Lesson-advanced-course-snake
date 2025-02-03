#include "game.h"
#include <time.h>
#include "food.h"
#include "game_field.h"
#include "snake.h"
#include <stdlib.h>
#include "config.h"
#include <ncurses.h>

static dir_t control_snake(char c, dir_t dir)
{
    switch (c) {
        case 'w':
        case 'W':
            return UP;
        case 'a':
        case 'A':
            return LEFT;
        case 's':
        case 'S':
            return DOWN;
        case 'd':
        case 'D':
            return RIGHT;
    }
    return dir;
}

static void end(void)
{
    char *end_arr[] = {
            "########################",
            "#                      #",
            "#       YOU LOSE       #",
            "#                      #",
            "########################",
    };

    int y_high = HEIGHT / 2 - (sizeof(end_arr) / sizeof(end_arr[0]) / 2);
    int x_left = WIDTH / 2 - (sizeof(end_arr[0]));

    timeout(10000);

    for(int i = 0; i < 5; ++i){
        mvprintw(y_high + i, x_left, "%s", end_arr[i]) ;
    }

    getch();
}

void start_game(void)
{
    initscr();

    raw();
    curs_set(0);
    noecho();

    food_t* food = create_food();
    print_field(WIDTH, HEIGHT, '#');
    snake_t* snake = create_snake();

    dir_t dir = snake->dir;
    clock_t prew_tick = clock();
    int cycle_without_food = 0;

    getch();
    timeout(0);

    while(1) {
        char c = getch();

        dir = control_snake(c, dir);

        if (c == 'q')
            break;

        if ((double) (clock() - prew_tick) * 8 < CLOCKS_PER_SEC)
            continue;

        prew_tick = clock();

        update_direction(snake, dir);

        check_food(food, snake);

        if (!food->cycles)
            ++cycle_without_food;

        if (cycle_without_food > 10) {
            cycle_without_food = 0;
            place_food(food);
        }

        move_or_grow_snake(snake);

        check_death(snake);

        if (snake->stats == DEAD) {
            end();
            break;
        }
    }

    endwin();
    free(snake);
    free(food);
}