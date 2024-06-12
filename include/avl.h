#ifndef __AVL__
#define __AVL__
#include<stdio.h>
#include<stdlib.h>
typedef struct _node {
    int num;
    int h;
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
void insere_avl(Arv * arv, int num);
void _insere(Node ** node, int num);
/* busca */
int busca_avl(Arv * arv, int num);
int _busca(Node ** node, int num);
/* destrói */
void libera_avl(Arv * arv);
void _libera(Node * node);
/* printa*/
void exibe_avl(Arv * arv);
void _exibe(Node * node);
#endif
