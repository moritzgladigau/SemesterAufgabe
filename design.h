#ifndef DESGIN
#define DESGIN

#include <stdio.h>
#include <stdlib.h>
#include "the-game.h"
#include "log.h"

/* ANSI Escape Codes for text color */
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define RESET   "\x1B[0m"

#define UNDERLINE "\033[4m"
#define BOLD "\033[1m"

void clear_screen(void);
void print_field(char **field, int width, int height, int curser[]);
void spiel_anleitung(void);
void levels_of_difficulty(void);
void menu_options(void);
void user_choice(int *width, int *height, float *percent_mines, int MAX_HEIGHT, int MAX_WIDTH, char *difficulty);
void print_minesweeper_art(void);
void printCenteredText(const char *text);

void tabel_menu_options(void);
void tabel_menu(void);
void scorboard(void);
int countDigits(int num);
void log_content(void);
void log_menue(void);

void pic_win(void);
void pic_lose(void);

#endif
