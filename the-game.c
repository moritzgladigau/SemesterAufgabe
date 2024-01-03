#include "the-game.h"

int total_number_of_mine = 0;

/* Initicialies of the storage space for the Game and Controle field */
char **field_init(int width, int height)
{
        int i, k;
        char **field = calloc(width, sizeof(int*));
        if(field == NULL){
                printf("Error: Memory allocation failed!\n");
                free(field);
                return NULL;
        }

        for (i = 0; i < width; i++) {
                field[i] = calloc(height, sizeof(int));
                if (field[i] == NULL) {
                        printf("ERROR: Memory allocation error.\n");
                        for (k = 0; k < i; k++) {
                                free(field[k]);
                        }
                        free(field);
                        return NULL;
                }
        }
        return field;
}

int place_a_mine(char **field, int perpercent_mines, int width, int height)
{
    int x, y;
    int number_of_fields = width * height;
    int count_number_of_mine;
    total_number_of_mine = floor(number_of_fields * perpercent_mines / 100) + 1;
    count_number_of_mine = total_number_of_mine;
    printf("Number of field: %i\n", number_of_fields);
    printf("Number of mine: %i\n", total_number_of_mine);
    while (count_number_of_mine > 0)
    {
        x = (rand() % width + 1) - 1;
        y = (rand() % height + 1) - 1;
        if (field[x][y] != MINE){
            field[x][y] = MINE;
            count_number_of_mine--;
        }
    }
    return EXIT_SUCCESS;
}

int mines_nearby(char **field, int width, int height, int x, int y)
{
        int j, nx, ny;
        int count = 0;
        int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1}; 

        for (j = 0; j < 8; j++){
                /* Set field to check x & y */
                nx = x + dx[j];
                ny = y + dy[j];
                /* Check boundaries */
                if (nx >= 0 && ny >= 0 && nx < width && ny < height) {
                        if (field[nx][ny] == MINE) {
                                count++;
                        }
                }
        }

        return count;
}

int place_numbers(char **field, int width, int height)
{
    int i, j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            if (field[i][j] != MINE) {
                field[i][j] = mines_nearby(field, width, height, i, j) + '0';
            }
        }
    }
    return EXIT_SUCCESS;
}

int fill_field(char **field, int width, int height) {
        int i, j;
        for (i = 0; i < height; i++) {
                for (j = 0; j < width; j++) {
                        field[i][j] = '-';
                }
        }
        return EXIT_SUCCESS;
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
                                
                                /* printf(" %c ", (i >= 0 && i < height && j >= 0 && j < width) ? field[i][j] : ' '); */
                        }

                        if (j == width - 1) {
                        printf("|");  /* Print right border */
                        }
                }
                printf("\n");
        }
}

int check_if_done(char **afield, char **cfield, int width, int height)
{
        int i, j, a, c;
        int result = CONTINUE;
        int founden_mines = 0;
        for (i = 0; i < width; i++)
        {
            for (j = 0; j < height; j++) {
                a = afield[i][j];
                c = cfield[i][j];

                if (c == MINE && a == 'f') {
                    printf("WIN\n");
                    founden_mines++;
                    if (founden_mines == total_number_of_mine) {
                            return WIN;
                    }
                } else if (c == MINE && a == MINE) {
                    printf("\nLOSE\n");
                    return LOSE;
                } else {
                    result = CONTINUE;
                }
            }
        }

        printf("CONTINUE\n");
        return result;
}
