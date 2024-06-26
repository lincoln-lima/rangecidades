#ifndef __RANGEQUERY__
#define __RANGEQUERY__
#include <stdio.h>
#include <stdlib.h>
#include "./avl.h"
typedef int Faixa;
#define IGUAL 0
#define MAIOR 1
#define MENOR -1
#define ENTRE 3
/* funções de menu */
void menu_inicial(int * op);
void menu_escolha(char * label, int * op);
void menu_range(Faixa * eq);
/* funções relativas a query */
int * query(ArvAVL * arv, Faixa eq, int tam);
int * comb_query(int * regs1, int * regs2, int tam);
int * _range(ArvAVL * arv, void * chave, Faixa eq, int tam);
void _salva_ret(int ** pret, Reg * reg);
#endif
