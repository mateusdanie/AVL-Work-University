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

int checkAVL(No *pointer, int maxNodes, int *count){

    if(pointer->esq != NULL){
       checkAVL(pointer->esq, maxNodes, count);
    }

    if(pointer->dir != NULL){
        checkAVL(pointer->dir, maxNodes, count);
    }

    int he = height(pointer->esq);
    int hd = height(pointer->dir);

    if(hd - he > 1 || hd - he < -1){
        return 0;
    }else{
        (*count)++;
    }

    if(*count == maxNodes){
        return 1;
    }
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

void rotationADD1(No **pointer, int *h) {
  No *pointerU;

  pointerU = (*pointer)->esq;
  if (pointerU->bal == -1) { 
    (*pointer)->esq = pointerU->dir;
    pointerU->dir = (*pointer);
    (*pointer) = pointerU;
    (*pointer)->dir->bal = 0;
  } else {            
    No *pointerV;
    pointerV = pointerU->dir;
    pointerU->dir = pointerV->esq;
    pointerV->esq = pointerU;
    (*pointer)->esq = pointerV->dir;
    pointerV->dir = (*pointer);
    
    if (pointerV->bal == -1) {
      (*pointer)->bal = 1;
      pointerU->bal = 0;
    } else if (pointerV->bal == 1) {
      (*pointer)->bal = 0;
      pointerU->bal = -1;
    } else {
      (*pointer)->bal = 0;
      pointerU->bal = 0;
    }
    (*pointer) = pointerV;
  }
  (*pointer)->bal = 0; *h = 0; 
}


void rotationADD2(No **pointer, int *h) {
    No *pointerU;
    pointerU = (*pointer)->dir;

    if (pointerU->bal == 1) { 
        (*pointer)->dir = pointerU->esq;
        pointerU->esq = (*pointer);
        (*pointer) = pointerU;
        (*pointer)->esq->bal = 0;
    } else {            
        No *pointerV;

        pointerV = pointerU->esq;
        pointerU->esq = pointerV->dir;
        pointerV->dir = pointerU;
        (*pointer)->dir = pointerV->esq;
        pointerV->esq = (*pointer);
        
        if (pointerV->bal == 1) {
        (*pointer)->bal = -1;
        pointerU->bal = 0;
        } else if (pointerV->bal == -1){
        (*pointer)->bal = 0;
        pointerU->bal = 1;
        } else {
        (*pointer)->bal = 0;
        pointerU->bal = 0;
        }
        (*pointer) = pointerV;
    }
    (*pointer)->bal = 0; *h = 0; 
}


void insertAVL(int x, No **pointer, int *h) {
    if ((*pointer) == NULL) {

        No *node = malloc(sizeof(No));
        node->esq = node->dir = NULL;
        node->bal = 0;
        node->key = x;
        (*pointer) = node;

        *h = 1;  
    }else{
        if (x == (*pointer)->key) {

            printf("Elemento, ja existe!!!\n");
            return;
        }
        
        if (x < (*pointer)->key) {

            insertAVL(x, &((*pointer)->esq), h);

            if(*h == 1){
                switch((*pointer)->bal){
                    case 1: 
                        (*pointer)->bal = 0; 
                        *h = 0;
                    break;
                    
                    case 0: 
                        (*pointer)->bal = -1;
                    break;

                    case -1: 
                        rotationADD1(pointer, h);
                    break;
                }
            }
        }else{

            insertAVL(x, &((*pointer)->dir), h);

            if (*h == 1) {
                switch((*pointer)->bal) {

                    case -1: 
                        (*pointer)->bal = 0; 
                        *h = 0;
                    break;

                    case 0: 
                        (*pointer)->bal = 1;
                    break;

                    case 1: 
                        rotationADD2(pointer, h);
                    break;

                }
            }
        }
    }
}

void rotationRemove1(No **pointer, int *h) {
  No *pointerU;

  pointerU = (*pointer)->esq;
  if (pointerU->bal <= 0) {
    (*pointer)->esq = pointerU->dir;
    pointerU->dir = (*pointer);
    (*pointer) = pointerU;
    if (pointerU->bal == -1) {
      pointerU->bal = (*pointer)->dir->bal = 0;
      *h = 1;
    } else {
      pointerU->bal = 1;
      (*pointer)->dir->bal = -1;
      *h = 0;
    }
  } else { 
    No *pointerV;
    pointerV = pointerU->dir;

    pointerU->dir = pointerV->esq;
    pointerV->esq = pointerU;
    (*pointer)->esq = pointerV->dir;
    pointerV->dir = (*pointer);
    (*pointer) = pointerV;

    switch(pointerV->bal) {

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

    }

    (*pointer)->bal = 0; 
    *h = 1;
  }
}

void rotationRemove2(No **pointer, int *h) {
  No *pointerU;
  pointerU = (*pointer)->dir;

  if (pointerU->bal >= 0) { 
    (*pointer)->dir = pointerU->esq;
    pointerU->esq = (*pointer);
    (*pointer) = pointerU;
    if (pointerU->bal == 1) { 
      pointerU->bal = (*pointer)->esq->bal = 0;
      *h = 1;
    } else {
      pointerU->bal = -1;
      (*pointer)->esq->bal = 1;
      *h = 0;
    }
  } else {
    No *pointerV;
    pointerV = pointerU->esq;

    pointerU->esq = pointerV->dir;
    pointerV->dir = pointerU;
    (*pointer)->dir = pointerV->esq;
    pointerV->esq = (*pointer);
    (*pointer) = pointerV;

    switch(pointerV->bal) {

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

    }

    (*pointer)->bal = 0; 
    *h = 1;
  }
}

// Procedimento: reponsável por realizar o balanceamento
void balance(No **pointer, char rotationSide, int* h) {
  if (*h) {
    if (rotationSide == 'R') {
      switch ((*pointer)->bal) {
        case 1: (*pointer)->bal = 0; break;
        case 0: (*pointer)->bal = -1; *h = 0; break;
        case -1: rotationRemove1(pointer, h); break;
      }
    } else {
      switch((*pointer)->bal) {
        case -1: (*pointer)->bal = 0; break;
        case 0: (*pointer)->bal = 1; *h = 0; break;
        case 1: rotationRemove2(pointer, h); break;
      }
    }
  }
}

void switchNodes(No **firstNode, No **secondNode) {
  No* bakcupPointer;
  int backupBal;

  bakcupPointer = (*secondNode);
  (*secondNode) = (*firstNode);
  (*firstNode) = bakcupPointer;

  bakcupPointer = (*secondNode)->esq;
  (*secondNode)->esq = (*firstNode)->esq;
  (*firstNode)->esq = bakcupPointer;
  
  bakcupPointer = (*secondNode)->dir;
  (*secondNode)->dir = (*firstNode)->dir;
  (*firstNode)->dir = bakcupPointer;

  backupBal = (*secondNode)->bal;
  (*secondNode)->bal = (*firstNode)->bal;
  (*firstNode)->bal = backupBal;
}

void removeAVL(int x, No **pointer, int *h) {
    if ((*pointer) == NULL) {   
        printf("Elemento, nao existe!\n"); 
        *h = 0;
    }else{

        if(x < (*pointer)->key){
            removeAVL(x, &(*pointer)->esq, h);
            balance(pointer,'L',h);
        }else{

            if(x > (*pointer)->key){
                removeAVL(x, &(*pointer)->dir, h);
                balance(pointer,'R',h);
            }else{

                No *backupPointer;
                backupPointer = (*pointer);

                if((*pointer)->esq == NULL){
                    (*pointer) = (*pointer)->dir; 
                    *h = 1;
                    free(backupPointer);
                }else{

                    if((*pointer)->dir == NULL){
                        (*pointer) = (*pointer)->esq; 
                        *h = 1;
                        free(backupPointer);
                    }else{

                        No *son;
                        son = (*pointer)->dir;

                        if(son->esq == NULL){
                            son->esq = (*pointer)->esq;
                            son->bal = (*pointer)->bal;
                            (*pointer) = son;
                            *h = 1;
                            free(backupPointer);
                        }else{

                            No *fatherSon;
                            while (son->esq != NULL) {
                                fatherSon = son;
                                son = son -> esq; 
                        }

                        switchNodes(pointer, &fatherSon->esq);
                        removeAVL(x, &(*pointer)->dir, h);
                        }
                        balance(pointer,'R',h);
                    }
                }
            }
        }
    }
}

void freeAVL(No *pointer){
    if(pointer->esq != NULL){
        freeAVL(pointer->esq);
    }

    if(pointer->dir != NULL){
        freeAVL(pointer->dir);
    } 

    free(pointer);
}



#endif