#include <stdio.h>
#include <stdlib.h>
#include "indice.h"
#include "arquivo.h"

Indice lerArqIndice(char nomeArquivo[], int tipo){
    FILE* arqIndice;
    Indice ind;
    ind.tam = 0;
    arqIndice = abrirArquivo(nomeArquivo, "r");

    if (arqIndice == NULL)
        return ind;

    if (fscanf(arqIndice, "%s\n", ind.flag_data) != 1){
        fclose(arqIndice);
        return ind;
    }

    switch(tipo){
        case TIPO_IP1:
            while (!fimArquivo(arqIndice)){
                if (fscanf(arqIndice, "%d %d %d\n", &ind.reg[ind.tam].chave, &ind.reg[ind.tam].offset, &ind.reg[ind.tam].rrn) != 3){
                    ind.tam = 0;
                    fclose(arqIndice);
                    return ind;
                }
                ind.tam++;
                
            }
        break;
        case TIPO_IS2:
            while (!fimArquivo(arqIndice)){
                if (fscanf(arqIndice, "%d %d\n", &ind.reg[ind.tam].chave, &ind.reg[ind.tam].rrn) != 2){
                    ind.tam = 0;
                    fclose(arqIndice);
                    return ind;
                }
                ind.tam++;
            }
        break;
        case TIPO_IP3:
            while (!fimArquivo(arqIndice)){
                if (fscanf(arqIndice, "%d %d\n", &ind.reg[ind.tam].chave, &ind.reg[ind.tam].offset) != 2){
                    ind.tam = 0;
                    fclose(arqIndice);
                    return ind;
                }
                ind.tam++;
            }
        break;
    }

    fclose(arqIndice);
    return ind;
}

void criaArqIndice(Indice ind, char nomeArquivo[], int tipo){
    FILE* arqIndice;
    int i;
    
    arqIndice = abrirArquivo(nomeArquivo, "w");

    fprintf(arqIndice, "%s\n", ind.flag_data);

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

ListaI lerArqListaI(char nomeArquivo[]){
    FILE* arqLista;
    ListaI lista;
    lista.tam = 0;
    
    arqLista = abrirArquivo(nomeArquivo, "r");

    if (arqLista == NULL)
        return lista;
    
    while (!fimArquivo(arqLista)){
        fscanf(arqLista, "%d %d\n", &lista.reg[lista.tam].chave, &lista.reg[lista.tam].prox);
        lista.tam++;
    }

    fclose(arqLista);

    return lista;
}

void criaArqListaI(ListaI lista, char nomeArquivo[]){
    FILE* arqLista;
    int i;
    
    arqLista = abrirArquivo(nomeArquivo, "w");
    
    for (i = 0; i < lista.tam; ++i)
        fprintf(arqLista, "%d %d\n", lista.reg[i].chave, lista.reg[i].prox);

    fclose(arqLista);
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

int buscab_indice(RegIndice reg_indice[], int chave, int esquerda, int direita){
    int meio = (esquerda + direita)/2;
    if (esquerda >= direita)
        return -(meio);
    if (chave == reg_indice[meio].chave)
        return meio;
    if (chave > reg_indice[meio].chave)
        return buscab_indice(reg_indice, chave, meio + 1, direita);
    else
        return buscab_indice(reg_indice, chave, esquerda, meio);
}

int buscaBinaria(Indice ind, int chave){
    return buscab_indice(ind.reg, chave, 0, ind.tam);
}