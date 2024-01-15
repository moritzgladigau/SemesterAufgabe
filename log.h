#ifndef LOG_FILE
#define LOG_FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int check_if_file_exist(void);
char* get_date(void);
char* get_time(void);
char* get_from_table(int row, int col);
int get_game_id(void);
void write_log(char user_name[], char difficulty[], int width, int height, double percent_mines, char spielende[], double time_difference);

#endif
