#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "operacoes.h"
#include "util.h"
#include "arquivo.h"
#include "indice.h"

#define DELIM "|"
#define MAX_TAM_REG 512
#define TAM_FLAG_DATA 19

Indice ip1;
Indice is2;
Indice ip3;
ListaI listaIP1;
ListaI listaIS2;

bool salvarEmArquivo(){
    criaArqIndice(ip1, NOME_ARQ_IP1, TIPO_IP1);
    criaArqIndice(is2, NOME_ARQ_IS2, TIPO_IS2);
    criaArqIndice(ip3, NOME_ARQ_IP3, TIPO_IP3);
    criaArqListaI(listaIP1, NOME_ARQ_LISTAIP1);
    criaArqListaI(listaIS2, NOME_ARQ_LISTAIS2);

    return true;
}

bool verificaFlagData(){
    char data_arq_ind[20] = "";
    char data_arq_racas[20] = "";
    FILE* arquivo_ind = fopen(NOME_ARQ_IND, "r");
    FILE* arquivo_racas = fopen(NOME_ARQ_RACAS, "r");
    fread(data_arq_ind, TAM_FLAG_DATA, 1, arquivo_ind);
    fread(data_arq_racas, TAM_FLAG_DATA, 1, arquivo_racas);
    fclose(arquivo_ind);
    fclose(arquivo_racas);

    if (strcmp(data_arq_ind, ip1.flag_data) != 0)
        return false;
    if (strcmp(data_arq_ind, ip3.flag_data) != 0)
        return false;
    if (strcmp(data_arq_racas, is2.flag_data) != 0)
        return false;

    return true;
}

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

    if (!verificaFlagData())
        return false;

    return true;
}

