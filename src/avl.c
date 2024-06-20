#include "../include/avl.h"

/* constrói */
void constroi_avl(Arv * arv) {
    arv->raiz = NULL;
}

/* auxiliares */
int _max(int a, int b) {
    return (a > b) ? a : b;
}

int _altura(Node * node) {
    return (node) ? node->h : -1;
}

Node ** _sucessor(Node ** node) {
    Node ** temp;
    Node ** aux = node;

    if((*aux)->dir) { // possui filho à direita
        temp = &(*aux)->dir;

        while((*temp)->esq) temp = &(*temp)->esq;
    }
    else { // não possui filho à direita
        temp = &(*aux)->pai;
        while(*temp && *aux == (*temp)->dir) { // encontra sucessor sem comparar item
            aux = &(*temp);
            temp = &(*temp)->pai;
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

    x->pai = y->pai;
    y->pai = x;
    if(B) B->pai = y;

    x->h = _max(_altura(A),_altura(y)) + 1;
    y->h = _max(_altura(B),_altura(C)) + 1;
}

/* inserção */
void insere_avl(Arv * arv, int reg) {
    _insere(&arv->raiz, NULL, reg);
}

void _insere(Node ** node, Node * pai, int reg) {
    if(!*node) {
        *node = (Node *) malloc(sizeof(Node));
        (*node)->esq = NULL;
        (*node)->dir = NULL;
        (*node)->pai = pai;
        (*node)->h = 0;

        (*node)->regs = (Reg *) malloc(sizeof(Reg));
        (*node)->regs->item = reg; 
        (*node)->regs->prox = NULL; 
    }
    else if(reg > (*node)->regs->item) _insere(&(*node)->dir, *node, reg);
    else if(reg < (*node)->regs->item) _insere(&(*node)->esq, *node, reg);
    else {
        Reg * aux = (*node)->regs;

        while(aux) aux = aux->prox;
        
        aux = (Reg *) malloc(sizeof(Reg));
        aux->item = reg;
        aux->prox = NULL;
    }

    (*node)->h = _max(_altura((*node)->dir), _altura((*node)->esq)) + 1;
    _rebalancear(node);
}
/* busca */
Reg * busca_avl(Arv * arv, int reg) {
    return _busca(&arv->raiz, reg);
}

Reg * _busca(Node ** node, int reg) {
    Reg * ret;

    if(!*node) ret = NULL;
    else if(reg > (*node)->regs->item) _busca(&(*node)->dir, reg);
    else if(reg > (*node)->regs->item) _busca(&(*node)->dir, reg);
    else ret = (*node)->regs;

    return ret;
}
/* destrói */
void libera_avl(Arv * arv) {
    _libera(arv->raiz);
}

void _libera(Node * node) {
    if(node) {
        _libera(node->esq);
        _libera(node->dir);

        while(node->regs) {
            Reg * aux = node->regs;
            node->regs = node->regs->prox;
            free(aux);
        }

        free(node);
    }
}
/* printa*/
void exibe_avl(Arv * arv) {
    _exibe(arv->raiz);
}

void _exibe(Node * node) {
    if(node) {
        _exibe(node->esq);

        Reg * aux = node->regs;

        while(aux) {
            printf("%d ", aux->item);
            aux = aux->prox;
        }

        _exibe(node->dir);
    }
}
