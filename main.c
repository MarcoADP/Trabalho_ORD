#include <stdio.h>
#include <stdlib.h>
#include "operacoes.h"
#include "util.h"
#include "arquivos.h"

void menuBusca(){
    char* campoRetorno[NUM_CAMPO_REG];
    int op;
    clrscr();
    do {
        printf("\n-----------------------------------------------\n");
        printf("                 MENU DE BUSCA                 \n");
        printf("-----------------------------------------------\n");
        printf("(1) - Buscar INDIVIDUOS pelo seu ID\n");
        printf("(2) - Buscar RACA pelo ID da raca\n");
        printf("(3) - Buscar RACAS pertencentes a um grupo\n");
        printf("(4) - Buscar INDIVIDUOS pertencentes a uma raca\n");
        printf("(5) - Buscar INDIVIDUOS pertencentes a uma raca e determinado sexo\n");
        printf("(6) - Voltar para o menu principal\n");
        op = lerInt("\nDigite sua opcao: ");

        switch(op){
            case 1:
                if (buscaID(ip3, NOME_ARQ_IND, campoRetorno)){
                    clrscr();
                    printaRegistro(campoRetorno);
                }
                else {
                    clrscr();
                    printf("Busca cancelada.\n");
                }
                break;
            case 2:
                if (buscaID(ip1, NOME_ARQ_RACAS, campoRetorno)) {
                    clrscr();
                    printaRegistro(campoRetorno);
                }
                else {
                    clrscr();
                    printf("Busca cancelada.\n");
                }
                break;
            case 3:
                if (buscaLista(is2, listaIS2, campoRetorno, ip1)){
                    clrscr();
                    printaRegistro(campoRetorno);
                }
                //printaRegistro(campoRetorno);
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
                clrscr();
                printf("ERRO: Opcao invalida\n");
        }
    } while (op != 6);
}

void menuPrincipal(){
    int op;

    bool arquivosExistem = carregarIndices();

    if (arquivosExistem){
        printf("Arquivos de indices carregados com sucesso.\n");
        printf("Nao e necessario importar arquivos.\n");
    }
    else {
        printf("ERRO: Arquivos de dados ou de indices não existem.\n");
        printf("Faca a importacao dos arquivos.\n");
    }
    //mostrar titulo
    do {
        printf("\n-----------------------------------------------\n");
        printf("                 MENU PRINCIPAL                \n");
        printf("-----------------------------------------------\n");
        printf("(1) - Importar arquivo\n");
        printf("(2) - Inserir individuo\n");
        printf("(3) - Buscar\n");
        printf("(4) - Sair\n");
        op = lerInt("\nDigite sua opcao: ");

        switch(op){
            case 1:
                if (importarArq()){
                    clrscr();
                    printf("Arquivos importados e convertidos com sucesso.\n");
                    arquivosExistem = true;
                }
                else {
                    clrscr();
                    printf("Importacao cancelada.\n");
                }
                break;
            case 2:
                if (arquivosExistem){
                    if (inserirIndividuo()){
                        clrscr();
                        printf("Individuo inserido com sucesso.\n");
                    }
                    else {
                        clrscr();
                        printf("Insercao cancelada.\n");
                    }
                }
                else {
                    clrscr();
                    printf("ERRO: Arquivo de individuos ou de racas nao existe.\n");
                    printf("Importe os arquivos antes de inserir.\n");
                }
                break;
            case 3:
                if (arquivosExistem){
                    menuBusca();
                    clrscr();
                }
                else {
                    clrscr();
                    printf("ERRO: Arquivo de individuos ou de racas nao existe.\n");
                    printf("Importe os arquivos antes de buscar.\n");
                }
                break;
            case 4:
                break;
            default:
                clrscr();
                printf("ERRO: Opcao invalida\n");
        }
    } while (op != 4);
}

void iniciar(){
    printf("***********************************************\n");
    printf("*               CADASTRO DE CAES              *\n");
    printf("***********************************************\n\n");

    menuPrincipal();
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
    }

    fseek(arquivo, 0, SEEK_END);
    printf("%d\n", ftell(arquivo));*/
    iniciar();

    pressEnter();
    return 0;
}
