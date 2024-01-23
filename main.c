
/* Hier werde ich jz sachen Testen ob DU wilst oder nicht!!! :P */

#include "the-game.h"
#include "userinput.h"
#include "design.h"
#include "log.h"
#include "sound.h"
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
char game_end[5];
int status = CONTINUE;

int main(void)
{       
        time_t start_time, end_time;
        double time_difference;

        int move = 0;
        int curser[] = {0, 0};
        char **game_field;
        char **controle_field;
        char *pname;
        width = 0;
        height = 0;
        percent_mines = 0;
        srand(time(NULL));
        
        /* Log Test */
        check_if_file_exist();

        /* Game */
        spiel_anleitung();
        strcpy(user_name, choose_user_name());
        pname = user_name;

        /* User Input fuer die Größe des Maps und der Mine-Prozentzahl */
        levels_of_difficulty();         /* Display the menu */
        menu_options();

        user_choice(&width, &height, &percent_mines, MAX_HEIGHT, MAX_WIDTH, difficulty, pname);

        /* Set Controle Field */
        controle_field = field_init(width, height);
        if(controle_field == NULL) {
                printf("Program finished!!\n");
                return 0;
        }
        place_a_mine(controle_field, percent_mines, width, height);
        place_numbers(controle_field, width, height);

        /* Set Game Field */
        game_field = field_init(width, height);
        if(game_field == NULL) {
                printf("Program finished!!\n");
                return 0;
        }
        fill_field(game_field, width, height);

        number_of_used_flags = total_number_of_mine;
        /* Start */
        time(&start_time);

        while (check_if_done(game_field, controle_field, width, height) == CONTINUE) {
                
                print_field(game_field, width, height, curser);

                move = curser_move(width, height, curser, &number_of_used_flags, game_field, controle_field);

                if (move == PROGRAM_FINISH){
                        break;
                }
                clear_screen();
        } 
        
        time(&end_time);
        time_difference = difftime(end_time, start_time);

        if (check_if_done(game_field, controle_field, width, height) == LOSE) {
                strcpy(game_end, "Lose");
                pic_lose();
        } else {
                strcpy(game_end, "Win");
                pic_win();
        }
        // wait_ticks(2000000000);
        // play_sound("end.mp3");
        print_field(controle_field, width, height, curser);
        write_log(user_name, difficulty, width, height, percent_mines, game_end, time_difference, open_field);
        free(controle_field);
        free(game_field);

 return 0;
}
