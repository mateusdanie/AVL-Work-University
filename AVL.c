#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main()
{
    No *pointer = NULL;
    int h, maxNodes = 0, count = 0;

    
    return 0;
}

int preOrdem(No *pointer){

    printf("No %d com bal %d\n", pointer->key, pointer->bal);

    if(pointer->esq != NULL){
        preOrdem(pointer->esq);
    }

    if(pointer->dir != NULL){
        preOrdem(pointer->dir);
    }
}

int height(No *pointer){
    int he, hd;

    if(pointer == NULL){
        return 0;
    }else{
        he = height(pointer->esq);
        hd = height(pointer->dir);
    }

    if(he > hd){
        return he + 1;
    }else{
        return hd + 1;
    }
    
}

int checkAVL(No *pointer, int maxNodes){
    int count = 1;

    if(pointer->esq != NULL){
       count = checkAVL(pointer->esq, maxNodes);
    }

    if(pointer->dir != NULL){
        count = checkAVL(pointer->dir, maxNodes);
    }

    int he = height(pointer->esq);
    int hd = height(pointer->dir);

    if(hd - he > 1 || hd - he < -1){
        count = 0;
    }else{
        count = 1;
    }

    return count;
}

int countNodes(No *pointer, int *count){
    if(pointer->esq != NULL){
        countNodes(pointer->esq, count);
    }

    (*count)++;

    if(pointer->dir != NULL){
        countNodes(pointer->dir, count);
    }
}

int bal(No *pointer){
    int he = height(pointer->esq);
    int hd = height(pointer->dir);

    pointer->bal = hd - he;
}

int allBals(No *pointer){
    if(pointer->esq != NULL){
        allBals(pointer->esq);
    }

    if(pointer->dir != NULL){
        allBals(pointer->dir);
    }

    bal(pointer);
}

int rotationADD1(No **pointer, int *h){
    No *pointerU = (*pointer)->esq;
    bal(pointerU);
    if((*pointer)-->bal == -1){
        (*pointer)->dir = pointerU->dir;
        pointerU->dir = (*pointer);
        (*pointer) = pointerU;
        (*pointer)->dir->bal = 0;
    }else{
        No *pointerV = pointerU->dir;
        bal(pointerV);
        pointerU->dir = pointerV->esq;
        pointerV->esq = pointerU;
        (*pointer)->esq = pointerV->dir;
        pointerV->dir = (*pointer);

        if(pointerV->bal == 1){
            (*pointer)->bal = 0;
            pointerU->bal = -1;
        }else{
            (*pointer)->bal = 1;
            pointerU->bal = 0;
        }
        (*pointer) = pointerV;
    }

    (*pointer)->bal = 0, h = 0;
}

int rotationADD2(No **pointer, int *h){
    No *pointerU = (*pointer)->dir;
    bal(pointerU);
    if((*pointer)->bal == -1){
        (*pointer)->esq = pointerU->dir;
        pointerU->dir = (*pointer);
        (*pointer) = pointerU;
        (*pointer)->dir->bal = 0;
    }else{
        No *pointerV = pointerU->dir;
        bal(pointerV);
        pointerU->dir = pointerV->esq;
        pointerV->esq = pointerU;
        pointerV->esq = pointerV->dir;
        pointerV->dir = (*pointer);

        if(pointerV->bal == 1){
            (*pointer)->bal = -1;
            pointerU->bal = 0;
        }else{
            (*pointer)->bal = 0;
            pointerU->bal = 1;
        }

        (*pointer) = pointerV;
    }

    (*pointer)->bal = 0, h = 0;
}

int insertAVL(int x, No **pointer, int *h){
    if((*pointer) == NULL){
        No *node = (No*)malloc(sizeof(No));
        node->esq = NULL;
        node->dir = NULL;
        node->bal = 0;
        node->key = x;
        (*pointer) = node;
        h = -1;
    }else{
        if(x == (*pointer)->key){
            printf("Elemento, encontrado!\n");
            return 1;
        }

        if(x < (*pointer)->key){
            insertAVL(x,&((*pointer)->esq), h);

            if(h == -1){
                switch ((*pointer)->bal)
                {
                case 1:
                    (*pointer)->bal = 0;
                    h = 0;
                    break;
                
                case 0:
                   (*pointer)->bal = 1;
                    break;

                case -1:
                    rotationADD1(pointer, h);
                    break;

                default:
                    break;
                }
            }
        }else{
            insertAVL(x, &((*pointer)->dir), h);
            if(h == -1){
                switch ((*pointer)->bal)
                {
                case -1:
                    (*pointer)->bal = 0;
                    h = 0;
                    break;
                
                case 0:
                    (*pointer)->bal = 1;
                    break;

                case 1:
                    rotationADD2(pointer, h);
                    break;
                    
                default:
                    break;
                }
            }
        }
    }
}