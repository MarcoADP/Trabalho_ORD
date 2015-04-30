#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arquivos.h"

bool fimArquivo(FILE* arq){
    long offset = ftell(arq);
    if (fgetc(arq) == EOF){
        fseek(arq, offset, SEEK_SET);
        return true;
    }

    fseek(arq, offset, SEEK_SET);
    return false;
}

FILE* abrirArquivo(char nomeArquivo[], char modo[]){
    FILE* arq;

    arq = fopen(nomeArquivo, modo);
    if (arq == NULL) {
        printf("ERRO: Arquivo não pode ser aberto.\n");
        return NULL;
    }

    return arq;
}