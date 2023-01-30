#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "./libs/funcoes_cec_2015/cec15_test_func.h"
#include "./libs/statistics.h"
#include "./libs/types.h"
#include "./libs/utils.h"
#define STATISTICS(x) x
#define DEBUG(x)

void fitness(individue *individuo, int dimension)
{
    // individuo.fitness = real_function(individuo.chromosome, dimension);
    cec15_test_func(individuo->chromosome, &individuo->fitness, dimension, 1, 3);
    // double x = individuo->chromosome[0];
    // double y = individuo->chromosome[1];
    // individuo->fitness = pow(x, 2) + pow(y, 2) - cos(18 * x) - cos(18 * y);
    // printf("fitness: %f\n", individuo->fitness);
}

int comparador_individue(const void *a, const void *b)
{
    individue *v1 = (individue *)a;
    individue *v2 = (individue *)b;

    return v1->fitness < v2->fitness;
}

int avaliar(individue *populacao, int n_populacoes, int select_criteria)
{
    int count = 0;
    DEBUG(printf("\navaliar\n"););
    for (int i = 0; i < n_populacoes; i++)
    {
        double individue_custo = populacao[i].fitness;
        if (individue_custo < select_criteria)
        {
            count += 1;
        }
    }

    float percent = (float)count / (float)n_populacoes;
    return percent > 0.90;
}

void print_roleta(int *roleta, int roleta_size, int ball1, int ball2)
{
    DEBUG(printf("\nprint_roleta\n"););
    for (int i = 0; i < roleta_size; i++)
    {
        if (i == ball1 || i == ball2)
            printf("%d<-o ", roleta[i]);
        else
            printf("%d ", roleta[i]);
    }
    printf("\n\n");
}

int roleta_pais(individue *populacao, int n_populacoes)
{
    DEBUG(printf("\nselect_parents\n"););
    int roulette[100000];
    double sum_beneficio = 0.0;

    DEBUG(printf("sum_beneficio[init]\n"););
    for (int i = 0; i < n_populacoes; i++)
    {
        sum_beneficio += populacao[i].fitness;
    }
    DEBUG(printf("sum_beneficio[end]: %lf\n", sum_beneficio););

    int base = 0;
    for (int i = 0; i < n_populacoes; i++)
    {
        double individue_beneficio = sum_beneficio - populacao[i].fitness;
        DEBUG(printf("individue_beneficio: %lf\n", individue_beneficio););
        int limit = ceil((double)(individue_beneficio) / (double)sum_beneficio * 100.00);
        DEBUG(printf("Preenchendo roleta com %d de %d até %d\n", i, base, base + limit););
        for (int j = base; j < base + limit; j++)
        {
            roulette[j] = i;
        }
        base += limit;
    }

    return roulette[rand() % base];
}

void select_parents(individue *populacao, int n_populacoes, individue *parents[2])
{
    int pai1 = roleta_pais(populacao, n_populacoes), pai2;
    do
    {
        pai2 = roleta_pais(populacao, n_populacoes);
    } while (pai1 == pai2);
    parents[0] = &populacao[pai1];
    parents[1] = &populacao[pai2];
    // printf("Pais: %d e %d\n", pai1, pai2);
}

typedef enum
{
    MEDIA,
    MEDIA_GEOMETRICA,
    METADE,
    PONTO,
    FLAT,
    BLEND,
} crossover_type;

individue cruzamento_media(individue parent1, individue parent2, int n_itens)
{
    DEBUG(printf("\ncruzamento_media\n"););

    double *child_chromosome = (double *)malloc(n_itens * sizeof(double));
    individue child = {child_chromosome, INFINITY};

    for (int i = 0; i < n_itens; i++)
    {
        child.chromosome[i] = (parent1.chromosome[i] + parent2.chromosome[i]) / 2;
    }
    fitness(&child, n_itens);
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
    fitness(&child, n_itens);
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
    fitness(&child, n_itens);
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
    fitness(&child, n_itens);
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
    fitness(&child, n_itens);
    return child;
}

individue cruzamento(individue *parents[2], int n_itens)
{
    DEBUG(printf("\ncruzamento\n"););
    individue parent1 = *parents[0];
    individue parent2 = *parents[1];
    int crossover = PONTO;
    switch (crossover)
    {
    case MEDIA:
        return cruzamento_media(parent1, parent2, n_itens);
    case METADE:
        return cruzamento_metade(parent1, parent2, n_itens);
    case PONTO:
        return cruzamento_ponto(parent1, parent2, n_itens);
    case MEDIA_GEOMETRICA:
        return cruzamento_ponto(parent1, parent2, n_itens);
    case FLAT:
        return cruzamento_flat(parent1, parent2, n_itens);
    case BLEND:
        return cruzamento_blend(parent1, parent2, n_itens);
    default:
        return cruzamento_media(parent1, parent2, n_itens);
    }
}

