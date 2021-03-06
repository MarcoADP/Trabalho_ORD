#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"

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

bool arqExiste(char nomeArquivo[]){
    FILE* arq = fopen(nomeArquivo, "r");
    if (arq == NULL){
        fclose(arq);
        return false;
    }

    fclose(arq);
    return true;
}