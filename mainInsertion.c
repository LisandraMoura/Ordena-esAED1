#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct cliente {
    int chave;
    char nome[20];
    char profissao[50];
    int idade;
}clientes;

void insertion_sort(struct cliente clientes[], int tamanho, int *passagens) {
    int i, j, chave;
    struct cliente temp;
    for (i = 1; i < tamanho; i++) {
        chave = clientes[i].chave;
        temp = clientes[i];
        j = i - 1;
        while (j >= 0 && clientes[j].chave > chave) {
            clientes[j + 1] = clientes[j];
            j--;
            (*passagens)++;
        }
        clientes[j + 1] = temp;
    }
}

int main() {
    int tamanho = 0, i;
    clock_t inicio, fim;
    inicio = clock();
    int passagens = 0;
    FILE *arquivoEntrada, *arquivoSaida;
  
//encoding
    arquivoEntrada = fopen( "dados1000aleatorio.csv", "r");
    if (arquivoEntrada == NULL) {
        printf("Nao foi possivel abrir o arquivo de entrada.\n");
        return 1;
    }
    arquivoSaida = fopen("clientes1000InsertionSort.csv", "w");
    if (arquivoSaida == NULL) {
        printf("Nao foi possivel criar o arquivo de saida.\n");
        return 1;
    }

    // Descobrir o tamanho do arquivo
    while (!feof(arquivoEntrada)) {
        if (fgetc(arquivoEntrada) == '\n') {
            tamanho++;
        }
    }

    rewind(arquivoEntrada);
    struct cliente clientes[tamanho];
    // Lê o arquivo e armazena os dados na struct




    char buffer[200];
    //buffer = (char *)malloc(sizeof(char) * 200); 

    //pessoas = (clientes *)malloc(sizeof(Pessoa) * 5000); // aloca dinamicamente memória para o vetor de pessoas
    int n;
    fgets(buffer, 200, arquivoEntrada); //descarta a primeira linha
    //lê o arquivo CSV e armazena as informações na estrutura

    while(fgets(buffer, 200, arquivoEntrada)) {
        sscanf(buffer, "%d;%[^;];%[^;];%d", &clientes[n].chave, clientes[n].nome, clientes[n].profissao, &clientes[n].idade);
        n++;

    }

    fclose(arquivoEntrada);
    // Ordena a lista de clientes com o método insertion sort
    insertion_sort(clientes, tamanho, &passagens);
    // Escreve a lista ordenada no arquivo de saída
    for (i = 0; i < tamanho; i++) {
        fprintf(arquivoSaida, "%d,%s,%s,%d\n", clientes[i].chave, clientes[i].nome, clientes[i].profissao, clientes[i].idade);
        
    }

    fclose(arquivoSaida);
    fim = clock();
    printf("Numero de passagens: %d\n", passagens);
    printf("Tempo de execucao: %lf segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
    return 0;
}