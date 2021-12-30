#ifndef TREE_H
#define TREE_H

typedef struct no{
    int key, bal;
    struct no *esq;
    struct no *dir;
}No;

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

int rotationRemove1(No **pointer, int *h){
    No *pointerU = (*pointer)->esq;
    bal(pointerU);

    if(pointerU->bal <= 0){
        (*pointer)->esq = pointerU->dir;
        pointerU->dir = (*pointer);
        (*pointer) = pointerU;

        if(pointerU->bal == -1){
            pointerU->bal = (*pointer)->dir->bal = 0;
            h = -1;
        }else{
            pointerU->bal = 1;
            (*pointer)->dir->bal = -1;
            h = 0;
        }

    }else{

        No *pointerV = pointerU->dir;
        bal(pointerV);
        pointerU->dir = pointerV->esq;
        pointerV->esq = pointerU;
        (*pointer)->esq = pointerV->dir;
        pointerV->dir = (*pointer);
        (*pointer) = pointerV;

        switch (pointerV->bal)
        {
        case -1:
            pointerU->bal = 0;
            (*pointer)->dir->bal = 1;
            break;
        case 0:
            pointerU->bal = 0;
            (*pointer)->dir->bal = 0;
            break;
        case 1:
            pointerU->bal = -1;
            (*pointer)->dir->bal = 0;
            break;
        default:
            break;
        }
    }

    (*pointer)->bal = 0;
    h = -1;
}

int rotationRemove2(No **pointer, int *h){
    No *pointerU = (*pointer)->dir;
    bal(pointerU);

    if(pointerU->bal >= 0){
        (*pointer)->dir = pointerU->esq;
        pointerU->esq = (*pointer);
        (*pointer) = pointerU;

        if(pointerU->bal == -1){
            pointerU->bal = (*pointer)->esq->bal = 0;
            h = -1;
        }else{
            pointerU->bal = -1;
            (*pointer)->dir->bal = 1;
            h = 0;
        }

    }else{

        No *pointerV = pointerU->esq;
        bal(pointerV);
        pointerU->esq = pointerV->dir;
        pointerV->dir = pointerU;
        (*pointer)->dir = pointerV->esq;
        pointerV->esq = (*pointer);
        (*pointer) = pointerV;

        switch (pointerV->bal)
        {
        case -1:
            pointerU->bal = 0;
            (*pointer)->esq->bal = -1;
            break;
        case 0:
            pointerU->bal = 0;
            (*pointer)->esq->bal = 0;
            break;
        case 1:
            pointerU->bal = 1;
            (*pointer)->esq->bal = 0;
            break;
        default:
            break;
        }
    }

    (*pointer)->bal = 0;
    h = -1;
}

int balance(No **pointer, char rotationSide, int *h){
    if(h -1){
        if(rotationSide == "D" || rotationSide == "d"){
            switch ((*pointer)->bal)
            {
            case 1:
                (*pointer)->bal = 0;
                break;
            case 0:
                (*pointer)->bal = -1;
                h = 0;
                break;
            case -1:
                rotationRemove1(pointer, h);
                break;

            default:
                break;
            }
        }else if(rotationSide == "L" || rotationSide == "l"){
            switch ((*pointer)->bal)
            {
            case -1:
                (*pointer)->bal = 0;
                break;
            case 0:
                (*pointer)->bal = 1;
                h = -1;
                break;
            case 1:
                rotationRemove2(pointer, h);
                break;

            default:
                break;
            }
        }else{
            printf("Lado da rotação invalida!!!\n");
        }
    }
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

int removeAVL(int x, No **pointer, int *h){
    if((*pointer) == NULL){
        printf("Elemento não existe!!!\n");
        h = 0;
    }else{
        if(x < (*pointer)->key){
            removeAVL(x, (*pointer)->dir, h);
            balance(pointer, "D", h);
        }else{
            No *aux = (*pointer);
            if((*pointer)->esq == NULL){
                (*pointer) = (*pointer)->dir;
                h = -1;
            }else{
                if((*pointer)->dir == NULL){
                    (*pointer) = (*pointer)->esq;
                    h = -1;
                }else{
                    No *son = (*pointer)->dir;
                    
                    if(son->esq == NULL){
                        son->esq = (*pointer)->esq;
                        son->bal = (*pointer)->bal;
                        (*pointer) = son;
                        h = -1;
                    }else{
                        No *fatherSon;
                        while(son->esq != NULL){
                            fatherSon = son;
                            son = son->esq;
                        }

                        No *backup;
                        int balBackup;

                        backup = fatherSon;
                        fatherSon = (*pointer);
                        (*pointer)->esq = backup;

                        backup = fatherSon->esq;
                        fatherSon->esq = (*pointer)->esq;
                        (*pointer)->esq = backup;

                        backup = fatherSon->dir;
                        fatherSon->dir = (*pointer)->dir;
                        (*pointer)->dir = backup;

                        balBackup = fatherSon->bal;
                        fatherSon->bal = (*pointer)->bal;
                        (*pointer)->bal = balBackup;

                        removeAVL(x, (*pointer)->dir, h);
                    }

                    balance((*pointer), D, h);
                }
            }
        }
    }
}



#endif