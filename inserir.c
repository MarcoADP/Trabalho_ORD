#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "arquivo.h"
#include "util.h"
#include "indice.h"
#include "busca.h"

#define DELIM "|"
#define MAX_CAMPO 50
#define MAX_REG 512
#define NUM_CAMPO_REG 4

void inserirIndividuo(){
    FILE* arquivo;
    int id;
    int raca;
    char id_s[MAX_CAMPO];
    char raca_s[MAX_CAMPO];
    char nome[99];
    char sexo[1];
    char buffer[MAX_REG + 1] = "";
    char teste[MAX_REG + 1] = "Teste";

    printf("Tela de cadastro de cachorros!\n\n");
    printf("Digite o id do Cachorro: ");
    scanf("%d", &id);
    limpar_stdin();

    while(buscaIndividuo(id)){
        printf("Id existente! \nDigite outro id: ");
        scanf("%d", &id);
        limpar_stdin();

    }

    //Fazer a verificação se o id EXISTE
    printf("Digite o ID da raca: ");
    scanf("%d", &raca);
    limpar_stdin();

    printf("Digite o nome do Cachorro: ");
    //gets(nome);
    scanf("%s", nome);
    limpar_stdin();
    printf("NOME: %s\n\n", nome);

    printf("Digite o sexo do Cachorro: ");
    gets(sexo);
    //limpar_stdin();

    itoa(id, id_s, 10);
    itoa(raca, raca_s, 10);

    strcat(buffer, id_s);
    strcat(buffer, DELIM);
    strcat(buffer, raca_s);
    strcat(buffer, DELIM);
    strcat(teste, nome);
    strcat(buffer, DELIM);
    printf("BUFFER%s\n", teste);
    strcat(buffer, sexo);
    strcat(buffer, DELIM);
    printf("Tamanho: %d\n", strlen(buffer));
    printf("%s", buffer);

    arquivo = fopen("convertidoIndividuo.txt","r+");
    printf("\nAbriu\n");
    fclose(arquivo);
}


