/* Hier werde ich jz sachen Testen ob DU wilst oder nicht!!! :P */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define ERROR 0
#define SUCCSES 1

/* Hier wird das Spiel erklärt. */
void spiel_anleitung();
void flush();

int main()
{
        char s[] = {'\0'};
        int result;
        

        /* Spiel Einfuehrung */
        printf("Hello World!\n");
        printf("Hallo hier wird Minesweeper gespielt :)\n");
        spiel_anleitung();

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


