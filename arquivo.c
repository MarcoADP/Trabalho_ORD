#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "arquivo.h"
#include "util.h"
#include "indice.h"

#define DELIM "|"
#define MAX_CAMPO 50
#define MAX_REG 512
#define NUM_CAMPO_REG 4

Indice ip1;
Indice is2;
Indice ip3;


bool fimArquivo(FILE* arq){
    int offset = ftell(arq);
    if (fgetc(arq) == EOF)
        return true;

    fseek(arq, offset, SEEK_SET);
    return false;
}

FILE* abrirArquivo(char nomeArquivo[], char modo[]){
    FILE* arq;

    arq = fopen(nomeArquivo, modo);
    if (arq == NULL) {
        printf("ERRO: Arquivo não pode ser aberto.\n");
        exit(1); //TRATAR O ERRO OU FAZER EXIT??????????
    }

    printf("\nArquivo %s aberto com sucesso.\n", nomeArquivo);

    return arq;
}

void gravarArquivo(char nomeArquivo[], char conteudo[], int tamanho){
    fwrite(conteudo, tamanho, 1, nomeArquivo);
}

char* lerCampo(FILE* arq){
    char *campo = malloc(MAX_CAMPO * sizeof(char));
    fgets(campo, MAX_CAMPO, arq);
    campo[strlen(campo) - 1] = '\0';

    return campo;
}

void converterArquivo(FILE* entrada, FILE* saida, void (*lerRegIndice)(char* campo[], int byteOffset, int i)){
    char* campo[4];
    char buffer[MAX_REG + 1] = "";
    short tam_reg = 0;
    int byteOffset = 0;
    int i = 0;

    while(!fimArquivo(entrada)){
        strcpy(buffer, ""); //Zera o buffer
        tam_reg = 0;

        int j;
        for (j = 0; j < NUM_CAMPO_REG; ++j){
            campo[j] = lerCampo(entrada);
            strcat(buffer, campo[j]);
            strcat(buffer, DELIM);
        }

        tam_reg = strlen(buffer);

        gravarArquivo(saida, &tam_reg, sizeof(tam_reg));
        gravarArquivo(saida, buffer, tam_reg);
        //fwrite(&tam_reg, sizeof(tam_reg), 1, saida); //FAZER UMA FUNCAO DE INSERIR PARA USAR DEPOIS COM INSERCAO NO ARQUIVO
        //fwrite(buffer, tam_reg, 1, saida);
        printf("%d -- %s\n", tam_reg, buffer);

        lerRegIndice(campo, byteOffset, i);

        byteOffset += tam_reg + sizeof(tam_reg);
        i++;
    }

}
