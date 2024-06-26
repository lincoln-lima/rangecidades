#include "../include/avl.h"

/* constrói */
void constroi_avl(ArvAVL * arv, int (* cmp)(void *, void *), Tipo tipo) {
   arv->raiz = NULL;
   arv->cmp = cmp; //passagem da função de comparação para chave específica
   arv->tipo = tipo;
}

/* auxiliares */
int _max(int a, int b) {
   return (a > b) ? a : b;
}

int _altura(Node * node) {
   return (node) ? node->h : -1;
}

Node ** _sucessor(Node ** node) {
   Node ** temp = NULL;

   if(*node) {
      Node ** aux = node;

      if((*aux)->dir) { // possui filho à direita
         temp = &(*aux)->dir;

         while((*temp)->esq) temp = &(*temp)->esq;
      }
      else { // não possui filho à direita
         temp = &(*aux)->pai;

         while(*temp && *aux == (*temp)->dir) { // encontra sucessor sem comparar chave
            aux = &(*temp);
            temp = &(*temp)->pai;
         } 
      }
   }

   return temp;
}

Node ** _antecessor(Node ** node) {
   Node ** temp = NULL;

   if(*node) {
      Node ** aux = node;

      if((*aux)->esq) { // possui filho à esquerda 
         temp = &(*aux)->esq;

         while((*temp)->dir) temp = &(*temp)->dir;
      }
      else { // não possui filho à esquerda
         temp = &(*aux)->pai;

         while(*temp && *aux == (*temp)->esq) { // encontra antecessor sem comparar chave
            aux = &(*temp);
            temp = &(*temp)->pai;
         } 
      }
   }

   return temp;
}

/* balanceamento */
void _rebalancear(Node ** node) {
   int fb = _altura((*node)->esq) - _altura((*node)->dir);

   if(fb == -2 || fb == 2) {
      Node * filho = (fb == -2) ? (*node)->dir : (*node)->esq; 

      int fbf = _altura(filho->esq) - _altura(filho->dir);

      if(fb == -2) {
         if(fbf > 0) _rd(&(*node)->dir);
         _re(node);
      }
      else if (fb == 2) {
         if(fbf < 0) _re(&(*node)->esq);
         _rd(node);
      }
   }
}

void _re(Node ** node) {
   Node * x = *node; 
   Node * y = x->dir;
   Node * A = x->esq;
   Node * B = y->esq;
   Node * C = y->dir;

   x->dir = B;
   y->esq = x;
   *node  = y;

   /* reordenando os pais  */
   y->pai = x->pai;
   x->pai = y;
   if(B) B->pai = x;

   x->h = _max(_altura(A),_altura(B)) + 1;
   y->h = _max(_altura(x),_altura(C)) + 1;
}

void _rd(Node ** node) {
   Node * y = *node; 
   Node * x = y->esq;
   Node * A = x->esq;
   Node * B = x->dir;
   Node * C = y->dir;

   y->esq = B; 
   x->dir = y;
   *node  = x;

   /* reordenando os pais  */
   x->pai = y->pai;
   y->pai = x;
   if(B) B->pai = y;

   x->h = _max(_altura(A),_altura(y)) + 1;
   y->h = _max(_altura(B),_altura(C)) + 1;
}

/* inserção */
void insere_avl(ArvAVL * arv, void * chave, int cod_ibge) {
   _insere(arv, &arv->raiz, NULL, chave, cod_ibge); //inserção com pai inicialmente nulo
}

void _insere(ArvAVL * arv, Node ** node, Node * pai, void * chave, int cod_ibge) {
   if(!*node) {
      *node = (Node *) malloc(sizeof(Node));
      (*node)->esq = NULL;
      (*node)->dir = NULL;
      (*node)->pai = pai;
      (*node)->h = 0;

      /* alocação da lista de registros do novo node */
      (*node)->regs = (Reg *) malloc(sizeof(Reg));
      (*node)->regs->chave = chave; 
      (*node)->regs->cod_ibge = cod_ibge;
      (*node)->regs->prox = NULL; 
   }
   else {
      int cmp = arv->cmp(chave, (*node)->regs->chave);

      if(cmp > 0) _insere(arv, &(*node)->dir, *node, chave, cod_ibge);
      else if(cmp < 0) _insere(arv, &(*node)->esq, *node, chave, cod_ibge);
      else {
         Reg * aux = (Reg *) malloc(sizeof(Reg));

         aux->chave = chave;
         aux->cod_ibge = cod_ibge;
         aux->prox = (*node)->regs;
         // inserção ao início da lista ligada
         (*node)->regs = aux;
      }
   }

   (*node)->h = _max(_altura((*node)->dir), _altura((*node)->esq)) + 1;
   _rebalancear(node);
}

/* busca */
Reg * busca_avl(ArvAVL * arv, void * chave) {
   return _busca(arv, arv->raiz, chave);
}

Reg * _busca(ArvAVL * arv, Node * node, void * chave) {
   if(node) {
      int cmp = arv->cmp(chave, node->regs->chave);

      if(cmp > 0) _busca(arv, node->dir, chave);
      else if(cmp < 0) _busca(arv, node->esq, chave);
      else return node->regs;
   }
   else return NULL;
}

/* destrói */
void libera_avl(ArvAVL * arv) {
   _libera(arv->raiz);
}

void _libera(Node * node) {
   if(node) {
      _libera(node->esq);
      _libera(node->dir);

      while(node->regs) {
         Reg * aux = node->regs;
         node->regs = node->regs->prox;
         free(aux); //liberação registro a registro
      }

      free(node);
   }
}
