#ifndef OPERACOES_H
#define OPERACOES_H

#include "indice.h"

#define TAM_MAX_CAMPO 50
#define NUM_CAMPO_POR_REG 4
#define MAX_REG 100

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
    char campo[MAX_REG][NUM_CAMPO_POR_REG][TAM_MAX_CAMPO];
    int tam;
};

bool salvarEmArquivo();
bool carregarIndices();
bool importarArq();
bool inserirIndividuo();
char lerSexo();
int recuperaPosicaoID(Indice ind, char msg[]);
void buscaID(Indice ind, int posicao, FILE* arquivo, CampoRetorno *retorno, char *condicaoSexo);
CampoRetorno buscaLista(Indice ind1, int posicao, ListaI lista, Indice ind2, FILE* arquivo, char *condicaoSexo);

#endif
