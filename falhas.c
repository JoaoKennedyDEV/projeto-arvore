#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "falhas.h"

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
        fprintf(f, "-1\n");
        return;
    }

    fprintf(f, "%d\n", raiz->id);
    fprintf(f, "%s\n", raiz->pergunta);
    fprintf(f, "%s\n", raiz->referencia);
    fprintf(f, "%d\n", raiz->ehFolha);
    fprintf(f, "%s\n", raiz->solucao);

    salvarArvoreArquivo(raiz->sim, f);
    salvarArvoreArquivo(raiz->nao, f);
}

int calcularProfundidadeMax(NO_DEC *raiz){
    if (raiz == NULL)
        return 0;

    int alt_esq = calcularProfundidadeMax(raiz->sim);
    int alt_dir = calcularProfundidadeMax(raiz->nao);

    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

void liberarArvoreDecisao(NO_DEC* raiz){
    if(raiz == NULL)
        return;
    libera_NO(raiz);
}

void libera_NO( NO_DEC* no){
    if(no == NULL)
        return;
    libera_NO(no->sim);
    libera_NO(no->nao);
    free(no);
    no = NULL;
}

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

void exibirArvoreCompleta(NO_DEC *raiz, int nivel){
    int i;

    if(raiz == NULL)
        return;

    for(i=0; i<nivel; i++)
        printf("   ");

    printf("%d - %s\n", raiz->id, raiz->pergunta);

    if (raiz->ehFolha) {
        for(i=0; i<nivel+1; i++)
            printf("   ");
        printf("[Solução: %s | Referência: %s]\n", raiz->solucao, raiz->referencia);
    }

    exibirArvoreCompleta(raiz->sim, nivel + 1);

    exibirArvoreCompleta(raiz->nao, nivel + 1);
}

void registrarSessao(int idDiagnostico, char *data, FILE *f){

    if(f == NULL)
        return;

    fprintf(f,"%d %s\n", idDiagnostico, data);
}

NO_DEC* carregarArvoreArquivo(FILE *f) {
    char linhaId[20];
    char pergunta[200], referencia[100], solucao[400];
    int id, ehFolha;
    NO_DEC *no;

    if (f == NULL)
        return NULL;

    if (fgets(linhaId, sizeof(linhaId), f) == NULL)
        return NULL;

    id = atoi(linhaId);
    if (id == -1)
        return NULL;

    if (fgets(pergunta, sizeof(pergunta), f) == NULL) return NULL;
    pergunta[strcspn(pergunta, "\n")] = '\0';

    if (fgets(referencia, sizeof(referencia), f) == NULL) return NULL;
    referencia[strcspn(referencia, "\n")] = '\0';

    if (fgets(linhaId, sizeof(linhaId), f) == NULL) return NULL;
    ehFolha = atoi(linhaId);

    if (fgets(solucao, sizeof(solucao), f) == NULL) return NULL;
    solucao[strcspn(solucao, "\n")] = '\0';

    no = criarNoDecisao(id, pergunta, ehFolha);
    if (no == NULL)
        return NULL;

    strcpy(no->referencia, referencia);
    strcpy(no->solucao, solucao);

    no->sim = carregarArvoreArquivo(f);
    no->nao = carregarArvoreArquivo(f);

    return no;
}

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

//Funcao extra
void buscarPorPalavraChave(NO_DEC *raiz, char *palavra){

    if(raiz == NULL)
        return;

    if(strstr(raiz->pergunta, palavra) != NULL)
        printf("Encontrado -> id=%d | %s\n", raiz->id, raiz->pergunta);

    buscarPorPalavraChave(raiz->sim, palavra);
    buscarPorPalavraChave(raiz->nao, palavra);
}