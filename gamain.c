#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

#include"ga.h"


individual_t SelectionP();
//random generate first Gene pool
void initial(individual_t pool[PoolSize])
{
    for(int i=0;i<PoolSize;i++){
        char str[ChromosomeSize];
        for(int j=0;j<ChromosomeSize;j++){
            str[j]=getrandom(0,1)+'0';
        }
        //printf("hello: %s",str);
        pool[i]=*i_new(str);
    }
}

void Reproduction(individual_t pool[PoolSize])
{
    individual_t newpool[PoolSize];

    for(int i=0;i<PoolSize;i++){
        individual_t f=i_chooseMate(pool);
        individual_t m=i_chooseMate(pool);
        newpool[i]=*i_crosser(&f,&m);
    }
    
    for(int i=0;i<PoolSize;i++){
        memcpy(&pool[i],&newpool[i],sizeof(individual_t));
    }
}

void showPool(individual_t pool[PoolSize])
{
    fSort(pool);

    bool next=-1;
    for(int i=0;i<PoolSize;i++){
        if(next>=1){
            printf("\n");
            next=0;
        }else
            next ++;
        i_show(&pool[i]);
        printf("\t");
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));

    individual_t Pool[PoolSize];
    initial(Pool);
    printf("----- 1 th gemerastion Gene: -----\n");
    showPool(Pool);

    for(int i=2;i<20;i++){
        Reproduction(Pool);
        printf("----- %d th gemerastion Gene: -----\n",i);
        showPool(Pool);
    }
    
    return 0;
}