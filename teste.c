#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tree.h"

void arrayCreate(int *array, int amount);

int main()
{
    srand(time(NULL));
    int *arrayADD = malloc(sizeof(No) * 10000);

    for(int i = 0; i < 1000; i++)
    {
        No *pointer = NULL;
        int h, count = 0;
        

        arrayCreate(arrayADD, 10000);
        
        for(int j = 0; j < 10000; j++)
        {
            
            insertAVL(arrayADD[j], &pointer, &h);
        }

        countNodes(pointer, &count);

        printf("Nos: %d\n", count);

        count = 0;

        if(checkAVL(pointer, 10000, &count) == 0){
            printf("Nao eh AVL!!!\n");
        }else{
            printf("Eh AVL!!!\n");
        }

        for(int k = 0; k < 1000; k++)
        {
            removeAVL(arrayADD[k], &pointer, &h);
        }

        count = 0;

        countNodes(pointer, &count);

        printf("Nos: %d\n", count);

        if(checkAVL(pointer, 1000, &count) == 0){
            printf("Nao eh AVL!!!\n");
        }else{
            printf("Eh AVL!!!\n");
        }
        
        freeAVL(pointer);

        printf("%d\n", i);
    }
    

    return 0;
}

void arrayCreate(int *array, int amount){
    int flag;
    for(int i = 0; i < amount; i++) {
        array[i] = rand() % 100000;
        flag = 0;
        for (int j = 0; j < i && flag == 0; j++) {
            if (array[i] == array[j])
                flag = 1;
        }
        if (flag == 1)
            i--;
    }
}
