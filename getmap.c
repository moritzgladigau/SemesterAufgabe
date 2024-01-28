#include "getmap.h"

int read_field_stats(char *file_name, int *width, int *height, float *percent)
{
	int i, j, token;
	int count = 0;
	char *buffer;
	FILE *file;
	*width = 0;
	*height =0;

	file = fopen(file_name, "r");

	if (file == NULL) {
		printf("Fehler beim oefnen der Datei\n");
		fclose(file);
		return 0;
	}

	while (fgetc(file) != '\n') {
		(*width)++;
	}

	fseek(file, 0, SEEK_SET);

	buffer = malloc((*width + 1) * sizeof(char));
	while (fgets(buffer, *width + 1, file) != NULL) {
		if (buffer[0] == '\n') {
			continue;
		}
		(*height)++;
	}
	free(buffer);

	fseek(file, 0, SEEK_SET);

		for (i = 0; i <= *height; i++) {
		for (j = 0; j < *width; j++) {
			token = getc(file);
			if (isdigit(token) || token == 'M' || token == '\n') {
				if (token == 'M') {
					count++;
				}
				continue;
			} else {
				printf("Unbekantes Zeichen gefunden in zeile: %i,%i", *height, *width);
				fclose(file);
				return 0;
			}
		}
	}
	fclose(file);

	*percent = (100.0/(*width * *height) * count);

	return 1;
}


void txt_to_gamefiled(char *file_name, char **field, int width, int height)
{
	int i, j;
	char token;

	FILE *file = fopen(file_name, "r");

	if (file == NULL) {
		printf("Fehler beim oefnen der Datei\n");
		fclose(file);
		return;
	}
	for (i = 0; i < height; i++) {
		for (j = 0; j <= width; j++) {
			token = getc(file);
			if (token != '\n') {
				field[i][j] = token;
			}
		}
	}
	fclose(file);
}



