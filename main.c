#include <stdio.h>
#include <stdlib.h>
#include "operacoes.h"
#include "util.h"

void menuBusca(){
    int op;
    do {
        printf("\nSelecione o tipo da busca\n");
        printf("(1) - Buscar INDIVIDUOS pelo seu ID\n");
        printf("(2) - Buscar RACA pelo ID da raca\n");
        printf("(3) - Buscar RACAS pertencentes a um grupo\n");
        printf("(4) - Buscar INDIVIDUOS pertencentes a uma raca\n");
        printf("(5) - Buscar INDIVIDUOS pertencentes a uma raca e determinado sexo\n");
        printf("(6) - Voltar para o menu principal\n");
        printf("\nDigite sua opcao: ");
        scanf("%d", &op);
        limpar_stdin();

        switch(op){
            case 1:
                buscaID(ip3, "convertidoIndividuos.txt");
                break;
            case 2:
                buscaID(ip1, "convertidoRacas.txt");
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
            case 6:
                break;
            default:
                system("cls");
                printf("\nERRO: Opcao invalida\n");
        }
    } while (op != 6);
}

void menu(){
    int op;

    //mostrar titulo
    do {
        printf("(1) - Importar arquivo\n");
        printf("(2) - Inserir individuo\n");
        printf("(3) - Buscar\n");
        printf("(4) - Sair\n");
        printf("\nDigite sua opcao: ");
        scanf("%d", &op);
        limpar_stdin();

        switch(op){
            case 1:
                importarArq();
                break;
            case 2:
                inserirIndividuo();
                break;
            case 3:
                menuBusca();
                break;
            case 4:
                break;
            default:
                system("cls");
                printf("\nERRO: Opcao invalida\n");
        }
    } while (op != 4);
}

int main(int argc, char const *argv[]){
    /*FILE* arquivo = abrirArquivo("convertidoIndividuos.txt","r");
    int i;
    short tam;
    for(i = 0; i < 60; i++){
        char buffer[512] = "";
        fread(&tam, 1, 2, arquivo);
        fread(buffer, 1, tam, arquivo);
        printf("%d -- %s\n", tam, buffer);
    }*/

    menu();

    pressEnter();
    return 0;
}
