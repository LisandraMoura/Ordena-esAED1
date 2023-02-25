#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 500 // máximo de linhas no arquivo .csv
#define MAX_COLS 5 // número de colunas no arquivo .csv

struct dados {
    int id;
    char nome[50];
    int idade;
    char profissao[50];
};

int ler_csv(char* arquivo, struct dados dados[]) {
    FILE* fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    char linha[1024];
    int i = 0;
    while (fgets(linha, 1024, fp) != NULL) {
        if (i >= MAX_ROWS) {
            printf("Número máximo de linhas excedido.\n");
            break;
        }
        char* token = strtok(linha, ",");
        dados[i].id = atoi(token);
        token = strtok(NULL, ",");
        strcpy(dados[i].nome, token);
        token = strtok(NULL, ",");
        dados[i].idade = atoi(token);
        token = strtok(NULL, ",");
        strcpy(dados[i].profissao, token);
        i++;
    }

    fclose(fp);
    return i;
}

int busca_sequencial(struct dados dados[], int n, int id, struct dados* resultado) {
    int i;
    for (i = 0; i < n; i++) {
        if (dados[i].id == id) {
            *resultado = dados[i];
            return 1;
        }
    }
    return 0;
}

int main() {
    struct dados dados[MAX_ROWS];
    int n = ler_csv("dados500aleatorio.csv", dados);

    int id;
    printf("Insira o ID que deseja procurar: ");
    scanf("%d", &id);

    struct dados resultado;
    if (busca_sequencial(dados, n, id, &resultado)) {
        printf("ID encontrado:\n");
        printf("ID: %d\n", resultado.id);
        printf("Nome: %s\n", resultado.nome);
        printf("Idade: %d\n", resultado.idade);
        printf("Profissao: %s\n", resultado.profissao);
    } else {
        printf("ID não encontrado.\n");
    }

    return 0;
}
