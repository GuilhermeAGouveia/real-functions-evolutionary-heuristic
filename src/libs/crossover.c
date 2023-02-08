#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "crossover.h"
#include "utils.h"
#include "types.h"



individue cruzamento_media(individue parent1, individue parent2, int n_itens)
{
    DEBUG(printf("\ncruzamento_media\n"););

    double *child_chromosome = (double *)malloc(n_itens * sizeof(double));
    individue child = {child_chromosome, INFINITY};

    for (int i = 0; i < n_itens; i++)
    {
        child.chromosome[i] = (parent1.chromosome[i] + parent2.chromosome[i]) / 2;
    }
    return child;
}

individue cruzamento_flat(individue parent1, individue parent2, int n_itens)
{
    DEBUG(printf("\ncruzamento_flat\n"););

    double *child_chromosome = (double *)malloc(n_itens * sizeof(double));
    individue child = {child_chromosome, INFINITY};

    for (int i = 0; i < n_itens; i++)
    {
        individue pais[2] = {parent1, parent2};
        int menor = parent1.chromosome[i] < parent2.chromosome[i] ? 0 : 1;
        child.chromosome[i] = random_double(pais[menor].chromosome[i], pais[!menor].chromosome[i]);
    }
    return child;
}

individue cruzamento_blend(individue parent1, individue parent2, int n_itens)
{
    DEBUG(printf("\ncruzamento_blend\n"););

    double *child_chromosome = (double *)malloc(n_itens * sizeof(double));
    individue child = {child_chromosome, INFINITY};

    for (int i = 0; i < n_itens; i++)
    {
        double alpha = random_double(0.0, 1.0);
        child.chromosome[i] = alpha * parent1.chromosome[i] + (1 - alpha) * parent2.chromosome[i];
    }
    return child;
}

individue cruzamento_metade(individue parent1, individue parent2, int n_itens)
{
    DEBUG(printf("\ncruzamento_metade\n"););

    double *child_chromosome = (double *)malloc(n_itens * sizeof(double));
    individue child = {child_chromosome, INFINITY};

    int crossover_point = n_itens / 2;
    for (int i = 0; i < crossover_point; i++)
    {
        child.chromosome[i] = parent1.chromosome[i];
    }
    for (int i = crossover_point; i < n_itens; i++)
    {
        child.chromosome[i] = parent2.chromosome[i];
    }
    return child;
}

individue cruzamento_ponto(individue parent1, individue parent2, int n_itens)
{
    DEBUG(printf("\ncruzamento_metade\n"););

    double *child_chromosome = (double *)malloc(n_itens * sizeof(double));
    individue child = {child_chromosome, INFINITY};

    int crossover_point = rand() % n_itens;
    for (int i = 0; i < crossover_point; i++)
    {
        child.chromosome[i] = parent1.chromosome[i];
    }
    for (int i = crossover_point; i < n_itens; i++)
    {
        child.chromosome[i] = parent2.chromosome[i];
    }
    return child;
}
