#include<stdio.h>
#include<stdlib.h>
#include "../include/avl.h"

int main() {
    Arv arv;
    constroi_avl(&arv);
    
    int num;

    printf("Inserir\n");
    do {
        printf("Valor: ");
        scanf("%d", &num);

        if(num != 0) insere_avl(&arv, num);
    } while(num != 0);

    exibe_avl(&arv);
    
    printf("\n");

    printf("Busca\n");
    do {
        printf("Valor: ");
        scanf("%d", &num);

        if(num != 0) {
            Reg * aux = busca_avl(&arv, num);

            while(aux) {
                printf("item: %d\n", aux->item);
                aux = aux->prox;
            }
        }

        printf("\n");
    } while(num != 0);

    libera_avl(&arv);

    return EXIT_SUCCESS;
}
