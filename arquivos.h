#ifndef ARQUIVOS_H
#define ARQUIVOS_H 

#include "util.h"

bool fimArquivo(FILE* arq);
FILE* abrirArquivo(char nomeArquivo[], char modo[]); //nao precisa dessa funcao 
bool arqExiste(char nomeArquivo[]);

#endif