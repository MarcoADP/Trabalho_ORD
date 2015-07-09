#include <stdio.h>
#include <stdlib.h>
#include "operacoes.h"
#include "util.h"
#include "arquivo.h"

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
    int sair;
    bool arqDesuatalizado = false;

    bool arquivosCarregados = carregarIndices();

    if (arquivosCarregados){
        printf("Arquivos de indices carregados com sucesso.\n");
        printf("Nao e necessario importar arquivos.\n");
    }
    else {
        printf("ERRO: Arquivos nao existem ou estao desuatalizados.\n");
        printf("Faca a importacao dos arquivos.\n");
    }
    do {
        printf("\n-----------------------------------------------\n");
        printf("                 MENU PRINCIPAL                \n");
        printf("-----------------------------------------------\n");
        printf("(1) - Importar arquivo\n");
        printf("(2) - Inserir individuo\n");
        printf("(3) - Buscar\n");
        printf("(4) - Salvar dados em arquivo\n");
        printf("(5) - Sair\n");
        op = lerInt("\nDigite sua opcao: ");

        switch(op){
            case 1:
                if (importarArq()){
                    clrscr();
                    printf("Arquivos importados e convertidos com sucesso.\n");
                    arquivosCarregados = true;
                    arqDesuatalizado = true;
                }
                else {
                    clrscr();
                    printf("Importacao cancelada.\n");
                }
                break;
            case 2:
                if (arquivosCarregados){
                    if (inserirIndividuo()){
                        clrscr();
                        printf("Individuo inserido com sucesso.\n");
                        arqDesuatalizado = true;
                    }
                    else {
                        clrscr();
                        printf("Insercao cancelada.\n");
                    }
                }
                else {
                    clrscr();
                    printf("ERRO: Arquivos nao foram importados.\n");
                    printf("Importe os arquivos antes de inserir.\n");
                }
                break;
            case 3:
                if (arquivosCarregados){
                    menuBusca();
                    clrscr();
                }
                else {
                    clrscr();
                    printf("ERRO: Arquivos nao foram importados.\n");
                    printf("Importe os arquivos antes de buscar.\n");
                }
                break;
            case 4:
                if (arquivosCarregados){
                    if (salvarEmArquivo()){
                        clrscr();
                        printf("Arquivos salvos com sucesso.\n");
                        arqDesuatalizado = false;
                    }
                    else {
                        clrscr();
                        printf("ERRO: Nao foi possivel salvar dados em arquivos.\n");
                    }
                }
                else {
                    clrscr();
                    printf("ERRO: Arquivos nao foram importados.\n");
                    printf("Importe os arquivos antes de salvar.\n");
                }
                break;
            case 5:
                if (arqDesuatalizado){
                    clrscr();
                    printf("Deseja sair sem salvar dados em arquivo? SIM(1) - NAO(0): \n");
                    sair = lerInt("");
                    while (sair != 0 && sair != 1){
                        printf("ERRO: Opcao invalida\n\n");
                        sair = lerInt("Informe outro valor: ");
                    }
                }
                else 
                    sair = 1;
                break;
            default:
                clrscr();
                printf("ERRO: Opcao invalida\n");
        }
    } while (sair != 1);
}

void iniciar(){
    printf("***********************************************\n");
    printf("*               CADASTRO DE CAES              *\n");
    printf("***********************************************\n\n");

    menuPrincipal();
}

int main(int argc, char const *argv[]){
    clrscr();
    iniciar();

    pressEnter();
    return 0;
}
