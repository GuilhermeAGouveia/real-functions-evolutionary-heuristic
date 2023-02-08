#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void print_individue(individue individuo, int dimension)
{
    DEBUG(printf("\nprint_individue\n"););
    printf("Individue: ");
    for (int j = 0; j < dimension; j++)
    {
        printf("%lf ", individuo.chromosome[j]);
    }
    printf("\nFitness: %lf\n", individuo.fitness);
}

void print_population(individue *pop, int n_populacoes, int dimension)
{
    DEBUG(printf("\nprint_population\n"););
    for (int i = 0; i < n_populacoes; i++)
    {
        print_individue(pop[i], dimension);
    }
}


double random_double(double min, double max)
{
    double random = min + (max - min) * (rand() / (double)RAND_MAX);
    return random;
}
