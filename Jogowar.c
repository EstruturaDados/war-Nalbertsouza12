#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5

struct territorio {
char nome [30]
char cor [10]
int tropas;
};

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();

void cadastrarTerritorios(struct Territorio *mapa, int total) {

 printf("\n=== Cadastro de Territorios ===\n");


    for (int i = 0; i < total; i++) {

        printf("\nTerritorio %d\n", i + 1);

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
