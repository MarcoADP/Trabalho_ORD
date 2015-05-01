#ifndef OPERACOES_H
#define OPERACOES_H 

#include "indice.h"

#define MAX_CAMPO 50
#define NUM_CAMPO_REG 4

#define NOME_ARQ_IND "convertidoIndividuos.txt"
#define NOME_ARQ_RACAS "convertidoRacas.txt"
#define NOME_ARQ_IP1 "ip1.txt"
#define NOME_ARQ_IS2 "is2.txt"
#define NOME_ARQ_IP3 "ip3.txt"
#define NOME_ARQ_LISTAIP1 "listaIP1.txt"
#define NOME_ARQ_LISTAIS2 "listaIS2.txt"

extern Indice ip1;
extern Indice is2;
extern Indice ip3;
extern ListaI listaIP1;
extern ListaI listaIS2;

bool carregarIndices();
bool importarArq();
bool inserirIndividuo();
bool buscaID(Indice ip, char nomeArquivo[], char* campoRetorno[]);

#endif