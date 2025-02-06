#include "snake.h"
#include <ncurses.h>
#include <stdlib.h>

static void print_snake(snake_t* snake, int print)
{
    for(int i = (snake->l - 1); i >= 0; --i){
        if(print)
            mvaddch(snake->body[i].y, snake->body[i].x, snake->body[i].p);
        else
            mvaddch(snake->body[i].y, snake->body[i].x, ' ');
    }
}

snake_t* create_snake()
{
    snake_t* snake = malloc(sizeof(snake_t));
    snake->l = 5;
    snake->stats = LIVE;
    snake->dir = UP;
    snake->hungry = 1;

    for(int i = 0; i < snake->l; ++i){
        snake->body[i].x = WIDTH / 2;
        snake->body[i].y = HEIGHT / 2 + i;
        snake->body[i].p = '#';
    }

    snake->body[0].p = '@';

    print_snake(snake, 1);

    return snake;
}

void check_death(snake_t* snake)
{
    int x_head = snake->body[snake->l - 1].x;
    int y_head = snake->body[snake->l - 1].y;

    if((x_head <= 0) || (x_head >= WIDTH)){
        snake->stats = DEAD;
        return;
    }
    if((y_head <= 0) || (y_head >= HEIGHT)){
        snake->stats = DEAD;
        return;
    }

    for(int i = 0; i < snake->l - 3; ++i){
        int x_body = snake->body[i].x;
        int y_body = snake->body[i].y;
        if(x_head == x_body && y_head == y_body){
            snake->stats = DEAD;
            return;
        }
    }
}

void update_direction(snake_t* snake, dir_t new_dir)
{
    if(new_dir == WRONG)
        return;

    if(((new_dir + snake->dir) % 2) != 0 )
        snake->dir = new_dir;
}

void move_snake(snake_t* snake)
{
    print_snake(snake, 0);

    for (int i = (snake->l - 1); i > 0 ; --i) {
        snake->body[i].x = snake->body[i - 1].x;
        snake->body[i].y = snake->body[i - 1].y;
    }

    switch (snake->dir) {
        case UP:
            snake->body[0].y -= 1;
            break;
        case DOWN:
            snake->body[0].y += 1;
            break;
        case LEFT:
            snake->body[0].x -= 1;
            break;
        case RIGHT:
            snake->body[0].x += 1;
            break;
        case WRONG:
            break;
    }

    print_snake(snake, 1);
}

void grow_snake(snake_t* snake)
{
    snake->body[snake->l] = snake->body[(snake->l) - 1];
    snake->l += 1;

    snake->hungry = 1;
}

point_t* get_head(snake_t* snake)
{
    return snake->body;
}