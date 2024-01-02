#ifndef THE_GAME
#define THE_GAME

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MINE 'M'

char **field_init(int width, int height);
int place_a_mine(char **field, int perpercent_mines, int width, int height);
int mines_nearby(char **field, int width, int height, int x, int y);
int place_numbers(char **field, int width, int height);
int fill_field(char **field, int width, int height);
void print_field(char **field, int width, int height);

#endif
