#include "falhas.h"
#include <stdlib.h>
#include <stdio.h>
#include "ArvoreBinaria.h"

NO_DEC* criarNoDecisao(int id, char *pergunta, int folha) {
    NO_DEC* raiz = (NO_DEC*) malloc(sizeof(NO_DEC));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void inserirFilho(NO_DEC *pai, NO_DEC *filho, int respSim){}
void navegarDiagnostico(NO_DEC *raiz){}
void exibirArvoreCompleta(NO_DEC *raiz, int nivel){}
int contarDiagnosticos(NO_DEC *raiz) {
    if(raiz == NULL)
        return 0;
    if((*raiz) == NULL)
        return 0;
    if ((*raiz).sim==NULL && (*raiz).nao==NULL)
        return 1;

    return contarDiagnosticos((*raiz).sim) + contarDiagnosticos((*raiz).nao);
}
int contarPerguntas(NO_DEC *raiz){}
void salvarArvoreArquivo(NO_DEC *raiz, FILE *f){}
NO_DEC* carregarArvoreArquivo(FILE *f){}
void registrarSessao(int idDiagnostico, char *data, FILE *f){}