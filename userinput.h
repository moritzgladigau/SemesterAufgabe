#ifndef USER_INPUT
#define USER_INPUT

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define ESCAPE_KEY 27
#define UP_ARROW 65
#define DOWN_ARROW 66
#define LEFT_ARROW 67
#define RIGHT_ARROW 68
#define F_KEY 102
#define A_KEY 97

int getch(void);
int handle_arrow_keys(int input, int curser[], int width, int height);
int curser_move(int width, int height, int curser[]);

#endif
