#ifndef THE_GAME
#define THE_GAME

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MINE 'M'
#define WIN 0
#define LOSE -1
#define CONTINUE 1

extern int total_number_of_mine;

char **field_init(int width, int height);
int place_a_mine(char **field, int perpercent_mines, int width, int height);
int mines_nearby(char **field, int width, int height, int x, int y);
void place_numbers(char **field, int width, int height);
void fill_field(char **field, int width, int height);

int check_if_done(char **afield, char **cfield, int width, int height);
void open_surrounding(char **afield, char **cfield, int width, int height, int curser[]);
void open(char **afield, char **cfield, int width, int height, int x, int y);





#endif
