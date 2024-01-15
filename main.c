
/* Hier werde ich jz sachen Testen ob DU wilst oder nicht!!! :P */

#include "the-game.h"
#include "userinput.h"
#include "design.h"
#include "log.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ERROR 0
#define SUCCSES 1

/* !WICHTIG Mindestanzahl muss (x/y * 3 +2) */
#define MAX_WIDTH 92 
#define MAX_HEIGHT 92

int width = 8;
int height = 8;
float percent_mines = 15.6;
int number_of_used_flags;
char difficulty[13] = "Beginner";
char user_name[16] = "User";
char game_end[];

int main(void)
{       
        time_t start_time, end_time;
        double time_difference;

        int move = 0;
        int curser[] = {0, 0};

        char **game_field;
        char **controle_field;
        
        srand(time(NULL));
        
        /* Log Test */
        check_if_file_exist();
        

        /* Game */
        spiel_anleitung();
        strcpy(user_name, choose_user_name());
        /* User Input fuer die Größe des Maps und der Mine-Prozentzahl */
        levels_of_difficulty();         /* Display the menu */
        
        user_choice(&width, &height, &percent_mines, MAX_HEIGHT, MAX_WIDTH, difficulty);
        printf("UserName: %s\n", user_name);
        /* Set Controle Field */
        controle_field = field_init(width, height);
        if(controle_field == NULL) {
                printf("Program finished!!\n");
                return 0;
        }
        place_a_mine(controle_field, percent_mines, width, height);
        place_numbers(controle_field, width, height);

        game_field = field_init(width, height);
        if(game_field == NULL) {
                printf("Program finished!!\n");
                return 0;
        }
        fill_field(game_field, width, height);

        number_of_used_flags = total_number_of_mine;
        
        time(&start_time);

        while (check_if_done(game_field, controle_field, width, height) == CONTINUE) {
                clear_screen();
                print_field(game_field, width, height, curser);

                move = curser_move(width, height, curser, &number_of_used_flags, game_field, controle_field);

                if (move == PROGRAM_FINISH){
                        break;
                }
        } 
        
        time(&end_time);
        time_difference = difftime(end_time, start_time);

        if (check_if_done(game_field, controle_field, width, height) == LOSE) {
                strcpy(game_end, "Lose");
        } else {
                strcpy(game_end, "Win");
        }
        
        print_field(controle_field, width, height, curser);
        write_log(user_name, difficulty, width, height, percent_mines, game_end, time_difference);

        return 0;
}