char* lerCampo(FILE* arq){
    char *campo = malloc(MAX_CAMPO * sizeof(char));
    fgets(campo, MAX_CAMPO, arq);
    if (strlen(campo) > 1)
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

void converterArquivo(FILE* entrada, FILE* saida, void (*lerRegIndice)(char* campo[], int byteOffset), char tempo_atual[]){
    char* campo[NUM_CAMPO_REG];
    char buffer[MAX_TAM_REG + 1] = "";
    short tam_reg = 0;
    int byteOffset = TAM_FLAG_DATA;

    fwrite(tempo_atual, strlen(tempo_atual), 1, saida);

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
    char tempo_atual[50];

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

    ip1.tam = 0;
    is2.tam = 0;
    ip3.tam = 0;
    listaIP1.tam = 0;
    listaIS2.tam = 0;

    obterTempoAtual(tempo_atual);

    converterArquivo(arquivoIndividuos, convertidoIndividuos, lerRegIndiceIndividuos, tempo_atual);
    converterArquivo(arquivoRacas, convertidoRacas, lerRegIndiceRacas, tempo_atual);

    qsort_indice(&ip1);
    qsort_indice(&is2);
    qsort_indice(&ip3);

    strcpy(ip1.flag_data, tempo_atual);
    strcpy(is2.flag_data, tempo_atual);
    strcpy(ip3.flag_data, tempo_atual);

    //criaArqIndice(ip1, NOME_ARQ_IP1, TIPO_IP1);
    //criaArqIndice(is2, NOME_ARQ_IS2, TIPO_IS2);
    //criaArqIndice(ip3, NOME_ARQ_IP3, TIPO_IP3);
    //criaArqListaI(listaIP1, NOME_ARQ_LISTAIP1);
    //criaArqListaI(listaIS2, NOME_ARQ_LISTAIS2);

    fclose(arquivoIndividuos);
    fclose(arquivoRacas);
    fclose(convertidoIndividuos);
    fclose(convertidoRacas);

    return true;
}

char lerSexo(){
    char sexo[1];

    printf("\n(M)asculino ou (F)eminino\n");
    printf("Digite o sexo do cachorro ou 0 para cancelar: ");
    gets(sexo);
    if (strcmp(sexo, "0") == 0)
        return '0';
    sexo[0] = toupper(sexo[0]);
    while (strcmp(sexo, "M") && strcmp(sexo, "F")){
        printf("\nERRO: Sexo inexistente!\n");
        printf("\n(M)asculino ou (F)eminino\n");
        printf("Digite o sexo do cachorro ou 0 para cancelar: ");
        gets(sexo);
        if (strcmp(sexo, "0") == 0)
            return '0';
        sexo[0] = toupper(sexo[0]);
    }

    return sexo[0];
}

bool inserirIndividuo(){
    FILE* arquivo;
    int idi;
    int idr;
    int posicao_idi;
    int posicao_idr;
    short tam_reg;
    char campo[MAX_CAMPO];
    char buffer[MAX_TAM_REG + 1] = "";
    char flag_data[20];
    obterTempoAtual(flag_data);

    printf("\nCadastro de cachorros:\n\n");

    idi = lerInt("Digite o ID do Cachorro ou 0 para cancelar: ");
    if (idi == 0)
        return false;
    while((posicao_idi = buscaBinaria(ip3, idi)) > -1 || idi < 0){
        printf("ERRO: O ID eh invalido ou ja existe!\n");
        idi = lerInt("\nDigite outro ID ou 0 para cancelar: ");
        if (idi == 0)
            return false;
    }

    itoa(idi, campo, 10);
    strcat(buffer, campo);
    strcat(buffer, DELIM);
    campo[0] = '\0';

    idr = lerInt("\nDigite o ID da raca ou 0 para cancelar: ");
    if (idr == 0)
        return false;
    while((posicao_idr = buscaBinaria(ip1, idr)) < 0 || idr < 0){
        printf("ERRO: Nao existe raca com esse id!\n");
        idr = lerInt("\nDigite o ID da raca ou 0 para cancelar: ");
        if (idr == 0)
            return false;
    }

    itoa(idr, campo, 10);
    strcat(buffer, campo);
    strcat(buffer, DELIM);
    campo[0] = '\0';

    printf("\nDigite o nome do cachorro ou 0 para cancelar: ");
    gets(campo);
    if (strcmp(campo, "0") == 0)
        return false;

    int l;
    for(l = 0; l < strlen(campo); l++)
        campo[l] = toupper(campo[l]);
    
    strcat(buffer, campo);
    strcat(buffer, DELIM);
    campo[0] = '\0';

    campo[0] = lerSexo();
    campo[1] = '\0';
    if (campo[0] == '0')
        return false;

    strcat(buffer, campo);
    strcat(buffer, DELIM);
    campo[0] = '\0';

    /*
    *   Grava no arquivo de dados
    */
    arquivo = fopen(NOME_ARQ_IND, "r+");
    fwrite(flag_data, strlen(flag_data), 1, arquivo);
    
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
    posicao_idi = -(posicao_idi);
    for (i = ip3.tam; i > posicao_idi; --i)
        ip3.reg[i] = ip3.reg[i-1];

    ip3.reg[posicao_idi].chave = idi;
    ip3.reg[posicao_idi].offset = offset;
    ip3.tam++;

    bool idr_nao_existe = inserirListaI(&listaIP1, idi, idr);
    if (idr_nao_existe)
        ip1.reg[posicao_idr].rrn = atribuiRRN(listaIP1, idr);

    /*
    *   Atualiza flag data
    */

    strcpy(ip1.flag_data, flag_data);
    strcpy(ip3.flag_data, flag_data);
    return true;
}

/*
* Lê um ID e retorna a posicão no indice ou retorna -1 caso seja cancelado.
*/
int recuperaPosicaoID(Indice ind, char msg[]){
    int id, posicao;

    id = lerInt(msg);
    if (id == 0)
        return -1;

    posicao = buscaBinaria(ind, id);

    while (posicao < 0 || id < 0){
        printf("\nERRO: ID nao existe.\n");
        id = lerInt(msg);
        if (id == 0)
            return -1;
        posicao = buscaBinaria(ind, id);
    }

    return posicao;
}

void buscaID(Indice ind, int posicao, FILE* arquivo, CampoRetorno *retorno, char *condicaoSexo){
    short tam_reg;
    char buffer[MAX_TAM_REG] = "";

    fseek(arquivo, ind.reg[posicao].offset, SEEK_SET);
    fread(&tam_reg, sizeof(tam_reg), 1, arquivo);
    fread(buffer, tam_reg, 1, arquivo);

    int i;
    strcpy(retorno->campo[retorno->tam][0], strtok(buffer, DELIM));
    for (i = 1; i < NUM_CAMPO_REG; ++i)
        strcpy(retorno->campo[retorno->tam][i], strtok(NULL, DELIM));
    
    if (condicaoSexo == NULL || strcmp(retorno->campo[retorno->tam][3], condicaoSexo) == 0)
        retorno->tam++;
}

CampoRetorno buscaLista(Indice ind1, int posicao, ListaI lista, Indice ind2, FILE* arquivo, char *condicaoSexo){
    CampoRetorno retorno;
    retorno.tam = 0;
    int posicaoLista;
    int chave;
    int posicaoReg;

    posicaoLista = ind1.reg[posicao].rrn;

    while (posicaoLista > -1){
        chave = lista.reg[posicaoLista].chave;        
        posicaoReg = buscaBinaria(ind2, chave);
        buscaID(ind2, posicaoReg, arquivo, &retorno, condicaoSexo);
        posicaoLista = lista.reg[posicaoLista].prox;
    }

    return retorno;
}