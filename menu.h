#ifndef MENU_H
#define MENU_H

void shellSort(struct cliente *clientes, int n, int *passagens, int *comparacoes);
void swap(struct cliente *a, struct cliente *b);
int partition(struct cliente *clientes, int low, int high);
void quicksort(struct cliente *clientes, int low, int high);
void insertion_sort(struct cliente clientes[], int tamanho, int *passagens);


#endif /* menu_h */
