#include "userinput.h"
#include "the-game.h"

int getch(void) {
    int ch;

    ch = getchar();
    fflush(stdin);

    return ch;
}


int handle_arrow_keys(int input, int curser[], int width, int height) {
    switch (input) {
        case UP:
            curser[1]--;
            break;
        case DOWN:
            curser[1]++;
            break;
        case LEFT:
            curser[0]--;
            break;
        case RIGHT:
            curser[0]++;
            break;
        default:
            return 0;   /* Not an arrow key */
    }

    if (curser[1] >= height) {
        curser[1] = 0;
    }
    if (curser[1] < 0) {
        curser[1] = height - 1;
    }
    if (curser[0] >= width) {
        curser[0] = 0;
    }
    if (curser[0] < 0) {
        curser[0] = width - 1;
    }

    return 1;    /*  Arrow key handled */
}

int curser_move(int width, int height, int curser[], int *number_of_used_flags, char **game_field, char **controle_field) {
    char input;
    int result;

    while (1) {
        result = 0;

        input = getch();

        if (input == UP || input == LEFT || input == DOWN || input == RIGHT) {

            result = handle_arrow_keys(input, curser, width, height);

            if (result) {
                return 0;
                /* Arrow key handled */
            } 
        }
        if (input == FLAG_KEY) {
            
            printf("NoF: %i\n", *number_of_used_flags);
            if (game_field[curser[1]][curser[0]] != FLAG_KEY && game_field[curser[1]][curser[0]] == '-' && *number_of_used_flags > 0) {
                    game_field[curser[1]][curser[0]] = FLAG_KEY;
                    (*number_of_used_flags)--;
                    printf("numOf Flag in: %i\n", *number_of_used_flags);
            } else if (game_field[curser[1]][curser[0]] == FLAG_KEY) {
                    game_field[curser[1]][curser[0]] = '-';
                    (*number_of_used_flags)++;
            }
            
            return FLAG_KEY;
        }

        if (input == OPEN_KEY && game_field[curser[1]][curser[0]] != FLAG_KEY) {

            game_field[curser[1]][curser[0]] = (controle_field[curser[1]][curser[0]] == '0') ? ' ' : controle_field[curser[1]][curser[0]];

            print_field(game_field, width, height, curser);
            open_surrounding(game_field, controle_field, width, height, curser);

            return OPEN_KEY;
        }


        if (input == PROGRAM_FINISH) {
            printf("\nProgram terminated.\n");
            return PROGRAM_FINISH;
        }
    }
}

