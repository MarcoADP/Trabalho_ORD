#include <stdio.h>
#include <stdlib.h>
#include "operacoes.h"
#include "util.h"
#include "arquivos.h"

void printaIndividuo(CampoRetorno retorno){
    if (retorno.tam == 0){
        printf("Nenhum resultado encontrado.\n");
        return;
    }
    int i;
    printf("RESULTADO DA BUSCA:\n");
    for (i = 0; i < retorno.tam; i++){
        printf("\nID-I: %s\n", retorno.campo[i][0]);
        printf("ID-R: %s\n", retorno.campo[i][1]);
        printf("NOME: %s\n", retorno.campo[i][2]);
        printf("SEXO: %s\n", retorno.campo[i][3]);
    }
}

void printaRaca(CampoRetorno retorno){
    if (retorno.tam == 0){
        printf("Nenhum resultado encontrado.\n");
        return;
    }
    int i;
    printf("RESULTADO DA BUSCA:\n");
    for (i = 0; i < retorno.tam; i++){
        printf("\nID-R: %s\n", retorno.campo[i][0]);
        printf("RACA: %s\n", retorno.campo[i][1]);
        printf("ID-G: %s\n", retorno.campo[i][2]);
        printf("GRUPO: %s\n", retorno.campo[i][3]);
    }
}

void menuBusca(){
    FILE* arquivo;
    CampoRetorno retorno;
    int op, posicao;
    char sexo[2];
    sexo[1] = '\0';
    clrscr();
    do {
        retorno.tam = 0;
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
                posicao = recuperaPosicaoID(ip3, "Digite o ID do INDIVIDUO ou 0 para cancelar: ");
                if (posicao < 0){
                    clrscr();
                    printf("Busca cancelada.\n");
                }
                else {
                    arquivo = abrirArquivo(NOME_ARQ_IND, "r");
                    buscaID(ip3, posicao, arquivo, &retorno, NULL);
                    fclose(arquivo);
                    clrscr();
                    printaIndividuo(retorno);
                }
                break;
            case 2:
                posicao = recuperaPosicaoID(ip1, "Digite o ID da RACA ou 0 para cancelar: ");
                if (posicao < 0){
                    clrscr();
                    printf("Busca cancelada.\n");
                }
                else {
                    arquivo = abrirArquivo(NOME_ARQ_RACAS, "r");
                    buscaID(ip1, posicao, arquivo, &retorno, NULL);
                    fclose(arquivo);
                    clrscr();
                    printaRaca(retorno);
                }
                break;
            case 3:
                posicao = recuperaPosicaoID(is2, "Digite o ID do GRUPO ou 0 para cancelar: ");
                if (posicao < 0){
                    clrscr();
                    printf("Busca cancelada.\n");
                }
                else {
                    arquivo = abrirArquivo(NOME_ARQ_RACAS, "r");
                    retorno = buscaLista(is2, posicao, listaIS2, ip1, arquivo, NULL);
                    fclose(arquivo);
                    clrscr();
                    printaRaca(retorno);
                }
                break;
            case 4:
                posicao = recuperaPosicaoID(ip1, "Digite o ID da RACA ou 0 para cancelar: ");
                if (posicao < 0){
                    clrscr();
                    printf("Busca cancelada.\n");
                }
                else {
                    arquivo = abrirArquivo(NOME_ARQ_IND, "r");
                    retorno = buscaLista(ip1, posicao, listaIP1, ip3, arquivo, NULL);
                    fclose(arquivo);
                    clrscr();
                    printaIndividuo(retorno);
                }
                break;
            case 5:
                posicao = recuperaPosicaoID(ip1, "Digite o ID da RACA ou 0 para cancelar: ");
                if (posicao < 0){
                    clrscr();
                    printf("Busca cancelada.\n");
                }
                else {
                    sexo[0] = lerSexo();
                    if (sexo[0] == '0'){
                        clrscr();
                        printf("Busca cancelada.\n");
                        break;
                    }
                    arquivo = abrirArquivo(NOME_ARQ_IND, "r");
                    retorno = buscaLista(ip1, posicao, listaIP1, ip3, arquivo, sexo);
                    fclose(arquivo);
                    clrscr();
                    printaIndividuo(retorno);
                }
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
    iniciar();

    pressEnter();
    return 0;
}
