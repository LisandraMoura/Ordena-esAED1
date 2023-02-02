#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct cliente {
    int chave;
    char nome[20];
    char profissao[50];
    int idade;
};

//funcao de ordenacao
void shellSort(struct cliente *clientes, int n, int *passagens, int *comparacoes) {
    int gap, i, j;
    struct cliente temp;
    for (gap = n/2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            (*comparacoes) ++;
            for (j = i-gap; j >= 0 && clientes[j].chave > clientes[j+gap].chave; j -= gap) {
                temp = clientes[j];
                clientes[j] = clientes[j+gap];
                clientes[j+gap] = temp;
                (*passagens)++;
            }
        }
    }
}

int main() {
    clock_t timetotal = clock();
    int n = 5000, cont = 0;
    int passagens = 0;
    int comparacoes = 0;
    int resposta = 0;
    char nomeArquivo [20];
    char arquivosaida[20];
    char buffer [200];
    struct cliente clientes[n];



    //pega o nome do arquivo
    printf("Digite o nome do arquivo a ser ordenado: \nEx: 'nome.csv'");
    scanf("%s", &nomeArquivo);

    // le arquivo
    FILE *arq = fopen(nomeArquivo, "r");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }


    while(fgets(buffer, 200, arq) != NULL){
        sscanf(buffer, "%d,%[^,],%[^,],%d\n", &clientes[cont].chave, clientes[cont].nome, clientes[cont].profissao, &clientes[cont].idade);
        cont ++;
    }
    fclose(arq);
    //executa shell sort
    clock_t start_time = clock();
    shellSort(clientes, n, &passagens, &comparacoes);
    clock_t end_time = clock();


    //prints

    double tempo = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("\n**********************************\n");
    printf("Tempo de execucao: %f segundos\n", tempo);
    printf("Numero de passagens: %d\n", passagens);
    printf("Numero de comparacoes : %d\n", comparacoes);
    printf("\n-----------------------------------\n");


    // escrever no arquivo a struct ordenada
    printf("De um nome para o arquivo de saida: \nEx: 'nome.csv'");
    scanf("%s", &arquivosaida);

    FILE *new = fopen(arquivosaida, "w");
    if (new == NULL) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }
    for (int i = 0; i < n; i++){
        fprintf(new, "%d,%s,%s,%d\n", clientes[i].chave, clientes[i].nome, clientes[i].profissao, clientes[i].idade);
    }
    fclose(new);
    

    clock_t timeEndTotal = clock();
    double tempo2 = (double)(timeEndTotal - timetotal) / CLOCKS_PER_SEC;
    printf("Tempo total de execussao : %d.\n", tempo2);
    return 0;
}


