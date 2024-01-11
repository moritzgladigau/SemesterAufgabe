
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

int number_of_used_flags, width, height;
float percent_mines;

int main(void)
{       
        int move = 0;
        int curser[] = {0, 0};
        char **game_field;
        char **controle_field;
        width = 0;
        height = 0;
        percent_mines = 0;
        srand(time(NULL));

        /* Game */
        printf("Hello World!\n");
        printf("Hello here is played minesweeper:)\n");
        spiel_anleitung();
        
        /* User Input fuer die Größe des Maps und der Mine-Prozentzahl */
        levels_of_difficulty();         /* Display the menu */
        
        user_choice(width, height, percent_mines, MAX_HEIGHT, MAX_WIDTH);

        controle_field = field_init(width, height);
        place_a_mine(controle_field, percent_mines, width, height);
        place_numbers(controle_field, width, height);

        game_field = field_init(width, height);
        fill_field(game_field, width, height);

        number_of_used_flags = total_number_of_mine;

        while (check_if_done(game_field, controle_field, width, height) == CONTINUE)
        {
                print_field(game_field, width, height, curser);
                move = curser_move(width, height, curser);
                /* printf("%i", move); */
                if (move == FLAG_KEY){
                        printf("NoF: %i\n", number_of_used_flags);
                        if (game_field[curser[1]][curser[0]] != FLAG_KEY && game_field[curser[1]][curser[0]] != ' ' && number_of_used_flags > 0) {
                                game_field[curser[1]][curser[0]] = FLAG_KEY;
                                number_of_used_flags--;
                        } else if (game_field[curser[1]][curser[0]] == FLAG_KEY) {
                                game_field[curser[1]][curser[0]] = '-';
                                number_of_used_flags++;
                        }
                }
                if (game_field[curser[1]][curser[0]] != FLAG_KEY && move == OPEN_KEY){
                        game_field[curser[1]][curser[0]] = (controle_field[curser[1]][curser[0]] == '0') ? ' ' : controle_field[curser[1]][curser[0]];
                        print_field(game_field, width, height, curser);
                        open_surrounding(game_field, controle_field, width, height, curser);
                }
                if (move == 'q'){
                        break;
                }
        }
        print_field(controle_field, width, height, curser);

        return 0;
}





