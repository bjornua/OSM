#include <stdio.h>
#include "bintree.c"
#include "dlist.c"

int main(int argc, const char *argv[])
{
    printf("\nTEST\n====\n\n");
    struct tnode_t *p = NULL;
    printf("Testing Insert:\n");
    insert(&p, 9);
    printf("%d\n", p->data);
    insert(&p, 6);
    printf("%d\n", p->lchild->data);
    insert(&p, 11);
    printf("%d\n", p->rchild->data);
    insert(&p, 10);
    printf("%d\n", p->rchild->lchild->data);

    printf("Testing print_inorder:\n");

    print_inorder(p);
    printf("\n");

    printf("Testing size:\n");

    printf("%d\n", size(p));

    printf("Testing to_array:\n");
    int *t;
    t  = to_array(p);

    printf("%d %d %d %d\n", t[0], t[1], t[2], t[3]);

    /* Testing dlist */
    printf("Testing dlist\n");
    struct dlist_t *lst;
    lst = tree2dlist(p);

    return 0;
}
