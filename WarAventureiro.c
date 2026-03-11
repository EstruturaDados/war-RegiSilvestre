#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Struct Territorio */
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

/* Exibe todos os territórios */
void exibirTerritorios(struct Territorio *mapa, int total) {
    printf("\n=====================================\n");
    printf("        MAPA DO MUNDO ATUAL\n");
    printf("=====================================\n");
    for(int i = 0; i < total; i++) {
        printf("%d. %s (Exercito: %s, Tropas: %d)\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }
}

/* Simula ataque: transfere 1 tropa do perdedor para o vencedor */
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\n===== FASE DE BATALHA =====\n");
    printf("Atacante (%s) rolou: %d\n", atacante->nome, dadoAtaque);
    printf("Defensor (%s) rolou: %d\n", defensor->nome, dadoDefesa);

    if(dadoAtaque > dadoDefesa) {
        // Atacante vence
        printf("\nVITORIA DO ATACANTE!\n");

        if(defensor->tropas > 0) {
            defensor->tropas--;
            atacante->tropas++;
            printf("O defensor perdeu 1 tropa.\n");
        }

        // Conquista se defensor ficar com 0 tropas
        if(defensor->tropas == 0 && strcmp(defensor->cor, atacante->cor) != 0) {
            strcpy(defensor->cor, atacante->cor);
            printf("%s conquistou o territorio %s!\n",atacante->nome, defensor->nome);
        }

    } else if(dadoAtaque < dadoDefesa) {
        // Defensor vence
        printf("\nVITORIA DO DEFENSOR!\n");

        if(atacante->tropas > 0) {
            atacante->tropas--;
            defensor->tropas++;
            printf("O atacante perdeu 1 tropa.\n");
        }

        // Conquista se atacante ficar com 0 tropas
        if(atacante->tropas == 0 && strcmp(atacante->cor, defensor->cor) != 0) {
            strcpy(atacante->cor, defensor->cor);
            printf("%s conquistou o territorio %s!\n", defensor->nome, atacante->nome);
        }

    } else {
        printf("\nEmpate! Nenhum vencedor nesta batalha.\n");
    }
}

/* Libera memória */
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
}

int main() {
    int totalTerritorios;
    srand(time(NULL));

    printf("=====================================\n");
    printf("  WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("=====================================\n\n");

    printf("Digite o numero de territorios: ");
    scanf("%d", &totalTerritorios);

    if(totalTerritorios <= 0) {
        printf("Numero invalido de territorios.\n");
        return 1;
    }

    struct Territorio *territorios = calloc(totalTerritorios, sizeof(struct Territorio));
    if(territorios == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    /* Cadastro dos territórios */
    for(int i = 0; i < totalTerritorios; i++) {
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);
        printf("Nome do Territorio: ");
        scanf("%s", territorios[i].nome);
        printf("Cor do Exercito: ");
        scanf("%s", territorios[i].cor);
        printf("Numero de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    /* Mostra mapa automaticamente após cadastro */
    printf("\n===== TERRITORIOS CADASTRADOS =====\n");
    exibirTerritorios(territorios, totalTerritorios);

    int opcao;
    do {
        printf("\n=====================================\n");
        printf("               MENU\n");
        printf("=====================================\n");
        printf("1 - Realizar ataque\n");
        printf("0 - Sair do jogo\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                int atacante, defensor;

                /* Mostra mapa antes do ataque */
                exibirTerritorios(territorios, totalTerritorios);

                printf("\nEscolha o territorio ATACANTE: ");
                scanf("%d", &atacante);
                printf("Escolha o territorio DEFENSOR: ");
                scanf("%d", &defensor);

                atacante--;
                defensor--;

                if(atacante < 0 || atacante >= totalTerritorios ||
                   defensor < 0 || defensor >= totalTerritorios) {
                    printf("\nTerritorio invalido.\n");
                }
                else if(strcmp(territorios[atacante].cor, territorios[defensor].cor) == 0) {
                    printf("\nNao é permitido atacar um territorio da mesma cor!\n");
                }
                else if(territorios[atacante].tropas == 0) {
                    printf("\nAtacante nao possui tropas suficientes para atacar!\n");
                }
                else if(territorios[defensor].tropas == 0) {
                    printf("\nDefensor nao possui tropas, escolha outro territorio!\n");
                }
                else {
                    atacar(&territorios[atacante], &territorios[defensor]);

                    /* Mostra mapa automaticamente após o ataque */
                    printf("\n===== MAPA ATUALIZADO =====\n");
                    exibirTerritorios(territorios, totalTerritorios);
                }

                break;
            }
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }

    } while(opcao != 0);

    liberarMemoria(territorios);
    printf("\nMemoria liberada com sucesso.\n");

    return 0;
}