#include "design.h"

void clear_screen(void)
{
        #ifdef _WIN32
                system("cls"); 
        #else
                system("clear");
        #endif
}

void print_field(char **field, int width, int height, int curser[])
{
        int i, j;
        for (i = -1; i <= height; i++) {
                for (j = 0; j < width; j++) {
                        if (j == 0) {
                                printf("|");  /* Print left border */
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
                printf("\n");
        }
}

void spiel_anleitung(void)
{
        printf("\n==================================================================================\n");
        printf("|| Gebe die Adresse eines Feldes ein,\t\t\t\t\t\t||\n||\twelche sich aus einem <Groß_Buchstaben> und einer <Zahl> zusammenstezt.\t||\n");
        printf("|| Dein makiertes Feld wird dir wie folgt angezeigt: <->\t\t\t||\n|| Wobei an stelle von dem '-' auch eine Zahl zwischen '1' und '8'\t\t||\n||\toder nix ' ' stehen kann.\t\t\t\t\t\t||\n");
        printf("|| Um ein Feld mit einer Flage zu belegen gebe <f> ein\t\t\t\t||\n|| Um ein Feld aufzudeken gebe <a> ein.\t\t\t\t\t\t||\n");
        printf("||\t\t\t\t\t\t\t\t\t\t||\n||\t----> Gebe <help> ein um wieder zu diesr Anleitung zu kommen <----\t||\n");
        printf("==================================================================================\n");
        printf("\n");
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


void user_choice(int *width, int *height, float *percent_mines, int MAX_HEIGHT, int MAX_WIDTH)
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
                                        printf("\tMap size will be set to 8x8.\n");
                                        printf("\tThe mine percentage is fixed at 15,6%%.\n");
                                        flush();
                                        break;
                                case 2:
                                        printf("You play: Intermediate\n");
                                        *width = 16;
                                        *height = 16;
                                        *percent_mines = 15.6;
                                        printf("\tMap size will be set to 16x16.\n");
                                        printf("\tThe mine percentage is fixed at 15.6%%.\n");
                                        flush();
                                        break;
                                case 3:
                                        printf("You play: Expert\n");
                                        *width = 30;
                                        *height = 16;
                                        *percent_mines = 20.6;
                                        printf("\tMap size will be set to 16x16.\n");
                                        printf("\tThe mine percentage is fixed at 20.6%%.\n");
                                        flush();
                                        break;
                                case 4:
                                        printf("You play: User -defined\n");
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
