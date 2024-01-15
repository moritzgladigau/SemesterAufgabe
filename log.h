#ifndef LOG_FILE
#define LOG_FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE_NAME "game_log.txt"
#define SPIEL 1
#define DATUM 2
#define UHRZEIT 3
#define SPIELER 4
#define SCHWIERIGKEIT 5
#define GRÖSSE 6
#define MINEN_DICHTE 7
#define SPIELENDE 8
#define ZEIT 9

int check_if_file_exist(void);
char* get_date(void);
char* get_time(void);
int get_game_id(void);
void write_log(char user_name[], char difficulty[], int width, int height, double percent_mines, char spielende[], double time_difference);
char* get_from_table(int row, int col);
void tabel(void);


#endif
