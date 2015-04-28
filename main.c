#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "indice.h"
#include "arquivo.h"
#include "inserir.h"

/*#define DELIM "|"
#define MAX_CAMPO 50
#define MAX_REG 512
#define NUM_CAMPO_REG 4

#define RACAS 0
#define INDIVIDUOS 1*/

Indice ip1;
Indice is2;
Indice ip3;

/*Testando!!! ok?*/



void menu(){
    int op = 0;

    printf("(1) - Importar arquivo\n");
    printf("(2) - Inserir individuo\n");
    printf("(3) - Buscar\n");
    printf("(4) - Sair\n");
    printf("\nDigite sua opcao: ");
    scanf("%d", &op);
    limpar_stdin();

    switch(op){
        case 1:
            importarArq();
        break;
        case 2:
            inserirIndividuo();
        break;
        case 3:
            busca();
        break;
    }
}

int main(int argc, char const *argv[]){
    menu();

    pressEnter();
    return 0;
}
