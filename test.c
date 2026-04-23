#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void cadastrarTerritorios(struct Territorio *mapa, int total) {
    printf("\n=== Cadastro de Territorios ===\n");

    for (int i = 0; i < total; i++) {
        printf("\n--- Territorio %d ---\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exercito: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }
}

void exibirTerritorios(struct Territorio *mapa, int total) {
    printf("\n=== MAPA DO MUNDO ===\n");

    for (int i = 0; i < total; i++) {
        printf("\n--------------------------\n");
        printf("Territorio %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Exercito: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
    printf("\n--------------------------\n");
}

void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n=== BATALHA INICIADA ===\n");
    printf("Atacante (%s) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s) rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\n🏆 VENCEDOR: %s\n", atacante->nome);
        printf("💀 PERDEDOR: %s\n", defensor->nome);

        strcpy(defensor->cor, atacante->cor);

        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

    } else {
        printf("\n🏆 VENCEDOR: %s\n", defensor->nome);
        printf("💀 PERDEDOR: %s\n", atacante->nome);

        atacante->tropas--;

        if (atacante->tropas < 1)
            atacante->tropas = 1;
    }

    printf("\n--- ESTADO FINAL ---\n");
    printf("%s: %d tropas\n", atacante->nome, atacante->tropas);
    printf("%s: %d tropas\n", defensor->nome, defensor->tropas);

    pausar();
}

int main() {
    srand(time(NULL));

    int total = MAX_TERRITORIOS;

    struct Territorio *mapa = (struct Territorio *)calloc(total, sizeof(struct Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria\n");
        return 1;
    }

    cadastrarTerritorios(mapa, total);

    int opcao;

    do {
        printf("\n===== WAR =====\n");
        printf("1 - Mostrar mapa\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida!\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();

        switch (opcao) {
            case 1:
                exibirTerritorios(mapa, total);
                pausar();
                break;

            case 2: {
                int atacante, defensor;  // ← AQUI: nomes alterados

                exibirTerritorios(mapa, total);

                printf("\nEscolha atacante (1 a %d): ", total);
                scanf("%d", &atacante);

                printf("Escolha defensor (1 a %d): ", total);
                scanf("%d", &defensor);
                getchar();

                if (atacante > 0 && atacante <= total && defensor > 0 && defensor <= total && atacante != defensor) {
                    atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
                } else {
                    printf("\nEscolha invalida!\n");
                    pausar();
                }
                break;
            }

            case 0:
                printf("\nEncerrando jogo...\n");
                break;

            default:
                printf("Opcao invalida\n");
                pausar();
        }

    } while (opcao != 0);

    free(mapa);

    return 0;
}