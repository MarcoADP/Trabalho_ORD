#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "busca.h"
#include "util.h"

#define MAX_TAM_REG 512

int buscab_indice(RegIndice reg_indice[], int chave, int esquerda, int direita){
    if (esquerda >= direita)
        return -1;
    int meio = (esquerda + direita)/2;
    if (chave == reg_indice[meio].chave)
        return meio;
    if (chave > reg_indice[meio].chave)
        return buscab_indice(reg_indice, chave, meio + 1, direita);
    else //if (chave < reg_indice[meio].chave)
        return buscab_indice(reg_indice, chave, esquerda, meio);
}

int buscaBinaria(Indice ind, int chave){
    return buscab_indice(ind.reg, chave, 0, ind.tam);
}

void buscaID(Indice ip, char nomeArquivo[]){
    int id;
    int posicao;
    short tam_reg;
    char buffer[MAX_TAM_REG];

    FILE* individuos;
    printf("Digite o ID: ");
    scanf("%d", &id);
    limpar_stdin();

    posicao = buscaBinaria(ip, id);
    individuos = abrirArquivo(nomeArquivo, "r");
    fseek(individuos, ip.reg[posicao].offset, SEEK_SET);
    fread(&tam_reg, 1, sizeof(tam_reg), individuos);
    fread(buffer, 1, tam_reg, individuos);

    printf("%s\n", buffer);
}
