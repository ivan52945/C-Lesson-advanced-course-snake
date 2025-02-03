#include "game_field.h"
#include <ncurses.h>

void print_field(int w, int h, char wall)
{
    for(int j = 0; j < (w + 1); ++j){
        mvaddch(0, j, wall);
        mvaddch(h, j, wall);
    }

    for(int i = 1; i < h; ++i){
        mvaddch(i, 0, wall);
        mvaddch(i, w, wall);
    }
}