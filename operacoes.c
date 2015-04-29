#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "operacoes.h"
#include "util.h"
#include "arquivos.h"

#define DELIM "|"
#define MAX_CAMPO 50
#define MAX_TAM_REG 512
#define NUM_CAMPO_REG 4

Indice ip1;
Indice is2;
Indice ip3;
ListaI listaIP1;
ListaI listaIS2;

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
        printf("%d -- %s\n", tam_reg, buffer);

        lerRegIndice(campo, byteOffset);

        byteOffset += tam_reg + sizeof(tam_reg);
        int i;
        for (i = 0; i < NUM_CAMPO_REG; i++)
            free(campo[i]);
    }
}

void importarArq(){
    FILE* arquivoIndividuos, *arquivoRacas, *convertidoIndividuos, *convertidoRacas;
    char nomeArquivoInd[20];
    char nomeArquivoRacas[20];

    do {
        printf("\nDigite o nome do arquivo de INDIVIDUOS ou 0 para cancelar: ");
        gets(nomeArquivoInd);
        if (strcmp(nomeArquivoInd, "0") == 0)
            return;
        arquivoIndividuos = abrirArquivo(nomeArquivoInd, "r");
    } while (arquivoIndividuos == NULL);

    do {
        printf("\nDigite o nome do arquivo de RACAS ou 0 para cancelar: ");
        gets(nomeArquivoRacas);
        if (strcmp(nomeArquivoRacas, "0") == 0)
            return;
        arquivoRacas = abrirArquivo(nomeArquivoRacas, "r");
    } while (arquivoRacas == NULL);

    convertidoIndividuos = abrirArquivo("convertidoIndividuos.txt", "w");
    convertidoRacas = abrirArquivo("convertidoRacas.txt", "w");

    converterArquivo(arquivoIndividuos, convertidoIndividuos, lerRegIndiceIndividuos);
    converterArquivo(arquivoRacas, convertidoRacas, lerRegIndiceRacas);

    qsort_indice(&ip1);
    qsort_indice(&is2);
    qsort_indice(&ip3);

    criaArqIndice(ip1, "ip1.txt", TIPO_IP1);
    criaArqIndice(is2, "is2.txt", TIPO_IS2);
    criaArqIndice(ip3, "ip3.txt", TIPO_IP3);
    criaArqListaI(listaIP1, "listaIP1.txt");
    criaArqListaI(listaIS2, "listaIS2.txt");

    fclose(arquivoIndividuos);
    fclose(arquivoRacas);
    fclose(convertidoIndividuos);
    fclose(convertidoRacas);
}

void inserirIndividuo(){
    FILE* arquivo;
    int id;
    int raca;
    short tam_reg;
    char campo[MAX_CAMPO];
    char buffer[MAX_TAM_REG + 1] = "";

    printf("Tela de cadastro de cachorros!\n\n");
    printf("Digite o id do Cachorro: ");
    scanf("%d", &id);
    limpar_stdin();

    while(buscaBinaria(ip3, id) > -1){
        printf("Id existente! \nDigite outro id: ");
        scanf("%d", &id);
        limpar_stdin();

    }

    itoa(id, campo, 10);
    strcat(buffer, campo);
    strcat(buffer, DELIM);
    campo[0] = '\0';

    printf("Digite o ID da raca: ");
    scanf("%d", &raca);
    limpar_stdin();
    while(buscaBinaria(ip1, raca) == -1){
        printf("Nao existe raca com esse id!\n");
        printf("Digite o ID da raca: ");
        scanf("%d", &raca);
        limpar_stdin();
    }

    itoa(raca, campo, 10);
    strcat(buffer, campo);
    strcat(buffer, DELIM);
    campo[0] = '\0';

    printf("Digite o nome do Cachorro: ");
    //gets(nome);
    scanf("%s", campo);
    limpar_stdin();
    strcat(buffer, campo);
    strcat(buffer, DELIM);
    campo[0] = '\0';


    printf("Digite o sexo do Cachorro: ");
    gets(campo);
    strcat(buffer, campo);
    strcat(buffer, DELIM);
    campo[0] = '\0';

    arquivo = fopen("convertidoIndividuos.txt", "a");
    printf("\nAbriu\n");

    tam_reg = strlen(buffer);

    fwrite(&tam_reg, 1, sizeof(tam_reg), arquivo);
    fwrite(buffer, 1, tam_reg, arquivo);
    fclose(arquivo);
}

void buscaID(Indice ip, char nomeArquivo[]){
    FILE* arquivo;
    int id;
    int posicao;
    short tam_reg;
    char buffer[MAX_TAM_REG];

    printf("Digite o ID: ");
    scanf("%d", &id);
    limpar_stdin();

    posicao = buscaBinaria(ip, id);
    arquivo = abrirArquivo(nomeArquivo, "r");

    fseek(arquivo, ip.reg[posicao].offset, SEEK_SET);
    fread(&tam_reg, 1, sizeof(tam_reg), arquivo);
    fread(buffer, 1, tam_reg, arquivo);

    printf("%s\n", buffer);
}