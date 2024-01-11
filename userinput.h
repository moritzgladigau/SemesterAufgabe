#ifndef USER_INPUT
#define USER_INPUT

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define ESCAPE_KEY 27
#define UP_ARROW 'w'
#define DOWN_ARROW 's'
#define LEFT_ARROW 'a'
#define RIGHT_ARROW 'd'
#define FLAG_KEY 'f'
#define OPEN_KEY 'o'

int getch(void);
int handle_arrow_keys(int input, int curser[], int width, int height);
int curser_move(int width, int height, int curser[]);

#endif
