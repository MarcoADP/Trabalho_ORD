#ifndef INDICE_H
#define INDICE_H

#define MAX_CAMPO_IND 50
#define MAX_REG_IND 100

typedef struct reg_indice RegIndice;
struct reg_indice {
    char chave[MAX_CAMPO_IND];
    char referencia[MAX_CAMPO_IND];
};

typedef struct indice Indice;
struct indice {
    RegIndice reg[MAX_REG_IND];
    //int flag;
    int tam;
};

void lerRegIndiceIndividuos(char* campo[], int byteOffset, int i);

void criaArqIndice(Indice ind, char nomeArquivo[]);


#endif
