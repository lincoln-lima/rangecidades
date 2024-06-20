#ifndef __AVLMOD__
#define __AVLMOD__
#include<stdio.h>
#include<stdlib.h>
typedef struct _reg{
    int item;
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
} Arv;

/* constrói */
void constroi_avl(Arv * arv);
/* auxiliares */
int _max(int a, int b);
int _altura(Node * node);
Node ** _sucessor(Node ** node);
/* balanceamento */
void _rebalancear(Node ** node);
void _re(Node ** node);
void _rd(Node ** node);
/* inserção */
void insere_avl(Arv * arv, int reg);
void _insere(Node ** node, Node * pai, int reg);
/* busca */
Reg * busca_avl(Arv * arv, int reg);
Reg * _busca(Node ** node, int reg);
/* destrói */
void libera_avl(Arv * arv);
void _libera(Node * node);
/* printa*/
void exibe_avl(Arv * arv);
void _exibe(Node * node);
#endif
