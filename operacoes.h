#ifndef OPERACOES_H
#define OPERACOES_H 

#include "indice.h"

#define MAX_CAMPO 50
#define NUM_CAMPO_REG 4

#define NOME_ARQ_IND "convertidoIndividuos.txt"
#define NOME_ARQ_RACAS "convertidoRacas.txt"

extern Indice ip1;
extern Indice is2;
extern Indice ip3;
extern ListaI listaIP1;
extern ListaI listaIS2;

bool buscaID(Indice ip, char nomeArquivo[], char* campoRetorno[]);
bool importarArq();
bool inserirIndividuo();

#endif