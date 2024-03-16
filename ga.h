#define PoolSize 20
#define ChromosomeSize 10

#define CrossoverRate 0.5 
#define MutationRate 0.1


typedef struct Individual
{
    char chromosome[ChromosomeSize];
    int fitness;
}individual_t;

void i_fitness(individual_t *q);

individual_t *i_new(const char str[ChromosomeSize]);

individual_t *i_crosser(individual_t *f,individual_t *m);

//choose a mate 
individual_t i_chooseMate(individual_t pool[PoolSize]);

void i_show(individual_t *q);

/********************/
/*****  TOOL    *****/
/********************/

//bubble sort: small->big
void swap(individual_t *a,individual_t *b);

void fSort(individual_t pool[PoolSize]);

int getrandom(int min,int max);