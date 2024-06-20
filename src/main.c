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

        insere_avl(&arv, num);
    } while(num != 0);

    exibe_avl(&arv);
    libera_avl(&arv);

//    printf("Sucessor\n");
//    do {
//        printf("Valor: ").
//        scanf("%d", &num);
//
//        _sucessor(busca_avl(&arv, num));
//    } while(num != 0);

    return EXIT_SUCCESS;
}
