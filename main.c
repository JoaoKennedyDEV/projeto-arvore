#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "falhas.h"

#define MAX_NOS 100

NO_DEC* todosNos[MAX_NOS];
int totalNos = 0;

void exibir_menu() {
    printf("\n===== MENU =====\n");
    printf("1. Navegar\n");
    printf("2. Exibir arvore\n");
    printf("3. Criar No\n");
    printf("4. Inserir Filho\n");
    printf("5. Mostrar Profundidade\n");
    printf("6. Mostrar Quantitade de Diagnostiscos\n");
    printf("7. Mostrar Quantidade de Perguntas\n");
    printf("8. Bustar por ID\n");
    printf("9. Regiatrar Sessao\n");
    printf("10. Liberar Arvore\n");
    printf("11. Buscar por palavra-chave\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

NO_DEC* buscarNaLista(int id) {
    int i;
    for (i = 0; i < totalNos; i++) {
        if (todosNos[i]->id == id)
            return todosNos[i];
    }
    return NULL;
}

void preencherListaNos(NO_DEC *raiz) {
    if (raiz == NULL)
        return;
    if (totalNos < MAX_NOS)
        todosNos[totalNos++] = raiz;
    preencherListaNos(raiz->sim);
    preencherListaNos(raiz->nao);
}

int main() {
    NO_DEC* raiz = NULL;
    int opcao,id,folha,idPai,idFilho,respSim;
    char pergunta[200],solucao[400],referencia[100],data[50];
    NO_DEC *aux, *novo;

    FILE *fCarga = fopen("arquivo.txt", "r");
    if (fCarga != NULL) {
        raiz = carregarArvoreArquivo(fCarga);
        fclose(fCarga);
        if (raiz != NULL) {
            preencherListaNos(raiz);
            printf("\nÁrvore carregada de 'arquivo.txt' (%d nó(s)).\n", totalNos);
        }
    }

    do {
        exibir_menu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                navegarDiagnostico(raiz);
                break;
            case 2:
                exibirArvoreCompleta(raiz,0);
                break;
            case 3:
                printf("ID:");
                scanf("%d", &id);

                printf("É folha (diagnostico)? (1-Sim / 0-Não): ");
                scanf("%d", &folha);

                printf("Pergunta:");
                scanf(" %[^\n]", pergunta);

                novo = criarNoDecisao(id,pergunta,folha);
                if (folha) {
                    printf("Solução: ");
                    scanf(" %[^\n]", solucao);
                    printf("Referência: ");
                    scanf(" %[^\n]", referencia);
                    strcpy(novo->solucao, solucao);
                    strcpy(novo->referencia, referencia);
                }
                todosNos[totalNos++] = novo;
                if (raiz == NULL) {
                    raiz = novo;
                    printf("\nNó criado e definido como RAIZ da árvore.\n");
                } else {
                    printf("\nNó criado (id %d). Use a opção 4 para encaixá-lo na árvore.\n", id);
                }
                break;
            case 4:
                printf("ID do nó PAI: ");
                scanf("%d", &idPai);
                printf("ID do nó FILHO: ");
                scanf("%d", &idFilho);
                printf("É filho do ramo SIM? (1-Sim / 0-Não): ");
                scanf("%d", &respSim);

                aux = buscarNaLista(idPai);
                novo = buscarNaLista(idFilho);

                if (aux == NULL || novo == NULL) {
                    printf("\nID de pai ou filho não encontrado. Crie os nós primeiro (opção 3).\n");
                    break;
                }

                inserirFilho(aux, novo, respSim);
                printf("\nNó %d inserido como filho (%s) de %d.\n",idFilho, respSim ? "SIM" : "NAO", idPai);
                break;
            case 5:
                printf("Profundidade: %d\n",calcularProfundidadeMax(raiz));
                break;
            case 6:
                printf("Quantidade de diagnosticos: %d\n", contarDiagnosticos(raiz));
                break;
            case 7:
                printf("Quantidade de perguntas: %d\n", contarPerguntas(raiz));
                break;
            case 8:
                printf("Qual ID para buscar: ");
                scanf("%d", &id);
                aux = buscarPorID(raiz,id);
                if (aux == NULL)
                    printf("id não encontrado na arvore!\n", id);
                else
                    printf("Encontrado: id=%d | %s\n", aux->id, aux->pergunta);
                break;
            case 9:
                printf("ID do diagnóstico: ");
                scanf("%d", &id);
                printf("Data (ex: 26/07/2026): ");
                scanf(" %[^\n]", data);

                FILE *fs = fopen("sessoes.txt", "a");
                if (fs == NULL) {
                    printf("\nErro ao abrir arquivo de sessões.\n");
                    break;
                }
                registrarSessao(id, data, fs);
                fclose(fs);
                printf("\nSessão registrada.\n");
                break;
            case 10:
                liberarArvoreDecisao(raiz);
                raiz = NULL;
                totalNos = 0;
                break;
            case 11: {
                char palavra[100];
                printf("Digite a palavra-chave: ");
                scanf(" %[^\n]", palavra);
                buscarPorPalavraChave(raiz, palavra);
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
    FILE *f=fopen("arquivo.txt","w");
    salvarArvoreArquivo(raiz,f);
    fclose(f);
    return 0;
}