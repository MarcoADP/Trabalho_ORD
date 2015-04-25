#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "arquivo.h"
#include "util.h"
#include "indice.h"

char* buscaIndividuo(){
    FILE* convertido = fopen("convertidoIndividuo.txt","r");
    FILE* indice = fopen("ip3.txt","r");
    int id_escolhido;
    int id;
    int referencia;
    char* campo[2];

    printf("\nDigite o ID do INDIVIDUO: ");
    scanf("%d", &id_escolhido);
    limpar_stdin();

    while(!fimArquivo(indice)){
        fscanf(indice,"%d %d \n", &id, &referencia);

        if(id_escolhido == id){
            printf("ID: %d\n", id);
            printf("REFERENCIA: %d\n\n", referencia);
            return "ID ENCONTRADO!";

        }
    }
    fclose(convertido);
    fclose(indice);
    return "Individuo não encontrado!";

}

void busca(){
    int op = 0;
    printf("\nSelecione o tipo da busca\n");
    printf("(1) - Buscar INDIVIDUOS pelo seu ID\n");
    printf("(2) - Buscar RACA pelo ID da raca\n");
    printf("(3) - Buscar RACAS pertencentes a um grupo\n");
    printf("(4) - Buscar INDIVIDUOS pertencentes a uma raca\n");
    printf("(5) - Buscar INDIVIDUOS pertencentes a uma raca e determinado sexo\n");
    printf("\nDigite sua opcao: ");
    scanf("%d", &op);
    limpar_stdin();

    switch(op){
        case 1:
            printf("%s\n",buscaIndividuo());
        break;
        case 2:
            //Buscar através de ip1
        break;
        case 3:
            //Buscar através da lista invertida + is2
        break;
        case 4:
            //Buscar através da lista invertida + ip1
        break;
        case 5:
            //Buscar através da lista invertida + ip1
        break;
    }
}
