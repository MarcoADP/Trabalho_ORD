#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
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
    if (scanf("%d", &x) != 1){
        limpar_stdin();
        return -1;
    }
    limpar_stdin();

    return x;
}

void obterTempoAtual(char retorno[]){
    time_t tempo_atual = time(NULL);
    struct tm *ptm = gmtime(&tempo_atual);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y-%H:%M:%S", ptm);
    strcpy(retorno, buffer);
}