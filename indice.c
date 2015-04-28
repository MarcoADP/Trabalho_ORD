#include <stdio.h>
#include <stdlib.h>
#include "indice.h"
#include "arquivos.h"

void trocaValor(RegIndice* x, RegIndice* y){
    RegIndice aux;
    aux = *x;
    *x = *y;
    *y = aux;
}

int partition(RegIndice reg_indice[], int esquerda, int direita){
    int pivo, i;

    pivo = esquerda;
    for (i = esquerda + 1; i <= direita; ++i){
        if (reg_indice[i].chave < reg_indice[esquerda].chave){
            ++pivo;
            trocaValor(&reg_indice[pivo], &reg_indice[i]);
        }
    }
    trocaValor(&reg_indice[esquerda], &reg_indice[pivo]);

    return pivo;
}

void quicksort(RegIndice reg_indice[], int esquerda, int direita){
    int pivo;
    if (esquerda < direita){
        pivo = partition(reg_indice, esquerda, direita);
        quicksort(reg_indice, esquerda, pivo - 1);
        quicksort(reg_indice, pivo + 1, direita);
    }
}

void qsort_indice(Indice *ind){
    quicksort(ind->reg, 0, ind->tam - 1);
}

void criaArqIndice(Indice ind, char nomeArquivo[], int tipo){
    FILE* arqIndice;
    int i;
    
    arqIndice = abrirArquivo(nomeArquivo, "w");
    switch(tipo){
        case TIPO_IP1:
            for (i = 0; i < ind.tam; ++i)
                fprintf(arqIndice, "%d %d %d\n", ind.reg[i].chave, ind.reg[i].offset, ind.reg[i].rrn);
        break;
        case TIPO_IS2:
            for (i = 0; i < ind.tam; ++i)
                fprintf(arqIndice, "%d %d\n", ind.reg[i].chave, ind.reg[i].rrn);
        break;
        case TIPO_IP3:
            for (i = 0; i < ind.tam; ++i)
                fprintf(arqIndice, "%d %d\n", ind.reg[i].chave, ind.reg[i].offset);
        break;
    }

    fclose(arqIndice);
}

/*
    retorna false se a chave_sec já existe na lista, caso contrario retorna true
*/
bool inserirListaI(ListaI* lista, int chave, int chave_sec){
    int i;
    for (i = lista->tam - 1; i >= 0; --i){
        if (-(chave_sec) == lista->reg[i].prox) {
            lista->reg[i].prox = lista->tam;
            break;
        }
    }

    lista->reg[lista->tam].chave = chave;
    lista->reg[lista->tam].prox = -(chave_sec);
    lista->tam++;

    return (i == -1);
}

void criaArqListaI(ListaI lista, char nomeArquivo[]){
    FILE* arqLista;
    int i;
    
    arqLista = abrirArquivo(nomeArquivo, "w");
    
    for (i = 0; i < lista.tam; ++i)
        fprintf(arqLista, "%d %d\n", lista.reg[i].chave, lista.reg[i].prox);

    fclose(arqLista);
}

int atribuiRRN(ListaI lista, int chave_primaria){
    ListaI temp = lista;
    int i, j;
    for (i = 0; i < temp.tam; ++i){
        if (temp.reg[i].chave >= 0){
            j = i;
            do {
                j = temp.reg[j].prox;
    
                if (-(j) == chave_primaria)
                    return i;
    
                temp.reg[j].chave = -1;
            } while (j > 0);
        }
    }

    return -1;
}