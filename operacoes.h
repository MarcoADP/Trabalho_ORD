#ifndef OPERACOES_H
#define OPERACOES_H

#include "indice.h"

#define MAX_CAMPO 50
#define NUM_CAMPO_REG 4
#define CAMPO_REG 99

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

typedef struct campo_retorno CampoRetorno;
struct campo_retorno {
    char campo[CAMPO_REG][NUM_CAMPO_REG][MAX_CAMPO];
    int tam;
};

bool carregarIndices();
bool importarArq();
bool inserirIndividuo();
int recuperaPosicaoID(Indice ind, char msg[]);
bool buscaID(Indice ind, int posicao, char nomeArquivo[], CampoRetorno *retorno);
bool buscaLista(Indice ind1, int posicao, ListaI lista, Indice ind2, char nomeArquivo[], CampoRetorno *retorno);

#endif
