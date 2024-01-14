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

int curser_move(int width, int height, int curser[]) {
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
                return FLAG_KEY;
        }
        if (input == OPEN_KEY) {
                return OPEN_KEY;
        }

        if (input == 'q') {
                return 'q';
                break;  /* Exit the loop if 'q' is pressed */
        }
    }

    printf("\nProgram terminated.\n");

    return result;
}

