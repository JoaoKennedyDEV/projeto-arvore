#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreBinaria.h"

void exibir_menu() {
    printf("\n===== MENU =====\n");
    printf("1. Criar NO \n");
    printf("2. \n");
    printf("3. \n");
    printf("4. \n");
    printf("5. \n");
    printf("6. \n");
    printf("7. \n");
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
