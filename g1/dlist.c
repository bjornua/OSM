#include <stdlib.h>
#include <stdio.h>

#include "dlist.h"

void cons(dlist_t *a, dlist_t *b){
    a->next->prev = b;
    b->prev->next = a;
    a->next = b;
    b->prev = a;
}

dlist_t *tree2dlist(tnode_t *tree){

    struct dlist_t *p;
    p = malloc(sizeof(dlist_t));
    struct dlist_t t = {tree->data, p, p};
    *p = t;

    struct dlist_t *ls;
    if (tree->lchild){
        ls = tree2dlist(tree->lchild);
        cons(ls, p);
    } else {
        ls = p;
    }

    if (tree->rchild){
        cons(p, tree2dlist(tree->rchild));
    }
    
    return ls;
}
