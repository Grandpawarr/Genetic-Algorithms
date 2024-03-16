#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<time.h>

#include"ga.h"

const char TargetGene[ChromosomeSize]="0011100000";

/********************/
/*****  individual_funtion    *****/
/********************/

void i_fitness(individual_t *q)
{
    for(int i=0;i<ChromosomeSize;i++){
        q->fitness +=(q->chromosome[i]==TargetGene[i]?1:0);
    }
}

individual_t *i_new(const char str[ChromosomeSize])
{
    individual_t *new=malloc(sizeof(individual_t));
    assert(new);

    strcpy(new->chromosome,str);
    new->fitness=0;
    i_fitness(new);

    return new;
}

individual_t *i_crosser(individual_t *f,individual_t *m)
{
    //mating and mutation grodue the next generation
    char cstr[ChromosomeSize+1]="";
    for(int i=0;i<ChromosomeSize;i++){
        float probability=(float)getrandom(0,100)/100;

        if(probability<CrossoverRate)
            cstr[i]=f->chromosome[i];
        else if(probability<MutationRate){
            cstr[i]=(char)getrandom(0,1);
            printf("\t%c\t",cstr[i]);}
        else
            cstr[i]=m->chromosome[i];
    }
    cstr[ChromosomeSize]='\0';
    //new individual
    individual_t *new=i_new(cstr);
    assert(new);

    return new;
}

//using wheel selection
individual_t i_chooseMate(individual_t pool[PoolSize])
{
    int fitsum=0;
    for(int i=0;i<PoolSize;i++){
        fitsum +=pool[i].fitness;
    }

    int probability=getrandom(0,fitsum)%fitsum;

    int targetnum=pool[0].fitness;
    for(int i=1;i<PoolSize;i++){
        if(targetnum>probability)
            return pool[i-1];
        targetnum +=pool[i].fitness;
    }

    return pool[PoolSize-1];
}

void i_show(individual_t *q)
{
    printf("%s\t%d",q->chromosome,q->fitness);
}

/********************/
/*****  TOOL    *****/
/********************/

void swap(individual_t *a,individual_t *b)
{
    individual_t tmp=*a;
    *a=*b;
    *b=tmp;
}

void fSort(individual_t pool[PoolSize])
{
    //individual_t tmp[PoolSize];
    for(int i=0;i<PoolSize-1;i++)
        for(int j=i+1;j<PoolSize;j++)
            if(pool[i].fitness>pool[j].fitness)
                swap(&pool[i],&pool[j]);
}

int getrandom(int min,int max)
{
    return (rand()%(max-min+1)+min);
}