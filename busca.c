#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "arquivo.h"
#include "util.h"
#include "indice.h"

bool buscaIndividuo(int id_escolhido){
    FILE* convertido = fopen("convertidoIndividuo.txt","r");
    FILE* indice = fopen("ip3.txt","r");
    int id;
    int referencia;
    char* campo[4];
    char* resultado;
    int j = 0;


    while(!fimArquivo(indice)){
        fscanf(indice,"%d %d \n", &id, &referencia);

        if(id_escolhido == id){
            printf("ID: %d\n", id);
            printf("REFERENCIA: %d\n\n", referencia);
            fseek(convertido, referencia+2, SEEK_SET);

            /*for (j = 0; j < 4; j++){
                campo[j] = lerCampo(convertido);
                printf("CAMPO: %s\n", campo[j]);
            }*/
            resultado = lerCampo(convertido);

            while(j<4){
                if (j == 0){
                    campo[0] = (char*)strtok(resultado, "|");
                } else {
                    campo[j] = (char*)strtok(NULL, "|");
                }
                j++;
            }
            printf("%s\n", campo[0]);
            printf("%s\n", campo[1]);
            printf("%s\n", campo[2]);
            printf("%s\n", campo[3]);

            return true;
        }
    }
    fclose(convertido);
    fclose(indice);
    return false;

}


void busca(){
    int id_escolhido;
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
            printf("\nDigite o ID do INDIVIDUO: ");
            scanf("%d", &id_escolhido);
            limpar_stdin();

            if(!buscaIndividuo(id_escolhido))
                printf("Nao encontrado!\n");
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
