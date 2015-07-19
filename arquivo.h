#ifndef ARQUIVO_H
#define ARQUIVO_H 

#include <stdbool.h>

bool fimArquivo(FILE* arq);
FILE* abrirArquivo(char nomeArquivo[], char modo[]);
bool arqExiste(char nomeArquivo[]);

#endif