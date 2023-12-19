/* Hier werde ich jz sachen Testen ob DU wilst oder nicht!!! :P */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define ERROR 0
#define SUCCSES 1

#define MAX_COLS 50
#define MAX_ROWS 50

/* Hier wird das Spiel erklärt. */
void spiel_anleitung();
void flush();
void levels_of_difficulty();
int create_map(int x_map_size, int y_map_size, int percent_mines);

int main()
{       
        int x_map_size = 0, y_map_size = 0;
        char game_map[MAX_COLS][MAX_ROWS];
        char comparison_map[MAX_COLS][MAX_ROWS];
        float percent_mines = 0;
        int choice;

        /* Game */
        printf("Hello World!\n");
        printf("Hallo hier wird Minesweeper gespielt :)\n");
        spiel_anleitung();
        
        /* User Input fuer die Größe des Maps und der Mine-Prozentzahl */
        levels_of_difficulty();         /* Display the menu */
        
        do{
                /* Get user Choice */
                printf("Enter your choice (1-5): ");
                scanf("%d", &choice);
                switch (choice) {
                        case 1:
                                printf("You play: Beginner\n");
                                x_map_size=8;
                                y_map_size=8;
                                percent_mines=15.6;
                                printf("\tMap size will be set to 8x8.\n");
                                printf("\tThe mine percentage is fixed at 15,6%%.\n");
                                break;
                        case 2:
                                printf("You play: Intermediate\n");
                                x_map_size=16;
                                y_map_size=16;
                                percent_mines=15.6;
                                printf("\tMap size will be set to 16x16.\n");
                                printf("\tThe mine percentage is fixed at 15.6%%.\n");
                                break;
                        case 3:
                                printf("You play: Expert\n");
                                x_map_size=30;
                                y_map_size=16;
                                percent_mines=20.6;
                                printf("\tMap size will be set to 16x16.\n");
                                printf("\tThe mine percentage is fixed at 20.6%%.\n");
                                break;
                        case 4:
                                printf("You play: User -defined\n");
                                do{
                                        printf("Gebe die Anzahl der Reihen (max. %i) an: ", MAX_COLS);
                                        scanf("%i", &x_map_size);
                                        flush();
                                } while (x_map_size > MAX_COLS);
                                do{
                                        printf("Gebe die Anzahl der Spalten (max. %i) an: ", MAX_ROWS);
                                        scanf("%i", &y_map_size);
                                        flush();
                                } while (y_map_size > MAX_ROWS);
                                do{
                                        printf("Gebe die Minendichte (min. 1%%, max. 99%%) an: ");
                                        scanf("%f", &percent_mines);
                                        flush();
                                } while (percent_mines < 1 || percent_mines > 99);
                                printf("\tMap size will be set to %ix%i.\n", x_map_size, y_map_size);
                                printf("\tThe mine percentage is fixed at %.1f%%.\n", percent_mines);
                                break;
                        case 5:
                                system("clear");
                                printf("\nExiting the menu.\n");
                                printf("\tMap size will be set to %ix%i.\n", x_map_size, y_map_size);
                                printf("\tThe mine percentage is fixed at %.1f%%.\n", percent_mines);
                                break;
                        default:
                                printf("Invalid choice. Please enter a number between 1 and 4.\n");
                } 
        } while (choice != 5);
        
        return 0;
}

void spiel_anleitung()
{
        printf("\n==================================================================================\n");
        printf("|| Gebe die Adresse eines Feldes ein,\t\t\t\t\t\t||\n||\twelche sich aus einem <Groß_Buchstaben> und einer <Zahl> zusammenstezt.\t||\n");
        printf("|| Dein makiertes Feld wird dir wie folgt angezeigt: <->\t\t\t||\n|| Wobei an stelle von dem '-' auch eine Zahl zwischen '1' und '8'\t\t||\n||\toder nix ' ' stehen kann.\t\t\t\t\t\t||\n");
        printf("|| Um ein Feld mit einer Flage zu belegen gebe <f> ein\t\t\t\t||\n|| Um ein Feld aufzudeken gebe <a> ein.\t\t\t\t\t\t||\n");
        printf("||\t\t\t\t\t\t\t\t\t\t||\n||\t----> Gebe <help> ein um wieder zu diesr Anleitung zu kommen <----\t||\n");
        printf("==================================================================================\n");
        printf("\n");
}

void flush()
{
        char c;
        while ((c = getchar()) != EOF && c != '\n');
}

void levels_of_difficulty()
{
        printf("Select a degree of prison:\n");
        printf("1. Beginner\n");
        printf("2. Intermediate\n");
        printf("3. Expert\n");
        printf("4. User -defined\n");
        printf("5. Exit/ Help\n");
}
