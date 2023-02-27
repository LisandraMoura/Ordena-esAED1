#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 5000 // máximo de linhas no arquivo .csv
#define MAX_COLS 4 // número de colunas no arquivo .csv

struct cliente {
    int id;
    char nome[50];
    char profissao[50];
    int idade;
};

int ler_csv(char* arquivo, struct cliente clientes[]) {
    FILE* fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    char linha[1024];
    int i = 0;
    while (fgets(linha, 1024, fp) != NULL) {
        char* token = strtok(linha, ";");
        int colunas_lidas = 0;
        while (token != NULL && colunas_lidas < MAX_COLS) {
            switch (colunas_lidas) {
                case 0:
                    clientes[i].id = atoi(token);
                    break;
                case 1:
                    strcpy(clientes[i].nome, token);
                    break;
                case 2:
                    strcpy(clientes[i].profissao, token);
                    break;
                case 3:
                    clientes[i].idade = atoi(token);
                    break;
                default:
                    break;
            }
            token = strtok(NULL, ";");
            colunas_lidas++;
        }
        if (colunas_lidas != MAX_COLS) {
            printf("Linha com número de colunas incorreto: %s", linha);
            continue;
        }
        i++;
    }

    fclose(fp);
    return i;
}

int main() {
    struct cliente clientes[MAX_ROWS];
    int n = ler_csv("dados2000decrescente.csv", clientes);

    FILE* fp = fopen("eeeee.csv", "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return 0;
    }

    fprintf(fp, "ID;nome;profissao;idade\n");
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d;%s;%s;%d\n", clientes[i].id, clientes[i].nome, clientes[i].profissao, clientes[i].idade);
    }

    fclose(fp);

    return 0;
}
