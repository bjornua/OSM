#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

void insert(tnode_t **tree, int a){
    if (!tree){
        fprintf(stderr, "Memory not allocated");
        exit(EXIT_FAILURE);
    }
    /* If we get an empty tree, we create a new tree whare data is equal to a.
     * */
    if (!(*tree)){
        struct tnode_t *p;
        p = malloc(sizeof(tnode_t));
        if (!p){
            fprintf(stderr, "Out of memory");
            exit(EXIT_FAILURE);
        }
        struct tnode_t t = {a, NULL, NULL};
        *p = t;
        *tree = p;
    /* If the tree is not empty, we recursively call instert on the left or
     * the right subtree. */
    } else if ((*tree)->data > a) {
        insert(&(*tree)->lchild, a);
    } else {
        insert(&(*tree)->rchild, a);
    }
}

/* We recursively call print_inorder on each of the subtree if they are
 * non-NULL. */
void print_inorder(tnode_t *tree){
    if(tree->lchild != NULL)            /* Print the left subtree */
        print_inorder(tree->lchild);
    printf("%d ", tree->data);           /* Print the actual data */
    if(tree->rchild != NULL)
        print_inorder(tree->rchild);    /* Print the right subtree */
}

int size(tnode_t *tree){
    if (tree == NULL)
        return 0;
    return size(tree->lchild) + 1 + size(tree->rchild);
}

/* We use the array_insert function to recurse the tree. array_insert
 * increments the the calue of p each time it insert an element into the
 * array, this way the elements will be insereted in order. */
void array_insert(tnode_t *tree, int **p){
    if (tree == NULL)
        return;
    array_insert(tree->lchild, p);
    **p = tree->data;
    *p = *p + 1;
    array_insert(tree->rchild, p);
}

int *to_array(tnode_t *tree){
    int *p, *q;
    /* Allocate the entire array, to the size of the the tree */
    p = malloc(size(tree) * sizeof(int));
    q = p;
    array_insert(tree, &q);
    return p;
}

