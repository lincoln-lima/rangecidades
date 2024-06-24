#include "../include/avl.h"

/* constrói */
void constroi_avl(ArvAVL * arv, int (* cmp)(void *, void *)) {
    arv->raiz = NULL;
    arv->cmp = cmp;
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
void insere_avl(ArvAVL * arv, void * chave, int cod_ibge) {
    _insere(arv, &arv->raiz, NULL, chave, cod_ibge);
}

void _insere(ArvAVL * arv, Node ** node, Node * pai, void * chave, int cod_ibge) {
    if(!*node) {
        *node = (Node *) malloc(sizeof(Node));
        (*node)->esq = NULL;
        (*node)->dir = NULL;
        (*node)->pai = pai;
        (*node)->h = 0;

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
            Reg * aux = (*node)->regs;

            while(aux->prox) aux = aux->prox;
            
            aux->prox = (Reg *) malloc(sizeof(Reg));
            aux->prox->chave = chave;
            aux->prox->cod_ibge = cod_ibge;
            aux->prox->prox = NULL;
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
            free(aux);
        }

        free(node);
    }
}

/* printa */
void exibe_avl(ArvAVL * arv) {
    _exibe(arv->raiz);
    printf("\n");
}

void _exibe(Node * node) {
    if(node) {
        _exibe(node->esq);

        Reg * aux = node->regs;

        while(aux) {
            printf("%d ", aux->cod_ibge);
            aux = aux->prox;
        }

        _exibe(node->dir);
    }
}

/* queries */
int * query_simp_avl(ArvAVL * arv, void * chave, int eq) {
    int * ret = (int *) calloc(5571, sizeof(int));
    int * pret = ret;
    int cmp;

    Node * aux = arv->raiz;
    Reg * reg;

    if(eq > 0) {
        while(aux->dir) aux = aux->dir;
        
        do {
            cmp = arv->cmp(chave, aux->regs->chave);

            if(cmp < 0) {
                reg = aux->regs;

                _salva_ret(&pret, reg);

                aux = *(_antecessor(&aux));
            }
        } while(aux && cmp < 0); 
    }
    else if(eq < 0) {
        while(aux->esq) aux = aux->esq;
        
        do {
            cmp = arv->cmp(chave, aux->regs->chave);

            if(cmp > 0) {
                reg = aux->regs;

                _salva_ret(&pret, reg);

                aux = *(_sucessor(&aux));
            }
        } while(aux && cmp > 0); 
    }
    else {
        reg = busca_avl(arv, chave);
        _salva_ret(&pret, reg);
    }

    return ret;
}

void _salva_ret(int ** pret, Reg * reg) {
    while(reg) {
        *(*pret)++ = reg->cod_ibge; 
        reg = reg->prox;
    } 
}

int * query_comb_avl(int * regs1, int * regs2) {
    int * ret = (int *) calloc(5571, sizeof(int));
    int * pret = ret;

    for(int * aux1 = regs1; aux1 < regs1 + 5570 && *aux1 != 0; aux1++) {
        int * aux2;
        for(aux2 = regs2; aux2 < regs2 + 5570 && *aux2 != 0 && *aux1 != *aux2; aux2++); 

        if(*aux1 == *aux2) *pret++ = *aux1;
    }

    free(regs1);
    free(regs2);

    return ret;
}
