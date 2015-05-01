#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "operacoes.h"
#include "util.h"
#include "arquivos.h"
#include "indice.h"

#define DELIM "|"
#define MAX_TAM_REG 512

Indice ip1;
Indice is2;
Indice ip3;
ListaI listaIP1;
ListaI listaIS2;

bool carregarIndices(){
    if (!arqExiste(NOME_ARQ_IND) || !arqExiste(NOME_ARQ_RACAS))
        return false;

    ip1 = lerArqIndice(NOME_ARQ_IP1, TIPO_IP1);
    if (ip1.tam == 0)
        return false;

    is2 = lerArqIndice(NOME_ARQ_IS2, TIPO_IS2);
    if (is2.tam == 0)
        return false;

    ip3 = lerArqIndice(NOME_ARQ_IP3, TIPO_IP3);
    if (ip3.tam == 0)
        return false;

    listaIP1 = lerArqListaI(NOME_ARQ_LISTAIP1);
    if (listaIP1.tam == 0)
        return false;

    listaIS2 = lerArqListaI(NOME_ARQ_LISTAIS2);
    if (listaIS2.tam == 0)
        return false;

    return true;
}

char* lerCampo(FILE* arq){
    char *campo = malloc(MAX_CAMPO * sizeof(char));
    fgets(campo, MAX_CAMPO, arq);
    campo[strlen(campo) - 1] = '\0';

    return campo;
}

void lerRegIndiceIndividuos(char* campo[], int byteOffset){
    ip3.reg[ip3.tam].chave = atoi(campo[0]);
    ip3.reg[ip3.tam].offset = byteOffset;
    ip3.tam++;

    inserirListaI(&listaIP1, atoi(campo[0]), atoi(campo[1]));
}

void lerRegIndiceRacas(char* campo[], int byteOffset){
    ip1.reg[ip1.tam].chave = atoi(campo[0]);
    ip1.reg[ip1.tam].offset = byteOffset;
    ip1.reg[ip1.tam].rrn = atribuiRRN(listaIP1, ip1.reg[ip1.tam].chave);
    ip1.tam++;

    bool idg_unico = inserirListaI(&listaIS2, atoi(campo[0]), atoi(campo[2]));
    if (idg_unico){
        is2.reg[is2.tam].chave = atoi(campo[2]);
        is2.reg[is2.tam].rrn = listaIS2.tam - 1;
        is2.tam++;
    }
}

void converterArquivo(FILE* entrada, FILE* saida, void (*lerRegIndice)(char* campo[], int byteOffset)){
    char* campo[NUM_CAMPO_REG];
    char buffer[MAX_TAM_REG + 1] = "";
    short tam_reg = 0;
    int byteOffset = 0;

    while(!fimArquivo(entrada)){
        strcpy(buffer, ""); //Zera o buffer
        tam_reg = 0;

        int j;
        for (j = 0; j < NUM_CAMPO_REG; ++j){
            campo[j] = lerCampo(entrada);
            strcat(buffer, campo[j]);
            strcat(buffer, DELIM);
        }

        tam_reg = strlen(buffer);

        fwrite(&tam_reg, sizeof(tam_reg), 1, saida);
        fwrite(buffer, tam_reg, 1, saida);

        lerRegIndice(campo, byteOffset);

        byteOffset += tam_reg + sizeof(tam_reg);
        int i;
        for (i = 0; i < NUM_CAMPO_REG; i++)
            free(campo[i]);
    }
}

bool importarArq(){
    FILE* arquivoIndividuos, *arquivoRacas, *convertidoIndividuos, *convertidoRacas;
    char nomeArquivoInd[20];
    char nomeArquivoRacas[20];

    do {
        printf("\nDigite o nome do arquivo de INDIVIDUOS ou 0 para cancelar: ");
        gets(nomeArquivoInd);
        if (strcmp(nomeArquivoInd, "0") == 0)
            return false;
        arquivoIndividuos = abrirArquivo(nomeArquivoInd, "r");
    } while (arquivoIndividuos == NULL);

    do {
        printf("\nDigite o nome do arquivo de RACAS ou 0 para cancelar: ");
        gets(nomeArquivoRacas);
        if (strcmp(nomeArquivoRacas, "0") == 0)
            return false;
        arquivoRacas = abrirArquivo(nomeArquivoRacas, "r");
    } while (arquivoRacas == NULL);

    convertidoIndividuos = abrirArquivo(NOME_ARQ_IND, "w");
    convertidoRacas = abrirArquivo(NOME_ARQ_RACAS, "w");

    converterArquivo(arquivoIndividuos, convertidoIndividuos, lerRegIndiceIndividuos);
    converterArquivo(arquivoRacas, convertidoRacas, lerRegIndiceRacas);

    qsort_indice(&ip1);
    qsort_indice(&is2);
    qsort_indice(&ip3);

    criaArqIndice(ip1, NOME_ARQ_IP1, TIPO_IP1);
    criaArqIndice(is2, NOME_ARQ_IS2, TIPO_IS2);
    criaArqIndice(ip3, NOME_ARQ_IP3, TIPO_IP3);
    criaArqListaI(listaIP1, NOME_ARQ_LISTAIP1);
    criaArqListaI(listaIS2, NOME_ARQ_LISTAIS2);

    fclose(arquivoIndividuos);
    fclose(arquivoRacas);
    fclose(convertidoIndividuos);
    fclose(convertidoRacas);

    return true;
}

