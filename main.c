#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#define MINE 'M'
#define BLANK ' '
#define FILED_SIZE 10

double percent_mines = 10;

char **field_init(int width, int height);
int fill_field(char **field, int width, int height);
char random_state(double mine_percent);
void print_field(char **field, int width, int height);
int mines_nearby(char **field, int width, int height, int x, int y);

int main(void)
{
        char **field;
        int width = FILED_SIZE, height = FILED_SIZE, user_x = 3, user_y = 4;
        srand(time(NULL));
        field = field_init(width, height);
        fill_field(field, width, height);
        print_field(field, width, height);
        return 0;
}

char **field_init(int width, int height)
{
        char **field = malloc(sizeof(char*) * height);
        int i;
        if (field == NULL)
        {
                printf("Fehler bei Initialisierung");
                free(field);
                return NULL;
        }
        
        for (i = 0; i < height; i++)
        {
                field[i] = malloc(sizeof(char)*width);
        }

        return field;
}

int fill_field(char **field, int width, int height)
{
        int i, j;
        for (i = 0; i < height; i++)
        {
                for (j = 0; j < width; j++)
                {
                        field[i][j] = random_state(percent_mines);
                }
                
        }
        for (i = 0; i < height; i++)
        {
                for (j = 0; j < width; j++)
                {
                        if (field[i][j] != MINE)
                        {
                                field[i][j] = (mines_nearby(field, width, height, i, j) + '0');
                        }
                        
                }
                
        }
        for (i = 0; i < height; i++)
        {
                for (j = 0; j < width; j++)
                {
                        if (field[i][j] == '0')
                        {
                                field[i][j] = ' ';
                        }
                        
                }
                
        }
        return 1;
}

char random_state(double mine_percent)
{
        int state = rand() % 101;
        int alive = mine_percent;
        if (alive >= state)
        {
                return MINE;
        }
        return BLANK;
}

void print_field(char **field, int width, int height)
{
        int i, j;
        for (i = 0; i < height; i++)
        {
                printf("|");
                for (j = 0; j < width; j++)
                {
                        printf(" %c |", field[i][j]);
                }
                printf("\n");
                for  (j = 0; j < width *4; j++)
                {
                        printf("-");
                }
                printf("\n");
                
        }
}

int mines_nearby(char **field, int width, int height, int x, int y)
{
    int mine_count = 0;
    int i, neighbours_x = 0, neighbours_y = 0;
    int neighbours[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for (i = 0; i < 8; i++)
    {
        neighbours_x = x + neighbours[i][0];
        neighbours_y = y + neighbours[i][1];
        if (neighbours_x >= 0 && neighbours_x < height && neighbours_y >= 0 && neighbours_y < width && field[neighbours_x][neighbours_y] == MINE)
        {
            mine_count++;
        }
    }
    return mine_count;
}

/*To-Do: 1. Feld initalisieren und Speicherplatz sichern.
         2. Feld zufällig mit Minen befüllen 
         3. Aufgedecktes Feld mit seinen Nachbarn vergleichen und die Anzahl in das Feld schreiben
         game-of-life.c!!!*/