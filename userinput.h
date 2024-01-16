#ifndef USER_INPUT
#define USER_INPUT

#include <stdio.h>
#include <stdlib.h>

#define PROGRAM_FINISH Q_KEY

#define ESCAPE_KEY 27

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define FLAG_KEY 'f'
#define OPEN_KEY 32     /* 32 => Space */

#define Q_KEY 'q'


int getch(void);
int handle_arrow_keys(int input, int curser[], int width, int height);
int curser_move(int width, int height, int curser[], int *number_of_used_flags, char **game_field, char **controle_field);
char *choose_user_name(void);

#endif
