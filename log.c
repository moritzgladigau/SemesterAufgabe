#include "log.h"

int check_if_file_exist(void)
{
        FILE *file;

        file = fopen("game_log.txt", "r");

        if (file == NULL) {
                printf("Es wird ein Log File angelegt.\n");
                file = fopen("game_log.txt", "w");
                if (file != NULL) {
                        printf("Es wurde erfolgreich ein Log file für Sie angelegt.\n");
                        file = fopen("game_log.txt", "a");
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
        FILE *file = fopen("game_log.txt", "r");
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
                /* printf("%s\n", fgets(buffer, sizeof(buffer), file)); */
                token = strtok(buffer, " \t");
                /* printf("token: %s\n", token); */
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

        file = fopen("game_log.txt", "a");

        if (file == NULL) {
                printf("Fehler beim Öffnen der Datei");
        } else {
                fprintf(file, "\n%i\t%s\t%s\t%s\t%s\t%ix%i\t%2.2f%%\t%s\t%0.3f", get_game_id(), get_date(), get_time(), user_name, difficulty, width, height, percent_mines, spielende, time_difference);
        }

        fclose(file);

}
