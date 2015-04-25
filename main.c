#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "indice.h"
#include "arquivo.h"

/*#define DELIM "|"
#define MAX_CAMPO 50
#define MAX_REG 512
#define NUM_CAMPO_REG 4

#define RACAS 0
#define INDIVIDUOS 1*/

Indice ip1;
Indice is2;
Indice ip3;



void importarArq(){
    FILE* arquivo;
    FILE* convertido;
    char nomeArquivo[20];
    int op = 0;

    printf("Digite o nome do arquivo: ");
    gets(nomeArquivo);

    printf("\nSelecione o tipo do arquivo\n");
    printf("(1) - Racas\n");
    printf("(2) - Individuos\n");
    printf("\nDigite sua opcao: ");
    scanf("%d", &op);
    limpar_stdin();

    arquivo = abrirArquivo(nomeArquivo, "r");
    convertido = abrirArquivo("convertido.txt", "w");

    switch(op){
        case 1:
            //cria indices primario e secundario com lista invertida
        break;
        case 2:
            //cria indice primario
            converterArquivo(arquivo, convertido, lerRegIndiceIndividuos);
            criaArqIndice(ip3, "ip3.txt");
        break;
    }

    //INDICES

    fclose(arquivo);
    fclose(convertido);
}

void menu(){
    int op = 0;

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

        break;

        case 3:

        break;
    }
}

int main(int argc, char const *argv[]){
    menu();

    pressEnter();
    return 0;
}
