#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "falhas.h"
#include "ArvoreBinaria.h"

NO_DEC* criarNoDecisao(int id, char *pergunta, int folha){

    NO_DEC *novo;
    novo = (NO_DEC*) malloc(sizeof(NO_DEC));

    if(novo == NULL)
        return NULL;

    novo->id = id;
    strcpy(novo->pergunta, pergunta);
    novo->ehFolha = folha;
    novo->solucao[0] = '\0';
    novo->referencia[0] = '\0';
    novo->sim = NULL;
    novo->nao = NULL;

    return novo;
}

void inserirFilho(NO_DEC *pai, NO_DEC *filho, int respSim){

    if(pai == NULL)
        return;

    if(filho == NULL)
        return;

    if(respSim)
        pai->sim = filho;
    else
        pai->nao = filho;
}

int contarDiagnosticos(NO_DEC *raiz) {
    
    if(raiz == NULL)
    return 0;

    if(raiz->ehFolha)
        return 1;

    return contarDiagnosticos(raiz->sim) + contarDiagnosticos(raiz->nao);
}

int contarPerguntas(NO_DEC *raiz){

    if(raiz == NULL)
    return 0;

    if(raiz->ehFolha)
        return 0;

    return contarPerguntas(raiz->sim) + contarPerguntas(raiz->nao) + 1;
}

void salvarArvoreArquivo(NO_DEC *raiz, FILE *f) {
    if (raiz == NULL) {
        return;
    }

    fprintf(f, "%d", raiz->id);
    fprintf(f, "%s", raiz->pergunta);
    fprintf(f, "%s", raiz->referencia);
    fprintf(f, "%d", raiz->ehFolha);
    fprintf(f, "%s", raiz->solucao);

    salvarArvoreArquivo(raiz->sim, f);
    salvarArvoreArquivo(raiz->nao, f);
}

int calcularProfundidadeMax(NO_DEC *raiz){
    if (raiz == NULL)
        return 0;
    /*if (*raiz == NULL)
        return 0;*/
    int alt_esq = calcularprofundidadeMax(raiz->sim);
    int alt_dir = calcularprofundidadeMax(raiz->nao);

    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

void liberarArvoreDecisao(NO_DEC* raiz){
    if(raiz == NULL)
        return;
    libera_NO(raiz);//libera cada nó
}

void libera_NO( NO_DEC* no){
    if(no == NULL)
        return;
    libera_NO(no->sim);
    libera_NO(no->nao);
    free(no);
    no = NULL;
}

void exibirArvoreCompleta(NO_DEC *raiz, int nivel){

void navegarDiagnostico(NO_DEC *raiz) {
    if(raiz == NULL){
        printf("Árvore vazia.\n");
        return;
    }

    NO_DEC *atual = raiz;
    char resposta;

    while(atual != NULL && !atual->ehFolha){

        printf("\n%s (S/N): ", atual->pergunta);
        scanf(" %c", &resposta);

        resposta = toupper(resposta);

        while(resposta != 'S' && resposta != 'N'){
            printf("Resposta inválida! Digite S ou N: ");
            scanf(" %c", &resposta);
            resposta = toupper(resposta);
        }

        if(resposta == 'S')
            atual = atual->sim;
        else
            atual = atual->nao;
    }

    if(atual == NULL){
        printf("\nDiagnóstico não encontrado.\n");
        return;
    }

    printf("\n=============================\n");
    printf("DIAGNÓSTICO\n");
    printf("=============================\n");
    printf("%s\n", atual->pergunta);

    printf("\nSolução:\n");
    printf("%s\n", atual->solucao);

    printf("\nReferência:\n");
    printf("%s\n", atual->referencia);
}

void exibirArvoreCompleta(NO_DEC *raiz, int nivel) {

void registrarSessao(int idDiagnostico, char *data, FILE *f){

    if(f == NULL)
        return;

    fprintf(f,"%d %s\n", idDiagnostico, data);
}

NO_DEC* carregarArvoreArquivo(FILE *f) {

NO_DEC* buscarPorID(NO_DEC *raiz, int id){

    if(raiz == NULL)
        return NULL;

    if(raiz->id == id)
        return raiz;

    NO_DEC *aux;

    aux = buscarPorID(raiz->sim, id);

    if(aux != NULL)
        return aux;

    return buscarPorID(raiz->nao, id);
}

void registrarSessao(int idDiagnostico, char *data, FILE *f) {

}

NO_DEC* buscarPorID(NO_DEC *raiz, int id) {

}