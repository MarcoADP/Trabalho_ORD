#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indice.h"

Indice ip1;
Indice is2;
Indice ip3;

void lerRegIndiceIndividuos(char* campo[], int byteOffset, int i){
    strcpy(ip3.reg[i].chave, campo[0]);
    itoa(byteOffset, ip3.reg[i].referencia, 10);
    ip3.tam++;
}

void criaArqIndice(Indice ind, char nomeArquivo[]){
    FILE* indice;
    int i;

    indice = abrirArquivo(nomeArquivo, "w");
    for (i = 0; i < ind.tam; ++i){
        fprintf(indice, "%s %s\n", ind.reg[i].chave, ind.reg[i].referencia);
    }
    fclose(indice);
}
