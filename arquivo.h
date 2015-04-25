//#ifndef ARQUIVO_H
#define ARQUIVO_H
#include "util.h"
#include <stdbool.h>


bool fimArquivo(FILE* arq);

FILE* abrirArquivo(char nomeArquivo[], char modo[]);

void gravarArquivo(char nomeArquivo[], char conteudo[], int tamanho);

char* lerCampo(FILE* arq);

void converterArquivo(FILE* entrada, FILE* saida, void (*lerRegIndice)(char* campo[], int byteOffset, int i));

void importarArq();
