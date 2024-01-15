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
                        fprintf(file, "Spiel\tDatum\tSpieler\tSchwierigkeit\tGrösse\tMinen Dichte\tSpielende\tZeit");
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
