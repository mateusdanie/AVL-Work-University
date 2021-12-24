#ifndef TREE_H
#define TREE_H

typedef struct no{
    int key, bal;
    struct no *esq;
    struct no *dir;
}No;

int preOrdem(No *pointer);
int height(No *pointer);
int bal(No *pointer);
int allBals(No *pointer);
int rotationADD1(No **pointer, int *h);
int rotationADD2(No **pointer, int *h);
int rotationRemove1(No **pointer, int *h);
int rotationRemove2(No **pointer, int *h);
int balance(No **pointer, char rotationSide, int *h);
int checkAVL(No *pointer, int maxNodes);
int countNodes(No *pointer, int *count);
int insertAVL(int x, No **pointer, int *h);
int removeAVL(int x, No **pointer, int *h);



#endif