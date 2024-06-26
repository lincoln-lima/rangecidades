#ifndef __AVLMOD__
#define __AVLMOD__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Tipo;
#define INT 1
#define FLOAT 2
#define STR 3

typedef struct _reg{
   void * chave;
   int cod;
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
   Tipo tipo;
} ArvAVL;

/* constrói */
void constroi_avl(ArvAVL * arv, Tipo tipo);
/* comparação */
int cmp_int(void * a, void * b);
int cmp_float(void * a, void * b);
int cmp_str(void * a, void * b);
/* auxiliares */
int _max(int a, int b);
int _altura(Node * node);
/* sucessor e antecessor */
Node ** _sucessor(Node ** node);
Node ** _antecessor(Node ** node);
/* balanceamento */
void _rebalancear(Node ** node);
void _re(Node ** node);
void _rd(Node ** node);
/* inserção */
void insere_avl(ArvAVL * arv, void * chave, int cod);
void _insere(ArvAVL * arv, Node ** node, Node * pai, void * chave, int cod);
/* busca */
Reg * busca_avl(ArvAVL * arv, void * chave);
Reg * _busca(ArvAVL * arv, Node * node, void * chave);
/* destrói */
void libera_avl(ArvAVL * arv);
void _libera(Node * node);
#endif
