#include "rangequery.h"

/* funções de menu */
void menu_escolha(char * label, int * op) { //menu de decisão se campo será incluso ao query
   printf("%s:\n[0] não\n[1] sim\n", label);
   printf("\n--> ");
   scanf("%d", op);

   *op = (*op == 1) ? *op : 0;

   printf("\n");
}

void menu_range(Faixa * eq) { //menu para determinar tipo de faixa desejada
   printf("Intervalo:");
   printf("\n[0] igual a(=)\n[1] maior que(>)\n[2] menor que(<)\n[3] entre(< >)\n");
   printf("\n--> ");
   scanf("%d", eq);

   *eq = (*eq == 2) ? MENOR : *eq;

   printf("\n");
}

/* funções relativas a query */
int * query(ArvAVL * arv, Faixa eq, int tam) {
   int * ret;

   void * campo1 = malloc(sizeof(void *));
   void * campo2 = NULL;

   printf("Chave: ");
   if(eq == ENTRE) { //novo campo será alocado para realizar duas queries
      printf("\b\bs\n");
      printf("--> mínimo: ");
      campo2 = malloc(sizeof(void *));
   }

   switch(arv->tipo) { //leitura mediante ao tipo de chave da árvore
      case INT:
         scanf("%d", (int *) campo1);

         if(eq == ENTRE) {
            printf("--> máximo: ");
            scanf("%d", (int *) campo2);
         }
         break;
      case FLOAT:
         scanf("%f", (float *) campo1);

         if(eq == ENTRE) {
            printf("--> máximo: ");
            scanf("%f", (float *) campo2);
         }
         break;
      case STR:
         scanf(" %[^\n]", (char *) campo1);
         break;
      default:
         printf("Tipagem inválida\n");
   }

   /* retorno mediante ao tipo de faixa */
   if(campo2) ret = comb_query(_range(arv, campo1, MAIOR, tam),_range(arv, campo2, MENOR, tam),tam);
   else ret = _range(arv, campo1, eq, tam);

   free(campo1);
   free(campo2);

   printf("\n");

   return ret;
}

/* interseção de duas query  */
int * comb_query(int * regs1, int * regs2, int tam) {
   int * ret = NULL;

   if(regs1 && regs2) { //em caso de que ao menos um é nulo, sua interseção é vazia
      ret = (int *) calloc(tam+1, sizeof(int));
      int * pret = ret;

      /* percorre todos os valores de ambos arrays e define interseção  */
      for(int * aux1 = regs1; aux1 < regs1 + tam && *aux1 != 0; aux1++) {
         int * aux2;
         for(aux2 = regs2; aux2 < regs2 + tam && *aux2 != 0 && *aux1 != *aux2; aux2++); 

         if(*aux1 == *aux2) *pret++ = *aux1; //valores iguais serão adicionados ao retorno
      }

      if(!*ret) { //em caso de interseção vazia libera retorno
         free(ret);
         ret = NULL;
      }
   }

   return ret;
}

int * _range(ArvAVL * arv, void * chave, Faixa eq, int tam) {
   int * ret = (int *) calloc(tam+1, sizeof(int)); //vetor de inteiro para retorno com fim zero
   int * pret = ret; //ponteiro para atribuição nos campos do vetor
   int cmp;

   Node * aux = arv->raiz;
   Reg * reg;

   switch(eq) {
      case MAIOR: //registros com chaves maiores que a chave de busca
         while(aux->dir) aux = aux->dir;

         do {
            cmp = arv->cmp(chave, aux->regs->chave);

            if(cmp < 0) {
               reg = aux->regs;

               _salva_ret(&pret, reg); //adição do valor ao retorno

               aux = *(_antecessor(&aux)); //retoma antecessor para buscar valores maiores
            }
         } while(aux && cmp < 0); 
         break;
      case MENOR: //registros com chaves menores que a chave de busca
         while(aux->esq) aux = aux->esq;

         do {
            cmp = arv->cmp(chave, aux->regs->chave);

            if(cmp > 0) {
               reg = aux->regs;

               _salva_ret(&pret, reg); //adição do valor ao retorno

               aux = *(_sucessor(&aux)); //retoma antecessor para buscar valores maiores
            }
         } while(aux && cmp > 0); 
         break;
      case IGUAL: //registros com chaves iguais à chave de busca 
         reg = busca_avl(arv, chave); //busca simples em caso de faixa igual
         _salva_ret(&pret, reg);
         break;
      default:
         printf("!!!INVÁLIDA!!!\n");
   }

   if(!*ret) { //em caso de vazio libera retorno
      free(ret);
      ret = NULL;
   }

   return ret;
}

void _salva_ret(int ** pret, Reg * reg) {
   while(reg) { //iteração da lista
      *(*pret)++ = reg->cod; //iteração do vetor de retorno
      reg = reg->prox;
   } 
}
