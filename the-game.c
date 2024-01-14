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

void place_numbers(char **field, int width, int height)
{
    int i, j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            if (field[i][j] != MINE) {
                field[i][j] = mines_nearby(field, width, height, i, j) + '0';
            }
        }
    }
}

void fill_field(char **field, int width, int height) {
        int i, j;
        for (i = 0; i < height; i++) {
                for (j = 0; j < width; j++) {
                        field[i][j] = '-';
                }
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



/* NOT DOON */

void open_surrounding(char **afield, char **cfield, int width, int height, int curser[])
{
        int i, j, x = curser[1], y = curser[0];
        /* Reset curser posion to check Quadrant down and to the right */
        /* Iterate over columns */
        for (j = 0; j < width; j++) {
                /* Iterate over rows */
                for (i = 0; i < height; i++) {
                        open(afield, cfield, width, height, x, y);

                        /* Increment x to move to the next row (only goes down) */
                        if (x < height - 1){
                                x++;
                        }
                                

                }
                x = curser[1];
                /* Increment y to move to the next columns (only goes right) */
                if (y < width - 1){
                        y++;
                }
        }
        /* Reset curser posion to check Quadrant above and to the right */
        x = curser[1];
        y = curser[0];

        /* Iterate over columns */
        for (j = 0; j < width; j++) {
                /* Iterate over rows */
                for (i = 0; i < height; i++) {
                        open(afield, cfield, width, height, x, y);
                        /* Decrement x to move to the next row (only goes up) */
                        if (x > 0){
                                x--;
                        }
                        
                }
                x = curser[1];
                /* Increment y to move to the next columns (only goes right) */
                if (y < width - 1){
                        y++;
                }
        }
        /* Reset curser posion to check Quadrant above and to the left */
        x = curser[1];
        y = curser[0];

        /* Iterate over columns */
        for (j = 0; j < width; j++) {
                /* Iterate over rows */
                for (i = 0; i < height; i++) {
                        open(afield, cfield, width, height, x, y);
                        /* Decrement x to move to the next row (only goes up) */
                        if (x > 0){
                                x--;
                        }
                        
                }
                x = curser[1];
                /* Increment y to move to the next columns (only goes left) */
                if (y > 0){
                        y--;
                }
        }
        /* Reset curser posion to check Quadrant down and to the left */
        x = curser[1];
        y = curser[0];

        /* Iterate over columns */
        for (j = 0; j < width; j++) {
                /* Iterate over rows */
                for (i = 0; i < height; i++) {
                        open(afield, cfield, width, height, x, y);

                        /* Increment x to move to the next row (only goes down) */
                        if (x < height - 1){
                                x++;
                        }
                                

                }
                x = curser[1];
                /* Increment y to move to the next columns (only goes left) */
                if (y > 0){
                        y--;
                }
        }
}


void open(char **afield, char **cfield, int width, int height, int x, int y)
{
        int i;
        int nx, ny;
        int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

        if (afield[x][y] == ' ') {
                for (i = 0; i < 8; i++){
                        /* Set field to check x & y */
                        nx = x + dx[i];
                        ny = y + dy[i];
                        /* Check boundaries */
                        if (nx >= 0 && ny >= 0 && nx < width && ny < height) {
                                if (afield[nx][ny] != 'f'){    
                                        if (cfield[nx][ny] == '0') {
                                                afield[nx][ny] = ' ';
                                        } else {
                                                afield[nx][ny] = cfield[nx][ny];
                                        }
                                }
                        }
                }
        }

}
