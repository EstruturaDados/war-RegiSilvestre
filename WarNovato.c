#include <stdio.h>
#include <string.h>

/*
    Definição da struct Territorio
    Essa estrutura agrupa informações relacionadas a um território
    dentro de um único tipo de dado composto.
*/
struct Territorio {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército que controla o território
    int tropas;      // Quantidade de tropas presentes no território
};

int main() {

    // Vetor para armazenar 5 territórios
    struct Territorio territorios[5];

    int i;

    printf("=====================================\n");
    printf("  WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("=====================================\n\n");
    
    printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n");
    printf("\n");
    /*
        Laço responsável pelo cadastro dos territórios.
        O usuário deverá inserir as informações solicitadas
        para cada território.
    */
    for(i = 0; i < 5; i++) {

        printf("---Cadastrando Territorio %d---\n", i + 1);

        printf("Digite o nome do Territorio: ");
        scanf("%s", territorios[i].nome);

        printf("Digite a cor do Exercito (Ex: Azul, Verde): ");
        scanf("%s", territorios[i].cor);

        printf("Digite a quantidade de Tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    /*
        Após o cadastro, o sistema percorre o vetor
        e exibe todos os territórios registrados.
    */
    printf("\nCadastro inicial concluído com sucesso!\n");

    printf("\n=====================================\n");
    printf("      MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("=====================================\n");

    for(i = 0; i < 5; i++) {

        printf("\nTERRITORIO %d:\n", i + 1);
        printf("- Nome: %s\n", territorios[i].nome);
        printf("- Dominado por: Exercito %s\n", territorios[i].cor);
        printf("- Tropas: %d\n", territorios[i].tropas);

    }

    
    return 0;
}