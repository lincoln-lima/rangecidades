#include "../include/range_query.h"

/* funções de menu */
void menu_inicial(int * op) {
   printf("----------------------------------------------------\n");
   printf("INFORME\n");
   printf("Busca de munícipios por queries\n");
   printf("0 - Encerrar\n");
   printf("1 - Realizar\n");
   printf("\nOpção: ");
   scanf("%d", op);
}

void menu_escolha(char * label, int * op) {
   printf("%s\n(0) - não (1) - sim\n: ", label);
   scanf("%d", op);

   *op = (*op == 1) ? *op : 0;
}

void menu_range(int * eq) {
   printf("\n0 - Igual\n1 - Maior\n2 - Menor\n\n");
   scanf("%d", eq);

   *eq = (*eq == 2) ? -1 : *eq;
}

/* funções relativas a query */
int * query(Arv * arv, int tipo) {
   void * campo;
   printf("Chave: ");

   int eq;
   switch(tipo) {
      case INT:
         scanf("%d", (int *) campo);
         menu_range(&eq);
         break;
      case FLOAT:
         scanf("%f", (float *) campo);
         menu_range(&eq);
         break;
      case STR:
         scanf(" %[^\n]", (char *) campo);
         eq = 0;
         break;
      default:
         printf("Tipo inválido\n");
   }

   return range_avl(arv, campo, eq, QTD_MUNICIPIOS);
}

int * comb_query(int * regs1, int * regs2, int tam) {
   int * ret = NULL;

   if(regs1 && regs2) {
      ret = (int *) calloc(tam+1, sizeof(int));
      int * pret = ret;

      /* percorre todos os valores de ambos arrays e define interseção  */
      for(int * aux1 = regs1; aux1 < regs1 + tam && *aux1 != 0; aux1++) {
         int * aux2;
         for(aux2 = regs2; aux2 < regs2 + tam && *aux2 != 0 && *aux1 != *aux2; aux2++); 

         if(*aux1 == *aux2) *pret++ = *aux1;
      }

      /* desalocação de arrays originais */
      free(regs1);
      free(regs2);
   }

   return ret;
}
