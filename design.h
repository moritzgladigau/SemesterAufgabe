#ifndef DESGIN
#define DESGIN

void getTerminalSize(int *rows, int *cols);
void setTerminalSize(int rows, int cols);
void user_choice(int width, int height, float percent_mines, int MAX_HEIGHT, int MAX_WIDTH);
void levels_of_difficulty(void);
void spiel_anleitung(void);
void print_field(char **field, int width, int height, int curser[]);
void clear_screen();





#endif