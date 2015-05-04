#include <stdio.h>
#include <ctype.h>
#include "util.h"


void limpar_stdin(){
    while (getchar() != '\n');
}

void pressEnter(){
    printf("\nPressione ENTER para continuar...\n");
    getchar();
}

void clrscr(){
    int i;
    for (i = 0; i < 30; ++i)
        printf("\n\n");
}

int lerInt(char msg[]){
    int x;
    printf("%s", msg);
    scanf("%d", &x);
    limpar_stdin();

    return x;
}
