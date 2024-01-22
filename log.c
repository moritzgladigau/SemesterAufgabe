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
                        fprintf(file, "Spiel\tDatum\tUhrzeit\tSpieler\tSchwierigkeit\tGrösse\tMinen Dichte\tSpielende\tZeit\tScore\tRang\t~");
                        fclose(file);
                        return 1;
                } else {
                        printf("Es konte kein Log file erstelt werden.\n");
                        fclose(file);
                        return 0;
                }
        } else {
                printf("Sie haben bereits ein Log File fuer ihre Spieldaten.\n");
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
                printf("Fehler beim Oeffnen der Datei.\n");
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

void write_log(char user_name[], char difficulty[], int width, int height, double percent_mines, char spielende[], double time_difference, int open_field)
{
        FILE *file;
        int score = set_score(width * height, percent_mines, time_difference, open_field);

        file = fopen(FILE_NAME, "a");

        if (file == NULL) {
                printf("Fehler beim Oeffnen der Datei");
        } else {
                fprintf(file, "\n%i\t%s\t%s\t%s\t%s\t%ix%i\t%2.2f%%\t%s\t%0.3f\t%i\t%i\t~", get_game_id(), get_date(), get_time(), user_name, difficulty, width, height, percent_mines, spielende, time_difference, score, get_rang(score));
        }

        fclose(file);
        if (get_game_id() - 1 != 1){
                update_rang();
        }

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

void tabel(int search_col, char search_for[])
{
        char *result;
        int max_row = get_game_id() - 1;
        int *looked_rows = malloc(max_row * sizeof(int));
        int i, j = 0;

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

        if(j == -1) {
                printf(RED "Es gibt keine Treffer!\n\n" RESET);
                free(looked_rows);
                return;
        }

        printf(GREEN "Spiel\tDatum\t\tUhrzeit\t\tSpieler\tSchwierigkeit\tGrösse\tMinen\tSpiel-\tZeit\tScore\tRang\n\t\t\t\t\t\t\t\t\tDichte\tende\n" RESET);
        
        while (j >= 0)
        {
            for (i = 1; i <= RANG; i++) {
                result = get_from_table(looked_rows[j], i);
                printf("%s\t", result);
            }
            printf("\n");
            j--;
        }

        free(looked_rows);
}

int get_rang(int score)
{
        int rang = INT_MAX;
        int max_row = get_game_id();
        int i;

        if (max_row == 1) {
                return rang = get_higest_rang();
        }

        for (i = 1; i < max_row; i++) {
                
            if (rang <= atoi(get_from_table(i, RANG))) {
                        continue;
            } else if (score <= atoi(get_from_table(i, SCORE))) {
                        rang = atoi(get_from_table(i, RANG));
            }
                
        }
    return rang = (rang == INT_MAX) ? get_higest_rang() : rang;
}

int set_score(int num_of_field, double percent_mines, double time, int open_field)
{
        int result;
        result = (num_of_field * (int) percent_mines) / ((int) time + 1) * open_field;
        return result;
}

int update_rang(void)
{
        int rang_update, i;
        int max_row = get_game_id();
        int save = atoi(get_from_table(max_row - 1, RANG));
        char *game_id, *date, *time, *user_name, *difficulty, *groese, *percent_mines, *spielende, *score, *time_difference;

        FILE *file = fopen(FILE_NAME, "r");
        FILE *temp = fopen("temp.txt", "w");

        if (file == NULL || temp == NULL) {
                perror("Fehler beim Öffnen der Datei");
                return 1;
        }

        fprintf(temp, "Spiel\tDatum\tUhrzeit\tSpieler\tSchwierigkeit\tGrösse\tMinen Dichte\tSpielende\tZeit\tScore\tRang\t~");

        for (i = 1; i < max_row - 1; i++) {
                if (atoi(get_from_table(max_row - 1, SCORE)) == atoi(get_from_table(i, SCORE))) {
                        return 0;
                }
        }

        for (i = 1; i < max_row; i++) {
                rang_update = atoi(get_from_table(i, RANG));

                game_id = get_from_table(i, SPIEL);
                date = get_from_table(i, DATUM);
                time = get_from_table(i, UHRZEIT);
                user_name = get_from_table(i, SPIELER);
                difficulty = get_from_table(i, SCHWIERIGKEIT);
                groese = get_from_table(i, GRoeSSE);
                percent_mines = get_from_table(i, MINEN_DICHTE);
                spielende = get_from_table(i, SPIELENDE);
                score = get_from_table(i, SCORE);
                time_difference = get_from_table(i, ZEIT);

                if (rang_update >= save) {
                        if (rang_update == save && atoi(get_from_table(max_row - 1, SCORE)) == atoi(get_from_table(i, SCORE))) {
                                fprintf(temp, "\n%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%i\t~", game_id, date, time, user_name, difficulty, groese, percent_mines, spielende, time_difference, score, rang_update);
                                continue;
                        } else {
                                rang_update++;
                        }
                }
                fprintf(temp, "\n%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%i\t~", game_id, date, time, user_name, difficulty, groese, percent_mines, spielende, time_difference, score, rang_update);
        }


        fclose(temp);
        fclose(file);

        if (remove(FILE_NAME) != 0 || rename("temp.txt", FILE_NAME) != 0) {
                printf("Fehler beim Umbenennen der Datei");
                return 1;
        }
        return 0;

}

int get_higest_rang(void)
{
        int i, result = 1;
        int max = get_game_id();
        for (i = 1; i < max; i++) {
                if (result < atoi(get_from_table(i, RANG))) {
                        result = atoi(get_from_table(i, RANG));
                }
        }
        return result;
}
