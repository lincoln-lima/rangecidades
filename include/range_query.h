#ifndef __RANGEQUERY__
#define __RANGEQUERY__
#include <stdio.h>
#include <stdlib.h>
#include "./avl.h"
void menu_inicial(int * op);
void menu_escolha(char * label, int * op);
void menu_range(int * eq);
int * query(Arv * arv, int tipo);
int * comb_query(int * regs1, int * regs2, int tam);
#endif
