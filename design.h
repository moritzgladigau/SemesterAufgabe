#ifndef DESGIN
#define DESGIN

#include <stdio.h>
#include <stdlib.h>

void clear_screen(void);
void print_field(char **field, int width, int height, int curser[]);
void spiel_anleitung(void);
void levels_of_difficulty(void);
void user_choice(int width, int height, float percent_mines, int MAX_HEIGHT, int MAX_WIDTH);


#endif
