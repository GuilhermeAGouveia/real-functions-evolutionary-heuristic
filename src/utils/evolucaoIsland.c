#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libs/funcoes_cec_2015/cec15_test_func.h"
#include "libs/utils.h"
#include "libs/types.h"
#include "libs/statistics.h"

/*#define POPULATION_SIZE 50
#define NUM_ISLANDS 10
#define MAX_GENERATIONS 75
#define MUTATION_RATE 0.01
#define DIMENSION 10*/

/*
// Struct para representar cada indivíduo na população
typedef struct
{
    double chromosome[DIMENSION];
    double fitness;
} Individual;

// Função para avaliar o fitness de cada indivíduo
double evaluate_fitness(Individual *individual, int dim)
{
    double result = 0.0;
    cec15_test_func(individual->chromosome, &result, dim, 1, 3);
    return result;
}

// Função para gerar a população inicial
void init_population(Individual *population)
{
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < DIMENSION; j++)
        {
            population[i].chromosome[j] = rand() % 2;
        }
        population[i].fitness = evaluate_fitness(&population[i], DIMENSION);
    }
}

// Função para seleção dos pais
void select_parents(Individual *population, Individual *parents)
{
    int parent1, parent2;
    parent1 = rand() % POPULATION_SIZE;
    do
    {
        parent2 = rand() % POPULATION_SIZE;
    } while (parent1 == parent2);

    parents[0] = population[parent1];
    parents[1] = population[parent2];
}

// Função para realizar a crossover
void crossover(Individual *parents, Individual *child)
{
    int crossover_point = rand() % DIMENSION;

    for (int i = 0; i < crossover_point; i++)
    {
        child->chromosome[i] = parents[0].chromosome[i];
    }
    for (int i = crossover_point; i < DIMENSION; i++)
    {
        child->chromosome[i] = parents[1].chromosome[i];
    }

    child->fitness = evaluate_fitness(child, DIMENSION);
}

// Função para realizar a mutação
void mutate(Individual *child)
{
    for (int i = 0; i < DIMENSION; i++)
    {
        float random_num = (float)rand() / (float)RAND_MAX;
        if (random_num < MUTATION_RATE)
        {
            child->chromosome[i] = !child->chromosome[i];
        }
    }

    child->fitness = evaluate_fitness(child, DIMENSION);
}

// Função para seleção dos sobreviventes
void select_survivors(Individual *population, Individual *children)
{
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        if (children[i].fitness > population[i].fitness)
        {
            population[i] = children[i];
        }
    }
}

// Função para executar o algoritmo genético de modelo de ilhas
void run_island_model(Individual *population)
{
    Individual parents[2];
    Individual children[POPULATION_SIZE];

    for (int g = 0; g < MAX_GENERATIONS; g++)
    {
        for (int i = 0; i < POPULATION_SIZE; i++)
        {
            select_parents(population, parents);
            crossover(parents, &children[i]);
            mutate(&children[i]);
        }
        select_survivors(population, children);
    }
}

int main()
{
    srand(time(NULL));

    Individual population[POPULATION_SIZE];
    init_population(population);

    run_island_model(population);
    printf("Fitness: %lf \n", population[0].fitness);
    return 0;
}*/

#define NUM_ISLANDS 4
#define POPULATION_SIZE_PER_ISLAND 50
#define MAX_GENERATIONS 75
#define MUTATION_RATE 0.10
#define DIMENSION 10

typedef struct
{
    double genes[DIMENSION];
    double fitness;
} Individual;

// Função para avaliar o fitness de cada indivíduo
double evaluate_fitness(Individual *individual, int dim)
{
    double result = 0.0;
    cec15_test_func(individual->genes, &result, dim, 1, 3);
    return result;
}

// Função para inicializar a população
void init_population(Individual population[][POPULATION_SIZE_PER_ISLAND])
{
    for (int i = 0; i < NUM_ISLANDS; i++)
    {
        for (int j = 0; j < POPULATION_SIZE_PER_ISLAND; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                population[i][j].genes[k] = rand() % 2;
            }
        population[i][j].fitness = evaluate_fitness(&population[i][j], DIMENSION);    
        }
    }
}

// Função para selecionar os pais
void select_parents(Individual *population, Individual *parents)
{
    int parent1 = rand() % POPULATION_SIZE_PER_ISLAND;
    int parent2 = rand() % POPULATION_SIZE_PER_ISLAND;

    while (parent1 == parent2)
    {
        parent2 = rand() % POPULATION_SIZE_PER_ISLAND;
    }

    parents[0] = population[parent1];
    parents[1] = population[parent2];
}

// Função para realizar o crossover
void crossover(Individual *parents, Individual *child)
{
    int crossover_point = rand() % 10;

    for (int i = 0; i < crossover_point; i++)
    {
        child->genes[i] = parents[0].genes[i];
    }

    for (int i = crossover_point; i < 10; i++)
    {
        child->genes[i] = parents[1].genes[i];
    }
    child->fitness = evaluate_fitness(child, DIMENSION);
}

// Função para realizar a mutação
void mutate(Individual *individual)
{
    for (int i = 0; i < 10; i++)
    {
        if (rand() / (double)RAND_MAX < MUTATION_RATE)
        {
            individual->genes[i] = individual->genes[i] == 1 ? 0 : 1;
        }
    }
    individual->fitness = evaluate_fitness(individual, DIMENSION);
}

// Função para selecionar os sobreviventes
void select_survivors(Individual *population, Individual *children)
{
    for (int i = 0; i < POPULATION_SIZE_PER_ISLAND; i++)
    {
        int child = rand() % POPULATION_SIZE_PER_ISLAND;
        population[i] = children[child];
    }
}

// Função para executar o algoritmo genético de modelo de ilhas
void run_island_model(Individual population[][POPULATION_SIZE_PER_ISLAND])
{
    Individual parents[2];
    Individual children[POPULATION_SIZE_PER_ISLAND];

    for (int g = 0; g < MAX_GENERATIONS; g++)
    {
        for (int i = 0; i < NUM_ISLANDS; i++)
        {
            for (int j = 0; j < POPULATION_SIZE_PER_ISLAND; j++)
            {
                select_parents(population[i], parents);
                crossover(parents, &children[j]);
                mutate(&children[j]);
            }
            select_survivors(population[i], children);
        }
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    Individual population[NUM_ISLANDS][POPULATION_SIZE_PER_ISLAND];
    init_population(population);
    run_island_model(population);
    printf("Fitness: %lf \n", population[0][0].fitness);
    return 0;
}
