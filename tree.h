#ifndef TREE_H
#define TREE_H

typedef struct no{
    int value, height;
    struct no *esq;
    struct no *dir;
}No;

int height(No *pointer);
int checkAVL(No *pointer, int maxNodes, int *count);
int countNodes(No *pointer, int *count);



#endif