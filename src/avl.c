#include "..include/avl.h"

/* constrói */
void constroi_avl(Arv * arv) {
    arv->raiz = NULL;
}

/* auxiliares */
int _max(int a, int b) {
    return (a>b) ? a : b;
}

int _altura(Node * node) {
    return node ? node->h : -1;
}

Node ** _sucessor(Node ** node) {
    if((*node)->esq) _sucessor(&(*node)->esq);
    else return node;
}

/* balanceamento */
void _rebalancear(Node ** node) {
    int fb = _altura((*node)->esq) - _altura((*node)->dir);

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

void _re(Node ** node) {
    Node * x = *node; 
    Node * y = x->dir;
    Node * A = x->esq;
    Node * B = y->esq;
    Node * C = y->dir;

    x->dir = B;
    y->esq = x; 
    *node  = y;

    x->h = max(_altura(A),_altura(B)) + 1;
    y->h = max(_altura(x),_altura(C)) + 1;
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

    x->h = max(_altura(A),_altura(y)) + 1;
    y->h = max(_altura(B),_altura(C)) + 1;
}

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
