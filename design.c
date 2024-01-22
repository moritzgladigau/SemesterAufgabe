#include "design.h"
#include "userinput.h"
#include <string.h>
#include "sound.h"

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
        char border = '|';
        char upper_border = '=';
        for (i = -1; i <= height; i++) {
                for (j = 0; j < width; j++) {
                        if (j == 0) {
                                printf(BLUE);
                                printf("%c", border);
                                printf(RESET); /* Print left border */
                        }

                        if (i == -1 || i == height) {
                                printf(BLUE);
                                printf("%c%c%c", upper_border, upper_border, upper_border);
                                printf(RESET);  /* Print horizontal border */
                        } else {
                                if (i >= 0 && i < height && j >= 0 && j < width) {
                                        if (i == curser[1] && j == curser[0]) {
                                                printf(BLUE);
                                                printf("[%c]", field[i][j]);
                                                printf(RESET);
                                        } else if (field[i][j] == '1')
                                        {
                                                printf(GREEN);
                                                printf(" %c ", field[i][j]);
                                                printf(RESET);
                                        } else if (field[i][j] == '2')
                                        {
                                                printf(BLUE);
                                                printf(" %c ", field[i][j]);
                                                printf(RESET);
                                        } else if (field[i][j] == '3')
                                        {
                                                printf(RED);
                                                printf(" %c ", field[i][j]);
                                                printf(RESET);
                                        } else if (field[i][j] == '4')
                                        {
                                                printf(MAGENTA);
                                                printf(" %c ", field[i][j]);
                                                printf(RESET);
                                        }else if(field[i][j] == 'f')
                                        {
                                                printf(" F ");
                                        }
                                        else {
                                                printf(" %c ", field[i][j]);
                                        }
                                } else {
                                        printf("   ");
                                }
                        }

                        if (j == width - 1) {
                                printf(BLUE);
                                printf("%c", border);  /* Print right border */
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
        printf("\n\n");
        printf("Waehle deinen Schwierigkeitsgrad!\n");
        printf(GREEN);
        printf("1. Beginner\n");
        printf(RESET);
        printf(BLUE);
        printf("2. Intermediate\n");
        printf(RESET);
        printf(MAGENTA);
        printf("3. Expert\n");
        printf(RESET);
        printf("4. User -defined\n");
}

void menu_options(void)
{
        printf("5. Sieh dir das Log-File an!\n");
        printf(RED);
        printf("Druecke 'LEERTASTE' und danach 'ENTER' um dass Spiel zu beginnen!\n");
        printf(RESET);
}

void print_minesweeper_art(void)
{
        char *line1 = " |    | ||| |\\  | ||||   |||  |   |  ||||  ||||  |||  ||||  ||||  ";
        char *line2 = " |\\  /|  |  | \\ | |     |     |   |  |     |     |  | |     |   | ";
        char *line3 = " | \\/ |  |  |  \\| ||||   |||  | | |  |||   |||   |||  |||   ||||  ";
        char *line4 = " |    |  |  |   | |         | | | |  |     |     |    |     |  | ";
        char *line5 = " |    | ||| |   | ||||   |||   | |   ||||  ||||  |    ||||  |  || ";
        play_sound("start.mp3");
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
        char choice;

        do{
                        /* Get user Choice */
                        scanf("%c", &choice);
                        switch (choice) {
                                case '1':
                                        printf("Du spielst als Anfaenger!\n");
                                        *width = 8;
                                        *height = 8;
                                        *percent_mines = 15.6;
                                        strcpy(difficulty, "Beginner");
                                        printf("\t Kartengroesse: 8x8.\n");
                                        printf("\t Minenanteil: 15,6%%.\n");
                                        printf(RED);
                                        printf("Druecke 'LEERTASTE' und danach 'ENTER' um dass Spiel zu beginnen!\n");
                                        printf(RESET);
                                        flush();
                                        break;
                                case '2':
                                        printf("Du spielst als Fortgeschrittener!\n");
                                        *width = 16;
                                        *height = 16;
                                        *percent_mines = 15.6;
                                        strcpy(difficulty, "Intermediate");
                                        printf("\t Kartengroesse: 16x16.\n");
                                        printf("\t Minenanteil: 15.6%%.\n");
                                        printf(RED);
                                        printf("Druecke 'LEERTASTE' und danach 'ENTER' um dass Spiel zu beginnen!\n");
                                        printf(RESET);
                                        flush();
                                        break;
                                case '3':
                                        printf("Du spielst als Experte!\n");
                                        *width = 30;
                                        *height = 16;
                                        *percent_mines = 20.6;
                                        strcpy(difficulty, "Expert");
                                        printf("\t Kartengroesse: 16x16.\n");
                                        printf("\t Minenanteil: 20.6%%.\n");
                                        printf(RED);
                                        printf("Druecke 'LEERTASTE' und danach 'ENTER' um dass Spiel zu beginnen!\n");
                                        printf(RESET);
                                        flush();
                                        break;
                                case '4':
                                        printf("Du spielst Nuter-Definiert!\n");
                                        strcpy(difficulty, "User-defined");
                                        do{
                                                printf("Gib die Anzahl an Zeilen ein: (max. %i):", (MAX_WIDTH-2)/3);
                                                scanf("%i", width);
                                                flush();
                                        } while (*width > (MAX_WIDTH-2)/3);
                                        do{
                                                printf("Gib die Anzahl an Spalten ein: (max. %i):", (MAX_HEIGHT-2)/3);
                                                scanf("%i", height);
                                                flush();
                                        } while (*height > (MAX_HEIGHT-2)/3);
                                        do{
                                                printf("Gib den Minenanteil ein: (min. 1 %%, max. 99 %%):");
                                                scanf("%f", percent_mines);
                                                flush();
                                        } while (*percent_mines < 1 || *percent_mines > 99);
                                        printf("\tKartengroesse: %ix%i.\n", *width, *height);
                                        printf("\tMinenanteil:  %.1f%%.\n", *percent_mines);
                                        printf(RED);
                                        printf("Druecke 'LEERTASTE' und danach 'ENTER' um dass Spiel zu beginnen!\n");
                                        printf(RESET);
                                        break;
                                case 32:
                                        clear_screen();
                                        printf("\nMenue wird verlassen!\n");
                                        printf("\tKartengroesse: %ix%i.\n", *width, *height);
                                        printf("\tMinenanteil:  %.1f%%.\n", *percent_mines);
                                        flush();
                                        break;
                                case '5':
                                        clear_screen();
                                        tabel_menu_options();
                                        tabel_menu();
                                        levels_of_difficulty();
                                        menu_options();
                                        break;
                                
                        } 
                } while (choice != 32);
}

void tabel_menu_options(void)
{
        printf("Menue:\n");
        printf("1. DATUM\n");
        printf("2. SPIELER\n");
        printf("3. SCHWIERIGKEIT\n");
        printf("4. SPIELENDE\n");
        printf("5. Scorboard\n");
        printf("6. <--Zurueck\n");
}

void tabel_menu(void)
{
        int choice;
        int choice1;
        char input[16];
        char activ_input[3];

        do{
                printf("Gib deine Auswahl ein: ");
                scanf("%d", &choice);

                switch (choice) {
                case 1:
                        printf("Gebe Nacheinander Tag.Monat.Jahr jeweis zweistellig an:\n");
                        printf("Day: ");
                        scanf("%2s", input);
                        flush();
                        strcat(input, ".");

                        printf("Month: ");
                        scanf("%2s", activ_input);
                        flush();
                        strcat(input, activ_input);
                        strcat(input, ".");

                        printf("Year: ");
                        scanf("%2s", activ_input);
                        flush();
                        strcat(input, activ_input);
                        
                        printf(">%s\n", input);

                        tabel(DATUM, input);
                        break;
                case 2:
                        strcpy(input, choose_user_name());
                        tabel(SPIELER, input);
                        break;
                case 3:
                        levels_of_difficulty();
                        printf("Enter your choice (1-4): ");
                        scanf("%d", &choice1);
                        switch (choice1) {
                        case 1:
                                tabel(SCHWIERIGKEIT, "Beginner");
                                break;
                        case 2:
                                tabel(SCHWIERIGKEIT, "Intermediate");
                                break;
                        case 3:
                                tabel(SCHWIERIGKEIT, "Expert");
                                break;
                        case 4:
                                tabel(SCHWIERIGKEIT, "User-defined");
                                break;
                        default:
                                break;
                        }
                        break;
                case 4:
                        printf("Wonach moechtest du filtern: ");
                        printf("1. Win\n");
                        printf("2. Lose\n");
                        scanf("%d", &choice1);
                        switch (choice1)
                        {
                        case 1:
                                tabel(SPIELENDE, "Win");
                                break;
                        case 2:
                                tabel(SPIELENDE, "Lose");
                                break;
                        default:
                                break;
                        }
                        break;
                case 5:
                        printf("Scorboard\n");
                        scorboard();
                        break;
                default:
                        break;
                }
                if (choice != 6) {
                        printf("\n");
                        tabel_menu_options();

                }

        } while (choice != 6);
        clear_screen();
}

void scorboard(void)
{
        int high_rank = get_higest_rang();
        int i;
        char *i_as_char = malloc(countDigits(high_rank) * sizeof(char));

        if (i_as_char == NULL) {
                free(i_as_char);
                printf("Fehler beim Allocieren.\n");
                return;
        }

        for (i = 1; i <= high_rank; i++) {
                sprintf(i_as_char, "%d", i);
                printf(BOLD UNDERLINE "Suche nach Rang: %s\n" RESET, i_as_char);
                tabel(RANG, i_as_char);
        }
        free(i_as_char);
}

int countDigits(int num) {
        int count = 0;  
        
        if (num == 0) {
                return 1;
        }       
        
        while (num != 0) {
                num /= 10;
                count++;
        }       
        return count;
}

void pic_win(void)
{
        play_sound("win.mp3");
        printf("             .");
        printf("           /|\\                .\n");
        printf("          / | \\            ./|\\,\n");
        printf("      ,-' \\|/ `-.        <-=O=->\n");
        printf("   <'--====--`>       '\\|/`\n");
        printf("    `-. /|\\ ,-'           '\n");
        printf("      \\ | /\n");
        printf("      \\|/   \n");
        printf("       '\n");
        printf("Du hast leider verloren!\n");
        wait_ticks(2000000000);
}

void pic_lose(void)
{
        printf("        ,--.!,\n");
        printf("     __/   -*-\n");
        printf("   ,d08b.  '|`\n");
        printf("   0088MM     \n");
        printf("   `9MMP'     \n");
        printf("\nDu hast leider verloren!\n");
        play_sound("lose.mp3");
        wait_ticks(2000000000);
}
