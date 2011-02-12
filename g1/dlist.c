#include <stdlib.h>
#include <stdio.h>

#include "dlist.h"

dlist_t *tree2dlist(tnode_t *tree){
    printf("tree2dlist %d \n", tree->data);

    struct dlist_t *ls, *rs;
    ls = tree2dlist(tree->lchild);
    rs = tree2dlist(tree->rchild);

    rs->prev = ls;
    ls->prev->next = rs;

    struct dlist_t *p;
    p = malloc(sizeof(dlist_t));
    struct dlist_t t = {tree->data, ls, rs};
    *p = t;
    rs->prev = p;
    ls->next = p;
    
    return ls;

}
