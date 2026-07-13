#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreBinaria.h"

void exibir_menu() {
    printf("\n===== MENU LISTA ENCADEADA =====\n");
    printf("1. Cadastrar aluno \n");
    printf("2. Listar Alunos\n");
    printf("3. Lancar Notas\n");
    printf("4. Lancar Faltas\n");
    printf("5. Calcular Situaçao\n");
    printf("6. Gerar Relatorio\n");
    printf("7. Aluno com a maior meia\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    ArvBin* raiz = cria_ArvBin();
    int opcao, matricula, aulas,bime;
    int mat=1;
    carregararquivo(raiz);
    do {
        exibir_menu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:

                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
    salvararquivo(raiz);
    libera_ArvBin(raiz);
    return 0;
}
