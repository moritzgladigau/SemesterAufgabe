/* Hier werde ich jz sachen Testen ob DU wilst oder nicht!!! :P */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ERROR 0
#define SUCCSES 1

/* Hier wird das Spiel erklärt. */
void spiel_anleitung();
int user_input(char w[]);
void flush();

int main()
{
        char s[] = {'\0'};
        

        /* Spiel Einfuehrung */
        printf("Hello World!\n");
        printf("Hallo hier wird Minesweeper gespielt :)\n");
        spiel_anleitung();

        user_input(s);
        
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

int user_input(char input[])
{
        /* Der User darf <help>, Feldcoordinaten z.B: <B1>, Flagen/Aufdeken z.B: <a> oder beides <B1a> */
        int result = SUCCSES;

        printf("Deine Eingabe: ");
        scanf("%s", input);

        if (strcmp(input, "help") == 0) {
                /* Gebe die Anleitung wieder aus */
                printf("Anleitung");
                spiel_anleitung();
                return ERROR;
        } else if (strlen(input) > 3 || (strlen(input) == 1 && islower(input[0]) == 0) || (strlen(input) >= 2 && isupper(input[0]) == 0)) {
                /* 
                uberpfuefe ob der wert Drei stellen oder weniger hat <B1f> 
                wenn der wert nur eine stelle hatt muss diese ein kleinbuchstabe sein <f> / <a> 
                wenn der wert Zweistellen hat oder mehr muss der erste ein Grosbuchtstabe <A> der zweite eine Zahl <1> sein
                hat der wert drei stellen muss vorheriges gelten und der dritte wert muss ein kleinbustabe sein!!
                */
                printf("ERROR: Wrong Input!!\nGebe <help> ein um mehr zu erfahren.");
                return ERROR;
        }

        flush();
        return result;
}

void flush()
{
        char c;
        while ((c = getchar()) != EOF && c != '\n');
}

