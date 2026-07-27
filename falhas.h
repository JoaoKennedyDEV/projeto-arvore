#ifndef FALHAS_H
#define FALHAS_H

#include <stdio.h>

typedef struct NO_DEC {
    int id;
    char pergunta[200];
    int ehFolha;
    char solucao[400];
    char referencia[100];
    struct NO_DEC *sim;
    struct NO_DEC *nao;
} NO_DEC;

typedef struct {
    NO_DEC *no;
    int profundidade;
} Estado;

NO_DEC* criarNoDecisao(int id, char *pergunta, int folha);

void inserirFilho(NO_DEC *pai, NO_DEC *filho, int respSim);
int contarDiagnosticos(NO_DEC *raiz);
int contarPerguntas(NO_DEC *raiz);
void navegarDiagnostico(NO_DEC *raiz);
void exibirArvoreCompleta(NO_DEC *raiz, int nivel);
int calcularProfundidadeMax(NO_DEC *raiz);
NO_DEC* buscarPorID(NO_DEC *raiz, int id);
void buscarPorPalavraChave(NO_DEC *raiz, char *palavra);

void salvarArvoreArquivo(NO_DEC *raiz, FILE *f);
NO_DEC* carregarArvoreArquivo(FILE *f);
void registrarSessao(int idDiagnostico, char *data, FILE *f);

void liberarArvoreDecisao(NO_DEC *raiz);
void libera_NO( NO_DEC* no);

#endif