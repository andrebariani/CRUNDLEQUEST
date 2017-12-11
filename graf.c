#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXTOF "%s strikes, and it does %d damage!\n"
#define TEXTOM "%s casts a spell, and it does %d damage!\n"

void delayPrint( char TEXTO[], char nome[], int dmg ) {

    char *TXT;
    asprintf(&TXT, TEXTO, nome, dmg);

    for( int c = 0 ; c < strlen(TXT) ; c++ ) {
        system("sleep 0.05");
        printf("%c", TXT[c]);
        // printf(TEXTO, nome, dmg);
        fflush(stdout);
    }

    free(TXT);
}

int main() {
    srand( (unsigned)time(NULL) );
    int r = rand() % 50;
    char nome[7] = "Goblin";

    delayPrint(TEXTOF, nome, r);

    delayPrint(TEXTOM, nome, r);

    printf("You Win\n");

    return 0;
}
