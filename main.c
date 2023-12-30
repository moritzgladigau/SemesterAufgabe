#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>


double percent_mines = 9.5;

char **field_init(int width, int height);
int fill_field(char **field, int width, int height);
char random_state(double mine_percent);
void print_field(char **field, int width, int height);

int main(void)
{
        char **field;
        int width = 5, height = 5;
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
        return 1;
}

char random_state(double mine_percent)
{
        int state = rand() % 101;
        int alive = mine_percent;
        if (alive >= state)
        {
                return 'M';
        }else {
                return '0';
        }

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

/*To-Do: 1. Feld initalisieren und Speicherplatz sichern.
         2. Feld zufällig mit Minen befüllen 
         3. Aufgedecktes Feld mit seinen Nachbarn vergleichen und die Anzahl in das Feld schreiben
         game-of-life.c!!!*/