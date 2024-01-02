#include "the-game.h"


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
