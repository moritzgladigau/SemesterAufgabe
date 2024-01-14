
/* Hier werde ich jz sachen Testen ob DU wilst oder nicht!!! :P */

#include "the-game.h"
#include "userinput.h"
#include "design.h"
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

int width = 0;
int height = 0;
float percent_mines = 0;
int number_of_used_flags;


/* Hier wird das Spiel erklärt. */






int main(void)
{       
        
        int move = 0;
        int curser[] = {0, 0};

        char **game_field;
        char **controle_field;

        srand(time(NULL));

        /* Game */
        printf("Hello World!\n");
        printf("Hello here is played minesweeper:)\n");
        spiel_anleitung();
        
        /* User Input fuer die Größe des Maps und der Mine-Prozentzahl */
        levels_of_difficulty();         /* Display the menu */
        
        user_choice(&width, &height, &percent_mines, MAX_HEIGHT, MAX_WIDTH);

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

        while (check_if_done(game_field, controle_field, width, height) == CONTINUE) {
                
                print_field(game_field, width, height, curser);

                move = curser_move(width, height, curser, &number_of_used_flags, game_field, controle_field);

                if (move == PROGRAM_FINISH){
                        break;
                }
        }

        print_field(controle_field, width, height, curser);

        return 0;
}



