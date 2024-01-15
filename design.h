#ifndef DESGIN
#define DESGIN

#include <stdio.h>
#include <stdlib.h>
#include "the-game.h"

/* ANSI Escape Codes for text color */
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define RESET   "\x1B[0m"

void clear_screen(void);
void print_field(char **field, int width, int height, int curser[]);
void spiel_anleitung(void);
void levels_of_difficulty(void);
void user_choice(int *width, int *height, float *percent_mines, int MAX_HEIGHT, int MAX_WIDTH, char *difficulty);
void print_minesweeper_art(void);
void printCenteredText(const char *text);



#endif
