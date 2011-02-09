#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

void insert(tnode_t **tree, int a){
    if (tree == NULL){
        fprintf(stderr, "Memory not allocated");
        exit(EXIT_FAILURE);
    }
    if (*tree == NULL){
        struct tnode_t *p;
        p = malloc(sizeof(tnode_t));
        if (p == NULL){
            fprintf(stderr, "Out of memory");
            exit(EXIT_FAILURE);
        }
        struct tnode_t t = {a, NULL, NULL};
        *p = t;
        *tree = p;
    } else if ((*tree)->data > a) {
        insert(&(*tree)->lchild, a);
    } else {
        insert(&(*tree)->rchild, a);
    }
}

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

void array_insert(tnode_t *tree, int *p){
    if (tree == NULL)
        return;
    int s;
    s = size(tree) * sizeof(int);
    array_insert(tree->lchild, p);
    p[s] = tree->data;
    array_insert(tree->rchild, p[s+1]);
}

int *to_array(tnode_t *tree){
    int *p;
    p = malloc(size(tree) * sizeof(int));
    array_insert(tree, p);
    return p;
}

