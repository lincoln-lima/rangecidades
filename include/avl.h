#ifndef __AVLMOD__
#define __AVLMOD__
#include<stdio.h>
#include<stdlib.h>
typedef struct _reg{
    void * item;
    struct _reg * prox;
} Regs;

typedef struct _node {
    Regs * regs;
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
void insere_avl(Arv * arv, void * reg);
void _insere(Node ** node, void * reg);
/* busca */
int busca_avl(Arv * arv, void * reg);
int _busca(Node ** node, void * reg);
/* destrói */
void libera_avl(Arv * arv);
void _libera(Node * node);
/* printa*/
void exibe_avl(Arv * arv);
void _exibe(Node * node);
#endif