int in_fitness_population(individue *populacao, int n_populacoes, individue individuo)
{
    DEBUG(printf("\nin_fitness_population\n"););
    for (int i = 0; i < n_populacoes; i++)
    {
        if (populacao[i].fitness == individuo.fitness)
        {
            return 1;
        }
    }
    return 0;
}

individue *generate_population(int n_populacoes, int dimension, domain domain_function)
{
    DEBUG(printf("\ngenerate_population\n"););
    individue *population = malloc(n_populacoes * sizeof(individue));
    for (int i = 0; i < n_populacoes; i++)
    {
        population[i].chromosome = (double *)malloc(dimension * sizeof(double));
        for (int j = 0; j < dimension; j++)
        {
            population[i].chromosome[j] = random_double(domain_function.min, domain_function.max);
        }
        population[i].fitness = INFINITY;
    }

    // DEBUG(print_population(population, n_populacoes, dimension););
    return population;
}

individue mutation(individue individuo, int dimension, domain domain_function)
{
    DEBUG(printf("\nmutation\n"););
    int mutation_point = rand() % dimension;
    individuo.chromosome[mutation_point] = random_double(domain_function.min, domain_function.max);
    fitness(&individuo, dimension);

    return individuo;
}

individue *get_best_of_population(individue *population, int n_populacoes)
{
    qsort(population, n_populacoes, sizeof(individue), comparador_individue);
    return &population[n_populacoes - 1];
}

int selection(individue *population, int n_populacoes, int dimension)
{
    DEBUG(printf("\nselection\n"););
    for (int i = 0; i < n_populacoes; i++)
    {
        if (population[i].fitness == INFINITY)
            fitness(&population[i], dimension);
    }

    qsort(population, n_populacoes, sizeof(individue), comparador_individue);
    return 0;
}

/**
 * @brief Algoritmo Evolucionário
 * O algoritmo para quando:
 * 1. Cerca de 90% da população for avaliada como melhor do que o critério de seleção
 * 2. O tempo de execução for maior que 10 segundos
 * 3. O numero de gerações for 500
 * @param itens
 * @param n_itens
 * @param capacidad
 * @param population_size
 * @param select_criteria
 * @return int*
 */

individue *get_pior_pai(individue *pais[2])
{
    return pais[0]->fitness < pais[1]->fitness ? pais[1] : pais[0];
}

individue *evolution(int population_size, int dimension, domain domain_function, double select_criteria, int generations_limit)
{
    DEBUG(printf("\nevolution\n"););
    individue *parents[2];
    individue *population = generate_population(population_size, dimension, domain_function);
    // int generations_count = 0;
    time_t time_init, time_now;
    int generations_count = 0;
    time(&time_init);
    do
    {
        // printf("\ni-ésima geração: %d\n", generations_count);
        selection(population, population_size, dimension);
        // print_population(population, population_size, dimension);
        for (int i = 0; i < population_size - 1; i++)
        {

            DEBUG(printf("\ni-ésimo individuo: %d\n", i););

            select_parents(population, population_size, parents);
            individue child = cruzamento(parents, dimension);
            // O if abaixo garante que nunca haverá dois individuos iguais na população
            if (in_fitness_population(population, population_size, child))
            {
                child = mutation(child, dimension, domain_function);

            }
            DEBUG(printf("Custo do filho: %lf\n", child.fitness););
            individue *pior_pai = get_pior_pai(parents);
            *pior_pai = child;
     
            if (rand() % 100 < 10)
            {
                population[i] = mutation(population[i], dimension, domain_function);
            }
        }
        time(&time_now);
        generations_count++;
        STATISTICS(print_coords(population, population_size, generations_count, generations_limit););

        //printf("Geração: %d\n", generations_count);
    } while (!avaliar(population, population_size, select_criteria) && difftime(time_now, time_init) < 80 && generations_count < generations_limit);

    return get_best_of_population(population, population_size);
}

int main(int argc, char *argv[])
{

    individue *result = NULL;
    result = evolution(50, 10, (domain){-100, 100}, 10, 75);

    print_individue(*result, 10);
    return 0;
}