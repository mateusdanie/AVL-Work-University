#ifndef TREE_H
#define TREE_H

typedef struct no{
    int key, height, bal;
    struct no *esq;
    struct no *dir;
}No;

int height(No *pointer);
int bal(No *pointer);
int allBals(No *pointer);
int rotation1(No *pointer, int *h);
int rotation2(No *pointer, int *h);
int checkAVL(No *pointer, int maxNodes, int *count);
int countNodes(No *pointer, int *count);
int insertAVL(int x, No *pointer, int *h);



#endif