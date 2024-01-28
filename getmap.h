#ifndef GETMAP
#define GETMAP

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "userinput.h"

int read_field_stats(char *file_name, int *width, int *height, float *percent);
void txt_to_gamefiled(char *file_name, char **field, int width, int height);

#endif

