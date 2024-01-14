#include "design.h"

void clear_screen(void)
{
        #ifdef _WIN32
                system("cls"); 
        #else
                system("clear");
        #endif
}

void print_field(char **field, int width, int height, int curser[])
{
        int i, j;
        for (i = -1; i <= height; i++) {
                for (j = 0; j < width; j++) {
                        if (j == 0) {
                                printf("|");  /* Print left border */
                        }

                        if (i == -1 || i == height) {
                                printf("===");  /* Print horizontal border */
                        } else {
                                if (i >= 0 && i < height && j >= 0 && j < width) {
                                        if (i == curser[1] && j == curser[0]) {
                                                printf("[%c]", field[i][j]);
                                        } else {
                                                printf(" %c ", field[i][j]);
                                        }
                                } else {
                                        printf("   ");
                                }
                        }

                        if (j == width - 1) {
                                printf("|");  /* Print right border */
                        }
                }
                printf("\n");
        }
}
