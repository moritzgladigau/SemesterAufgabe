#include "log.h"

int check_if_file_exist(void)
{
        FILE *file;

        file = fopen(FILE_NAME, "r");

        if (file == NULL) {
                printf("Es wird ein Log File angelegt.\n");
                file = fopen(FILE_NAME, "w");
                if (file != NULL) {
                        printf("Es wurde erfolgreich ein Log file für Sie angelegt.\n");
                        file = fopen(FILE_NAME, "a");
                        fprintf(file, "Spiel\tDatum\tUhrzeit\tSpieler\tSchwierigkeit\tGrösse\tMinen Dichte\tSpielende\tZeit");
                        fclose(file);
                        return 1;
                } else {
                        printf("Es konte kein Log file erstelt werden.\n");
                        fclose(file);
                        return 0;
                }
        } else {
                printf("Sie haben bereits ein Log File für ihre Spieldaten.\n");
                return 1;
        }
}

char* get_date(void)
{
        time_t t;
        struct tm *info;
        static char time_string[10];

        time(&t);

        info = localtime(&t);

        sprintf(time_string, "%02d.%02d.%02d", info->tm_mday, info->tm_mon + 1, info->tm_year % 100);

        return time_string;

}

char* get_time(void)
{
        time_t t;
        struct tm *info;
        static char time_string[10];

        time(&t);

        info = localtime(&t);

        sprintf(time_string, "%02d:%02d:%02d", info->tm_hour, info->tm_min + 1, info->tm_sec % 100);

        return time_string;
}

int get_game_id(void)
{
        FILE *file = fopen(FILE_NAME, "r");
        long pos;
        char letztesZeichen;
        int result;
        char buffer[100];
        char *token;

        if (file == NULL) {
                printf("Fehler beim Öffnen der Datei.\n");
                return 0;
        }

        fseek(file, 0, SEEK_END);

        pos = ftell(file);

        do {
                pos--;
                fseek(file, pos, SEEK_SET);
                letztesZeichen = fgetc(file);
        } while (letztesZeichen != '\n' && pos > 0);

        if (fgets(buffer, sizeof(buffer), file) != NULL) {
                token = strtok(buffer, " \t");
                result = atoi(token);
        } else {
                printf("Fehler beim Lesen der Aktuellen Spiel ID!\n");
                result = -1;
        }

        
        fclose(file);
        return ++result;
}

void write_log(char user_name[], char difficulty[], int width, int height, double percent_mines, char spielende[], double time_difference)
{
        FILE *file;

        file = fopen(FILE_NAME, "a");

        if (file == NULL) {
                printf("Fehler beim Öffnen der Datei");
        } else {
                fprintf(file, "\n%i\t%s\t%s\t%s\t%s\t%ix%i\t%2.2f%%\t%s\t%0.3f", get_game_id(), get_date(), get_time(), user_name, difficulty, width, height, percent_mines, spielende, time_difference);
        }

        fclose(file);

}


char* get_from_table(int row, int col)
{
    int max_row = get_game_id() - 1;
    char buffer[100];
    char *token = NULL;
    char *result;
    int i;
    FILE *file = fopen(FILE_NAME, "r");

    if (file == NULL) {
        printf("File konnte nicht gelesen werden!\n");
        fclose(file);
        return NULL;
    }

    if (max_row < row) {
        printf("Es wurden noch keine %i Spiele gespiel.\n", row);
        fclose(file);
        return NULL;
    }

    /* Zeilen überspringen */
    for (i = 0; i < row; i++) {
        fgets(buffer, sizeof(buffer), file);
    }

    /* Lese die gewünschte Zeile */
    if(fgets(buffer, sizeof(buffer), file) != NULL) {
        /* printf("buff: %s\n", buffer); */
        
        for (i = 1; i <= col; i++) {
            if (i == 1) {
                token = strtok(buffer, "\t");
                continue;
            }
            
            token = strtok(NULL, "\t");
            if (token == NULL) {
                printf("Es gibt nicht genügend Spalten.\n");
                break;
            }
        }
    }
    fclose(file);

    if (token != NULL) {
        result = (char*)malloc(strlen(token) + 1);
        if (result != NULL) {
            strcpy(result, token);
            /* printf("result buff: %s\n", result); */
            
            return result;
        } else {
            printf("Speicher konnte nicht allokiert werden.\n");
            return NULL;
        }
    } else {
        return NULL;
    }
}

void tabel(void)
{
        char *result;
        int max_row = get_game_id() - 1;
        int *looked_rows = malloc(max_row * sizeof(int));
        int i, j = 0;

        /* Gebe deine Gesuchten Werte hier ein. */
        int search_col = SPIELENDE;
        char search_for[] = "Lose";

        if (looked_rows == NULL) {
                printf("Fehler beim Allocieren.\n");
                free(looked_rows);
        }

        for (i = 1; i <= max_row; i++) {
                result = get_from_table(i, search_col);
                if (result != NULL && strcmp(result, search_for) == 0) {
                        looked_rows[j++] = atoi(get_from_table(i, 1));
                }
        }
        j--;
        while (j >= 0)
        {
            for (i = 1; i <= ZEIT; i++) {
                result = get_from_table(looked_rows[j], i);
                printf("%s\t", result);
            }
            printf("\n");
            j--;
        }

        free(looked_rows);
}
