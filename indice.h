#ifndef INDICE_H
#define INDICE_H

#include <stdbool.h>

#define MAX_REG_INDICE 100
#define MAX_REG_LISTA 100

#define TIPO_IP1 1
#define TIPO_IS2 2
#define TIPO_IP3 3

typedef struct reg_indice RegIndice;
typedef struct indice Indice;
typedef struct lista_invertida ListaI;
typedef struct reg_lista_invertida RegListaI;

struct reg_indice {
    int chave;
    int offset;
    int rrn;
};

struct indice {
    RegIndice reg[MAX_REG_INDICE];
    //int flag;
    int tam;
};

struct reg_lista_invertida {
    int chave;
    int prox;
};

struct lista_invertida {
    RegListaI reg[MAX_REG_LISTA];
    int tam;
};

Indice lerArqIndice(char nomeArquivo[], int tipo);
void criaArqIndice(Indice ind, char nomeArquivo[], int tipo);
ListaI lerArqListaI(char nomeArquivo[]);
void criaArqListaI(ListaI lista, char nomeArquivo[]);
bool inserirListaI(ListaI* lista, int chave, int chave_sec);
int atribuiRRN(ListaI lista, int chave);
void qsort_indice(Indice *ind);
int buscaBinaria(Indice ind, int chave);

#endif