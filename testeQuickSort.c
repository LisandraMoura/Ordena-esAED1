#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct cliente {
    int chave;
    char nome[20];
    char profissao[50];
    int idade;
} clientes;

int swaps = 0;

void swap(struct cliente *a, struct cliente *b) {
    swaps++;
    struct cliente temp = *a;
    *a = *b;
    *b = temp;
}

int partition(struct cliente *clientes, int low, int high) {
    int pivot = clientes[high].chave;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (clientes[j].chave < pivot) {
            i++;
            swap(&clientes[i], &clientes[j]);
        }
    }
    swap(&clientes[i + 1], &clientes[high]);
    return (i + 1);
}

void quicksort(struct cliente *clientes, int low, int high) {
    if (low < high) {
        int pi = partition(clientes, low, high);

        quicksort(clientes, low, pi - 1);
        quicksort(clientes, pi + 1, high);
    }
}

int main() {
    int tamanho = 0;
        
    FILE *arquivoSaida, *arquivoEntrada;
 
    //encoding
    arquivoEntrada = fopen("dados1000aleatorio.csv", "r");
    if (arquivoEntrada == NULL) {
        printf("Não foi possível abrir o arquivo de entrada.\n");
        return 1;
    }
    arquivoSaida = fopen("clientesteste1000QuickSort.csv", "w");
    if (arquivoSaida == NULL) {
        printf("Não foi possível criar o arquivo de saída.\n");
        return 1;
    }

    // Descobrir o tamanho do arquivo
    while (!feof(arquivoEntrada)) {
        if (fgetc(arquivoEntrada) == '\n') {
            tamanho++;
        }
    }
    rewind(arquivoEntrada);
    clientes clientes[tamanho];

    //char buffer[200];******************
    char* buffer = (char *) malloc(sizeof(char) * 200); 
    
    int n;

    fgets(buffer, 200, arquivoEntrada); //descarta a primeira linha

    //lê o arquivo CSV e armazena as informações na estrutura
    while(fgets(buffer, 200, arquivoEntrada)) {
        sscanf(buffer, "%d;%[^;];%[^;];%d", &clientes[n].chave, clientes[n].nome, clientes[n].profissao, &clientes[n].idade);
        n++;
    }
    fclose(arquivoEntrada);
    
    // Ordena a lista de clientes com o método insertion sort
    
    int t = sizeof(clientes) / sizeof(clientes[0]);

    clock_t start = clock();
    quicksort(clientes, 0, t - 1);
    clock_t end = clock();

    // Escreve a lista ordenada no arquivo de saída

    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivoSaida, "%d,%s,%s,%d\n", clientes[i].chave, clientes[i].nome, clientes[i].profissao, clientes[i].idade);
        
    }

    fclose(arquivoSaida);

    printf("Trocas realizadas: %d\n", swaps);
    printf("Tempo de execucao: %f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);  

    return 0;
}
