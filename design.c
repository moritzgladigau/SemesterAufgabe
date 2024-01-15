#include "design.h"
#include "userinput.h"
#include "string.h"

int lineWidth = 180;

void clear_screen(void)
{
        #ifdef _WIN32
                system("cls"); 
        #else
                system("clear");
        #endif
}

void printCenteredText(const char *text) {
        int textLength = strlen(text);
        int padding = (lineWidth - textLength) / 2;
        int i;
        for (i = 0; i < padding; i++) {
                printf(" ");
        }

        printf("%s\n", text);
}

void print_field(char **field, int width, int height, int curser[])
{
        int i, j;
        for (i = -1; i <= height; i++) {
                for (j = 0; j < width; j++) {
                        if (j == 0) {
                                printf(GREEN "|");  /* Print left border */
                        }

                        if (i == -1 || i == height) {
                                printf("===");  /* Print horizontal border */
                        } else {
                                if (i >= 0 && i < height && j >= 0 && j < width) {
                                        if (i == curser[1] && j == curser[0]) {
                                                printf("[%c]", field[i][j]);
                                        } else {
                                                printf(" %c ", field[i][j]);
                                        }
                                } else {
                                        printf("   ");
                                }
                        }

                        if (j == width - 1) {
                                printf("|");  /* Print right border */
                        }
                }
                printf("\n" RESET);
        }
}

void spiel_anleitung(void)
{
        char *text1 = "Hallo hier wird Minesweeper gespielt!";
        char *text2 = "Du kannst den Cursor mit 'WASD' bewegen, beachte jedoch! du musst deine Eingabe immer mit 'ENTER' bestaetigen!";
        char *text3 = "Mit 'f' kannst du eine Flagge auf einem Feld platzieren, dieses wird dann nicht mehr aufgedeckt!";
        char *text4 = "Ein Feld aufdecken kannst du mit Leertaste!";
        char *text5 = "Druecke ENTER um das Spiel zu starten!";
        char *button1 = "----------------";
        char *button2 = "|      Start!    |";
        char *button3 = "----------------";
        printf("Bitte gib die Breite deines Terminal ein! (Standard = 180): ");
        scanf("%d", &lineWidth);
        flush();
        print_minesweeper_art();
        printCenteredText(text1);
        printCenteredText(text2);
        printCenteredText(text3);
        printCenteredText(text4);
        printf("\n\n");
        printf(RED);
        printCenteredText(text5);
        printCenteredText(button1);
        printCenteredText(button2);
        printCenteredText(button3);
        printf(RESET);
        while (1)
        {
                if (getch() == '\n')
                {
                        break;
                }
                
        }
        
}

void levels_of_difficulty(void)
{
        printf("Select a degree of prison:\n");
        printf("1. Beginner\n");
        printf("2. Intermediate\n");
        printf("3. Expert\n");
        printf("4. User -defined\n");
        printf("5. Exit/ Help\n");
}

void print_minesweeper_art(void)
{
        char *line1 = " |    | ||| |\\  | ||||   |||  |   |  ||||  ||||  |||  ||||  ||||  ";
        char *line2 = " |\\  /|  |  | \\ | |     |     |   |  |     |     |  | |     |   | ";
        char *line3 = " | \\/ |  |  |  \\| ||||   |||  | | |  |||   |||   |||  |||   ||||  ";
        char *line4 = " |    |  |  |   | |         | | | |  |     |     |    |     |  | ";
        char *line5 = " |    | ||| |   | ||||   |||   | |   ||||  ||||  |    ||||  |  || ";
        printf(RED);
        printCenteredText(line1);
        printCenteredText(line2);
        printCenteredText(line3);
        printCenteredText(line4);
        printCenteredText(line5);
        printf("\n\n\n");
        printf(RESET);
}


void user_choice(int *width, int *height, float *percent_mines, int MAX_HEIGHT, int MAX_WIDTH, char *difficulty)
{
        int choice;

        do{
                        /* Get user Choice */
                        printf("Enter your choice (1-5): ");
                        scanf("%d", &choice);
                        switch (choice) {
                                case 1:
                                        printf("You play: Beginner\n");
                                        *width = 8;
                                        *height = 8;
                                        *percent_mines = 15.6;
                                        strcpy(difficulty, "Beginner");
                                        printf("\tMap size will be set to 8x8.\n");
                                        printf("\tThe mine percentage is fixed at 15,6%%.\n");
                                        flush();
                                        break;
                                case 2:
                                        printf("You play: Intermediate\n");
                                        *width = 16;
                                        *height = 16;
                                        *percent_mines = 15.6;
                                        strcpy(difficulty, "Intermediate");
                                        printf("\tMap size will be set to 16x16.\n");
                                        printf("\tThe mine percentage is fixed at 15.6%%.\n");
                                        flush();
                                        break;
                                case 3:
                                        printf("You play: Expert\n");
                                        *width = 30;
                                        *height = 16;
                                        *percent_mines = 20.6;
                                        strcpy(difficulty, "Expert");
                                        printf("\tMap size will be set to 16x16.\n");
                                        printf("\tThe mine percentage is fixed at 20.6%%.\n");
                                        flush();
                                        break;
                                case 4:
                                        printf("You play: User -defined\n");
                                        strcpy(difficulty, "User-defined");
                                        do{
                                                printf("Enter the number of rows (max. %i):", (MAX_WIDTH-2)/3);
                                                scanf("%i", width);
                                                flush();
                                        } while (*width > (MAX_WIDTH-2)/3);
                                        do{
                                                printf("Enter the number of columns (max. %i):", (MAX_HEIGHT-2)/3);
                                                scanf("%i", height);
                                                flush();
                                        } while (*height > (MAX_HEIGHT-2)/3);
                                        do{
                                                printf("Add the min density (min. 1 %%, max. 99 %%):");
                                                scanf("%f", percent_mines);
                                                flush();
                                        } while (*percent_mines < 1 || *percent_mines > 99);
                                        printf("\tMap size will be set to %ix%i.\n", *width, *height);
                                        printf("\tThe mine percentage is fixed at %.1f%%.\n", *percent_mines);
                                        break;
                                case 5:
                                        system("clear");
                                        printf("\nExiting the menu.\n");
                                        printf("\tMap size will be set to %ix%i.\n", *width, *height);
                                        printf("\tThe mine percentage is fixed at %.1f%%.\n", *percent_mines);
                                        flush();
                                        break;
                                default:
                                        printf("Invalid choice. Please enter a number between 1 and 4.\n");
                                        flush();
                        } 
                } while (choice != 5);
}
