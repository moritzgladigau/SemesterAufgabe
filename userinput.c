#include "userinput.h"
#include "the-game.h"

int getch(void) {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}


int handle_arrow_keys(int input, int curser[], int width, int height) {
    switch (input) {
        case UP_ARROW:
            curser[1]--;
            break;
        case DOWN_ARROW:
            curser[1]++;
            break;
        case LEFT_ARROW:
            curser[0]++;
            break;
        case RIGHT_ARROW:
            curser[0]--;
            break;
        default:
            return 0;  // Not an arrow key
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

    return 1;  // Arrow key handled
}

int curser_move(int width, int height, int curser[]) {
    char input;
    int result;

    while (1) {
        result = 0;
        fflush(stdout);

        input = getch();

        if (input == ESCAPE_KEY) {
            input = getch();  /* Capture '[' */
            input = getch();  /* Capture the actual arrow key */

            result = handle_arrow_keys(input, curser, width, height);

            if (result) {
                return 0;
                // Arrow key handled
            } 
        }
        if (input == F_KEY) {
                return F_KEY;
        }
        if (input == A_KEY) {
                return A_KEY;
        }

        if (input == 'q') {
                return 'q';
                break;  /* Exit the loop if 'q' is pressed */
        }
    }

    printf("\nProgram terminated.\n");

    return result;
}

