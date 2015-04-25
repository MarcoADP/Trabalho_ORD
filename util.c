#include <stdio.h>
#include "util.h"

void limpar_stdin(){
    while (getchar() != '\n');
}

void pressEnter(){
    printf("\nPressione ENTER para continuar...\n");
    getchar();
}