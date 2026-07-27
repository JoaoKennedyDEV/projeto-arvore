#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreBinaria.h"
#include "falhas.h"

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
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    NO_DEC* raiz = NULL;
    int opcao,id,folha;
    char pergunta[200];
    NO_DEC* aux;
    //carregarArvoreArquivo(f);
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

                printf("É folha (diagnóstico)? (1-Sim / 0-Não): ");
                scanf("%d", &folha);

                printf("Pergunta:");
                scanf(" %[^\n]", pergunta);

                criarNoDecisao(id,pergunta,folha);
                break;
            case 4:
                //inserirFilho();
                break;
            case 5:
                printf("Profundidade: %d\n",calcularProfundidadeMax(raiz));
                break;
            case 6:
                printf("Quantidade de diagnósticos: %d\n", contarDiagnosticos(raiz));
                break;
            case 7:
                printf("Quantidade de perguntas: %d\n", contarPerguntas(raiz));
                break;
            case 8:
                printf("Qual ID para buscar: ");
                scanf("%d", &id);
                aux = buscarPorID(raiz,id);
                if (aux == NULL)
                    printf("id não encontrado na árvore.\n", id);
                else
                    printf("Encontrado: id=%d | %s\n", aux->id, aux->pergunta);
                break;
            case 9:
                //registrarSessao(idDiagnostico,data,f);
                break;
            case 10:
                liberarArvoreDecisao(raiz);
                break;
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