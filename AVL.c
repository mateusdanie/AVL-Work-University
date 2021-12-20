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

int rotation1(No *pointer, int *h){
    No *pointerU = pointer->esq;
    bal(pointerU);
    if(pointer->bal == 01){
        pointer->esq = pointerU->dir;
        pointerU->dir = pointer;
        pointer = pointerU;
        pointer->dir->bal = 0;
    }else{
        No *pointerV = pointerU->dir;
        bal(pointerV);
        pointerU->dir = pointerV->esq;
        pointerV->esq = pointerV->dir;
        pointerV->dir = pointer;

        if(pointerV->bal == 1){
            pointer->bal = 0;
            pointerU->bal = -1;
        }else{
            pointer->bal = 1;
            pointerU->bal = 0;
        }
        pointer = pointerV;
    }

    pointer->bal = 0, h = 0;
}

int rotation2(No *pointer, int *h){

}

int insertAVL(int x, No *pointer, int *h){
    if(pointer == NULL){
        pointer->key = x;
        pointer->height = height(pointer);
        pointer->bal = bal(pointer);
        h = -1;
    }else{
        if(x == pointer->key){
            printf("Elemento, encontrado!\n");
            return 1;
        }

        if(x < pointer->key){
            insertAVL(x, pointer->esq, h);

            if(h == -1){
                switch (pointer->bal)
                {
                case 1:
                    pointer->bal = 0;
                    h = 0;
                    break;
                
                case 0:
                    pointer->bal = 1;
                    break;

                case -1:
                    rotation1(pointer, h);
                    break;

                default:
                    break;
                }
            }
        }else{
            insertAVL(x, pointer->dir, h);
            if(h == -1){
                switch (pointer->bal)
                {
                case -1:
                    pointer->bal = 0;
                    h = 0;
                    break;
                
                case 0:
                    pointer->bal = 1;
                    break;

                case 1:
                    rotation2(pointer, h);
                    break;
                    
                default:
                    break;
                }
            }
        }
    }
}