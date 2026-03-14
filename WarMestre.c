#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ================================
   STRUCT TERRITORIO
================================ */
struct Territorio{
    char nome[30];
    char cor[10];
    int tropas;
};

/* ================================
   EXIBIR MAPA
================================ */
void exibirTerritorios(struct Territorio *mapa, int total){
    printf("\n=========== MAPA ATUAL ===========\n");
    for(int i=0;i<total;i++){
        printf("%d - %s (Cor: %s | Tropas: %d)\n",
               i+1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }
}

/* ================================
   ATRIBUIR MISSÃO
================================ */
void atribuirMissao(char* destino, char* missoes[], int totalMissoes){
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

/* ================================
   EXIBIR MISSÃO
================================ */
void exibirMissao(char *missao){
    printf("\n=========== SUA MISSÃO ===========\n");
    printf("%s\n", missao);
}

/* ================================
   VERIFICAR MISSÃO
================================ */
int verificarMissao(char* missao, struct Territorio* mapa, int total){
    int territoriosJogador = 0;
    int tropasJogador = 0;

    // Contar territórios e tropas da cor "Azul" (jogador)
    for(int i=0;i<total;i++){
        if(strcmp(mapa[i].cor,"Azul")==0){
            territoriosJogador++;
            tropasJogador += mapa[i].tropas;
        }
    }

    // Missão 2 territorios
    if(strstr(missao,"2 territorios") && territoriosJogador >= 2)
        return 1;

    // Missão 3 territorios
    if(strstr(missao,"3 territorios") && territoriosJogador >= 3)
        return 1;

    // Missão 10 tropas
    if(strstr(missao,"10 tropas") && tropasJogador >= 10)
        return 1;

    // Missão qualquer territorio
    if(strstr(missao,"qualquer territorio") && territoriosJogador >= 1)
        return 1;

    return 0;
}

/* ================================
   ATAQUE
================================ */
void atacar(struct Territorio* atacante, struct Territorio* defensor){
    int dadoAtaque = rand()%6 + 1;
    int dadoDefesa = rand()%6 + 1;

    printf("\n=========== BATALHA ===========\n");
    printf("Atacante rolou: %d\n", dadoAtaque);
    printf("Defensor rolou: %d\n", dadoDefesa);

    if(dadoAtaque > dadoDefesa){
        printf("Atacante venceu!\n");

        if(atacante->tropas > 0) atacante->tropas++;
        if(defensor->tropas > 0) defensor->tropas--;

        if(defensor->tropas <= 0){
            printf("Território conquistado!\n");
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 0;
        }
    }
    else if(dadoDefesa > dadoAtaque){
        printf("Defensor venceu!\n");

        if(defensor->tropas > 0) defensor->tropas++;
        if(atacante->tropas > 0) atacante->tropas--;

        if(atacante->tropas <= 0){
            atacante->tropas = 0;
        }
    }
    else{
        printf("Empate! Nenhuma tropa perdida.\n");
    }
}

/* ================================
   LIBERAR MEMÓRIA
================================ */
void liberarMemoria(struct Territorio* mapa, char* missao){
    free(mapa);
    free(missao);
}

/* ================================
   MAIN
================================ */
int main(){
    srand(time(NULL));

    int totalTerritorios;
    printf("======= WAR SIMPLIFICADO =======\n");
    printf("Numero de territorios: ");
    scanf("%d",&totalTerritorios);

    if(totalTerritorios <= 0){
        printf("Numero invalido\n");
        return 1;
    }

    struct Territorio *territorios = calloc(totalTerritorios,sizeof(struct Territorio));
    if(territorios == NULL){
        printf("Erro de memoria\n");
        return 1;
    }

    /* MISSÕES */
    char* missoes[] = {
        "Conquistar 2 territorios",
        "Controlar 3 territorios",
        "Possuir pelo menos 10 tropas",
        "Conquistar qualquer territorio"
    };
    int totalMissoes = 4;
    char *missaoJogador = malloc(200);

    atribuirMissao(missaoJogador,missoes,totalMissoes);
    printf("\nMissao sorteada!\n");
    exibirMissao(missaoJogador);

    /* CADASTRO DOS TERRITÓRIOS */
    for(int i=0;i<totalTerritorios;i++){
        printf("\nTerritorio %d\n",i+1);
        printf("Nome: ");
        scanf("%s",territorios[i].nome);
        printf("Cor do exercito: ");
        scanf("%s",territorios[i].cor);
        printf("Tropas: ");
        scanf("%d",&territorios[i].tropas);
    }

    int opcao;
    do{
        printf("\n=========== MENU ===========\n");
        printf("1 - Atacar\n");
        printf("2 - Ver mapa\n");
        printf("3 - Ver missao\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d",&opcao);

        switch(opcao){
            case 1:{
                int atacante,defensor;
                exibirTerritorios(territorios,totalTerritorios);

                printf("Territorio atacante: ");
                scanf("%d",&atacante);
                printf("Territorio defensor: ");
                scanf("%d",&defensor);

                atacante--;
                defensor--;

                if(atacante < 0 || defensor < 0 ||
                   atacante >= totalTerritorios ||
                   defensor >= totalTerritorios){
                    printf("Territorio invalido\n");
                }
                else if(strcmp(territorios[atacante].cor,
                               territorios[defensor].cor)==0){
                    printf("Nao pode atacar territorio da mesma cor\n");
                }
                else{
                    atacar(&territorios[atacante],
                           &territorios[defensor]);

                    // Mostrar mapa atualizado
                    printf("\n===== MAPA ATUALIZADO =====\n");
                    exibirTerritorios(territorios,totalTerritorios);

                    // Verificar missão
                    if(verificarMissao(missaoJogador,
                                       territorios,
                                       totalTerritorios)){
                        printf("\n===== MISSAO CUMPRIDA! =====\n");
                        printf("Parabens! Voce cumpriu sua missao!\n");
                    }
                }
                break;
            }
            case 2:
                exibirTerritorios(territorios,totalTerritorios);
                break;
            case 3:
                exibirMissao(missaoJogador);
                break;
            case 0:
                printf("Encerrando jogo...\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
    }while(opcao!=0);

    liberarMemoria(territorios,missaoJogador);
    printf("Memoria liberada\n");

    return 0;
}