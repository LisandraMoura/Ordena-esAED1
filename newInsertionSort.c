#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
            printf("Linha com numero de colunas incorreto: %s", linha);
            continue;
        }
        i++;
    }

    fclose(fp);
    return i;
}

void insertion_sort(struct cliente clientes[], int tamanho, int *passagens, int *comparacoes) {
    // Ordenação dos dados usando insertion sort
    for (int i = 1; i < tamanho; i++) {
        struct cliente temp = clientes[i];
        int j = i - 1;
        while (j >= 0 && clientes[j].id > temp.id) {
            clientes[j + 1] = clientes[j];
            j--;
            (*comparacoes)++;
        }
        clientes[j + 1] = temp;
        (*passagens)++;
    }
}

int main() {
    clock_t inicio, fim;
    int passagens;
    int comparacoes;
    struct cliente clientes[MAX_ROWS];
    char nomeArquivo [20];
    char arquivosaida[20];

    printf("Digite o nome do arquivo a ser ordenado: \nEx: 'nome.csv'\n");
    scanf("%s", &nomeArquivo);
    int n = ler_csv(nomeArquivo, clientes);

    inicio = clock();
    insertion_sort(clientes, n, &passagens, &comparacoes);
    fim = clock();

    printf("De um nome para o arquivo de saida: \nEx: 'nome.csv'\n");
    scanf("%s", &arquivosaida);

    FILE* fp = fopen(arquivosaida, "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return 0;
    }

    fprintf(fp, "ID;nome;profissao;idade\n");
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d;%s;%s;%d\n", clientes[i].id, clientes[i].nome, clientes[i].profissao, clientes[i].idade);
    }

    fclose(fp);
    printf("Numero de passagens: %d\n", passagens);
    printf("Numero de comparacoes: %d\n", comparacoes);
    printf("Tempo de execucao: %lf segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

    return 0;
}

