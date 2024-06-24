#ifndef __AVLMODMUN__
#define __AVLMODMUN__
#include<stdio.h>
#include<stdlib.h>
typedef struct _reg{
   void * chave;
   int cod_ibge;
   struct _reg * prox;
} Reg;

typedef struct _node {
   Reg * regs;
   int h;
   struct _node * pai;
   struct _node * esq;
   struct _node * dir;
} Node;

typedef struct {
   Node * raiz;
   int (* cmp)(void *, void *);
} ArvAVL;

/* constrói */
void constroi_avl(ArvAVL * arv, int (*cmp)(void *, void *));
/* auxiliares */
int _max(int a, int b);
int _altura(Node * node);
Node ** _sucessor(Node ** node);
Node ** _antecessor(Node ** node);
/* balanceamento */
void _rebalancear(Node ** node);
void _re(Node ** node);
void _rd(Node ** node);
/* inserção */
void insere_avl(ArvAVL * arv, void * chave, int cod_ibge);
void _insere(ArvAVL * arv, Node ** node, Node * pai, void * chave, int cod_ibge);
/* busca */
Reg * busca_avl(ArvAVL * arv, void * chave);
Reg * _busca(ArvAVL * arv, Node * node, void * chave);
/* destrói */
void libera_avl(ArvAVL * arv);
void _libera(Node * node);
/* queries */
int * range_avl(ArvAVL * arv, void * chave, int eq, int tam);
void _salva_ret(int ** pret, Reg * reg);
#endif
