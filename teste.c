#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct cliente {
    int chave;
    char nome[20];
    char profissao[50];
    int idade;
} clientes;

void shellSort(clientes meusClientes[], int n, int *passagens, int *comparacoes) {
    int gap, i, j;
    clientes temp;
    for (gap = n/2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            (*comparacoes) ++;
            for (j = i-gap; j >= 0 && meusClientes[j].chave > meusClientes[j+gap].chave; j -= gap) {
                temp = meusClientes[j];
                meusClientes[j] = meusClientes[j+gap];
                meusClientes[j+gap] = temp;
                (*passagens)++;
            }
        }
    }
}

int main() {
    clock_t timetotal = clock();
    int n = 1000, cont = 0;
    int passagens = 0;
    int comparacoes = 0;
    int resposta = 0;
    char nomeArquivo [20];
    //char buffer [200];

    clientes meusClientes[n];

    // ler arquivo csv desordenado

    printf("Digite o nome do arquivo a ser ordenado: \nEx: 'nome.csv'");
    //scanf("%s", &nomeArquivo);

    FILE *arq = fopen(nomeArquivo, "r");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    int coluna, linha;
    char buffer[200];
    char trans_Arq[1024];

    while(fgets(buffer,  50, arq) != NULL) {
        coluna = 0;
        if(linha != 0) {
            // Separador dos campos do csv
            char *campo = strtok(buffer, ";");

            while(campo) {
                if(coluna == 0) { // int
                    strcpy(trans_Arq, campo);
                    meusClientes[linha - 1].chave = atoi(trans_Arq);
                }
                if(coluna == 1) { //char
                    strcpy(trans_Arq, campo);
                    strcpy(meusClientes[linha - 1].nome, trans_Arq);
                }
                if(coluna == 2) { // char
                    strcpy(trans_Arq, campo);
                    strcpy(meusClientes[linha - 1].profissao, trans_Arq);
                }
                if(coluna == 3) { // int
                    strcpy(trans_Arq, campo);
                    meusClientes[linha - 1].idade = atoi(trans_Arq);
                }
                campo = strtok(NULL, ";");
                coluna++;
            }
        } linha++;
    }
    /* FILE *arquivoSaida = fopen("meusClientes1000InsertionSort.csv", "w");
    if (arquivoSaida == NULL) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }
    */

  /* char linha[5000], *campo;
    while (fgets(linha, 5000, arq)) {
        campo = strtok(linha, ";");
        clientes[cont].chave = atoi(campo);
        campo = strtok(NULL, ";");
        strcpy(clientes[cont].nome, campo);
        campo = strtok(NULL, ";");
        strcpy(clientes[cont].profissao, campo);
        campo = strtok(NULL, ";");
        clientes[cont].idade = atoi(campo);
        cont++;
    }
*/ 
        // ordenar com shell sort
    clock_t start_time = clock();
    shellSort(meusClientes, n, &passagens, &comparacoes);
    clock_t end_time = clock();
    fclose(arq);



    double tempo = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("\n************\n");
    printf("Tempo de execucao: %f segundos\n", tempo);
    printf("Numero de passagens: %d\n", passagens);
    printf("Numero de comparacoes : %d\n", comparacoes);
    printf("\n-----------------------------------\n");


    // escrever arquivo csv ordenado
    printf("Caso queria, digite 1 para ver a lista ordenada.\n");
    scanf("%d", &resposta);
    if(resposta==1){
        for (int i = 0; i < n; i++) {
            printf("%d, %s, %s, %d\n", meusClientes[i].chave, meusClientes[i].nome, meusClientes[i].profissao, meusClientes[i].idade);
        }
    }
    else {
        printf("Numero incorreto.\n");
    }



    clock_t timeEndTotal = clock();
    double tempo2 = (double)(timeEndTotal - timetotal) / CLOCKS_PER_SEC;
    printf("Esse foi o tempo total da execussao do algoritmo: %d.\n", tempo2);
    
    return 0;
}