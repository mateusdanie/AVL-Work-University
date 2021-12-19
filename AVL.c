#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main()
{

    return 0;
}

int height(No *pointer){
    int he, hd;

    if(pointer->esq != NULL){
       he = height(pointer->esq);
    }else{
        he = 0;
    }
        
    if(pointer->dir != NULL){
        hd = height(pointer->dir);
    }else{
        hd = 0;
    }
    
    if(he > hd){
        pointer->height = he + 1;
    }else{
        pointer->height = hd + 1;
    }
}

int checkAVL(No *pointer, int maxNodes, int *count){
    if(pointer->esq != NULL){
        checkAVL(pointer->esq, maxNodes, count);
    }

    count++;

    if(pointer->dir != NULL){
        checkAVL(pointer->dir, maxNodes, count);
    }

    int he = height(pointer->esq);
    int hd = height(pointer->dir);

    if(hd - he > 1 || hd - he < -1){
        printf("Nao eh AVL!!!\n");
        return -1;
    }else{
        if(count == maxNodes){
            printf("Eh AVL!!!\n");
            return 0;
        }
    }
}

int countNodes(No *pointer, int *count){
    if(pointer->esq != NULL){
        countNodes(pointer->esq, count);
    }

    count++;

    if(pointer->dir != NULL){
        countNodes(pointer->dir, count);
    }
}