bool inserirIndividuo(){
    FILE* arquivo;
    int idi;
    int idr;
    int posicao;
    short tam_reg;
    char campo[MAX_CAMPO];
    char buffer[MAX_TAM_REG + 1] = "";

    printf("\nTela de cadastro de cachorros:\n\n");

    idi = lerInt("Digite o ID do Cachorro ou 0 para cancelar: ");
    if (idi == 0)
        return false;
    while((posicao = buscaBinaria(ip3, idi)) > -1){
        printf("ERRO: O ID ja existe!\n");
        idi = lerInt("Digite outro ID ou 0 para cancelar: ");
        if (idi == 0)
            return false;
    }

    itoa(idi, campo, 10);
    strcat(buffer, campo);
    strcat(buffer, DELIM);
    campo[0] = '\0';

    idr = lerInt("Digite o ID da raca ou 0 para cancelar: ");
    if (idr <= 0) //Algum asno pode inserir negativo tambem!
        return false;
    while(buscaBinaria(ip1, idr) < 0){
        printf("ERRO: Nao existe raca com esse id!\n");
        idr = lerInt("Digite o ID da raca ou 0 para cancelar: ");
        if (idr == 0)
            return false;
    }

    itoa(idr, campo, 10);
    strcat(buffer, campo);
    strcat(buffer, DELIM);
    campo[0] = '\0';

    printf("Digite o nome do cachorro ou 0 para cancelar: ");
    gets(campo);
    if (strcmp(campo, "0") == 0)
        return false;
    strcat(buffer, campo);
    strcat(buffer, DELIM);
    campo[0] = '\0';

    printf("Digite o sexo do cachorro ou 0 para cancelar: ");
    gets(campo);
    if (strcmp(campo, "0") == 0)
        return false;
    strcat(buffer, campo);
    strcat(buffer, DELIM);
    campo[0] = '\0';

    /*
    *   Grava no arquivo de dados
    */
    arquivo = fopen(NOME_ARQ_IND, "r+");
    fseek(arquivo, 0, SEEK_END);

    int offset = ftell(arquivo);

    tam_reg = strlen(buffer);

    fwrite(&tam_reg, sizeof(tam_reg), 1, arquivo);
    fwrite(buffer, tam_reg, 1, arquivo);
    fclose(arquivo);

    /*
    *   Insere na posição correta do indice e insere na lista invertida de ip1
    */
    int i;
    posicao = -(posicao);
    for (i = ip3.tam; i > posicao; --i)
        ip3.reg[i] = ip3.reg[i-1];

    ip3.reg[posicao].chave = idi;
    ip3.reg[posicao].offset = offset;
    ip3.tam++;

    inserirListaI(&listaIP1, idi, idr);

    criaArqIndice(ip3, NOME_ARQ_IP3, TIPO_IP3);
    criaArqListaI(listaIP1, NOME_ARQ_LISTAIP1);

    return true;
}

void transformaBuffer(char buffer[], char* campoRetorno[]){
    int i;
    campoRetorno[0] = strtok(buffer, DELIM);
    for (i = 1; i < NUM_CAMPO_REG ; ++i)
        campoRetorno[i] = strtok(NULL, DELIM);
}

bool buscaID(Indice ip, char nomeArquivo[], char* campoRetorno[]){
    FILE* arquivo;
    int id;
    int posicao;
    short tam_reg;
    char buffer[MAX_TAM_REG] = "";

    id = lerInt("Digite o ID ou 0 para cancelar: ");
    if (id == 0)
        return false;
    posicao = buscaBinaria(ip, id);

    while (posicao < 0){
        printf("\nERRO: ID nao existe.\n");
        id = lerInt("\nDigite o ID ou 0 para cancelar: ");
        if (id == 0)
            return false;
        posicao = buscaBinaria(ip, id);
    }

    arquivo = abrirArquivo(nomeArquivo, "r");

    fseek(arquivo, ip.reg[posicao].offset, SEEK_SET);
    fread(&tam_reg, sizeof(tam_reg), 1, arquivo);
    fread(buffer, tam_reg, 1, arquivo);

    transformaBuffer(buffer, campoRetorno);
    return true;
}
