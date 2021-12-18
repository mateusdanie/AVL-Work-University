#ifndef TREE_H
#define TREE_H

typedef struct no{
    int value;
    struct no *esq;
    struct no *dir;
}No;

int height(No *pointer);


#endif