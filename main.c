
/* Hier werde ich jz sachen Testen ob DU wilst oder nicht!!! :P */

#include "the-game.h"
#include "userinput.h"
#include "design.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ERROR 0
#define SUCCSES 1

/* !WICHTIG Mindestanzahl muss (x/y * 3 +2) */
#define MAX_WIDTH 92 
#define MAX_HEIGHT 92

int width = 0;
int height = 0;
float percent_mines = 0;
int number_of_used_flags;


/* Hier wird das Spiel erklärt. */
void spiel_anleitung(void);
void flush(void);

void levels_of_difficulty(void);


int main(void)
{       
        
        int choice, move = 0;
        int curser[] = {0, 0};

        char **game_field;
        char **controle_field;

        srand(time(NULL));

        /* Game */
        printf("Hello World!\n");
        printf("Hello here is played minesweeper:)\n");
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
                                width = 8;
                                height = 8;
                                percent_mines = 15.6;
                                printf("\tMap size will be set to 8x8.\n");
                                printf("\tThe mine percentage is fixed at 15,6%%.\n");
                                flush();
                                break;
                        case 2:
                                printf("You play: Intermediate\n");
                                width = 16;
                                height = 16;
                                percent_mines = 15.6;
                                printf("\tMap size will be set to 16x16.\n");
                                printf("\tThe mine percentage is fixed at 15.6%%.\n");
                                flush();
                                break;
                        case 3:
                                printf("You play: Expert\n");
                                width = 30;
                                height = 16;
                                percent_mines = 20.6;
                                printf("\tMap size will be set to 16x16.\n");
                                printf("\tThe mine percentage is fixed at 20.6%%.\n");
                                flush();
                                break;
                        case 4:
                                printf("You play: User -defined\n");
                                do{
                                        printf("Enter the number of rows (max. %i):", (MAX_WIDTH-2)/3);
                                        scanf("%i", &width);
                                        flush();
                                } while (width > (MAX_WIDTH-2)/3);
                                do{
                                        printf("Enter the number of columns (max. %i):", (MAX_HEIGHT-2)/3);
                                        scanf("%i", &height);
                                        flush();
                                } while (height > (MAX_HEIGHT-2)/3);
                                do{
                                        printf("Add the min density (min. 1 %%, max. 99 %%):");
                                        scanf("%f", &percent_mines);
                                        flush();
                                } while (percent_mines < 1 || percent_mines > 99);
                                printf("\tMap size will be set to %ix%i.\n", width, height);
                                printf("\tThe mine percentage is fixed at %.1f%%.\n", percent_mines);
                                break;
                        case 5:
                                system("clear");
                                printf("\nExiting the menu.\n");
                                printf("\tMap size will be set to %ix%i.\n", width, height);
                                printf("\tThe mine percentage is fixed at %.1f%%.\n", percent_mines);
                                flush();
                                break;
                        default:
                                printf("Invalid choice. Please enter a number between 1 and 4.\n");
                                flush();
                } 
        } while (choice != 5);

        /* Set Controle Field */
        controle_field = field_init(width, height);
        if(controle_field == NULL) {
                printf("Program finished!!\n");
                return 0;
        }
        place_a_mine(controle_field, percent_mines, width, height);
        place_numbers(controle_field, width, height);

        game_field = field_init(width, height);
        if(game_field == NULL) {
                printf("Program finished!!\n");
                return 0;
        }
        fill_field(game_field, width, height);

        number_of_used_flags = total_number_of_mine;

        while (check_if_done(game_field, controle_field, width, height) == CONTINUE) {
                
                print_field(game_field, width, height, curser);

                move = curser_move(width, height, curser, &number_of_used_flags, game_field, controle_field);

                if (move == PROGRAM_FINISH){
                        break;
                }
        }

        print_field(controle_field, width, height, curser);

        return 0;
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

void flush(void)
{
        char c;
        while ((c = getchar()) != EOF && c != '\n');
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
