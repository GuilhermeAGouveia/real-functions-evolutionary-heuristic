#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "libs/types.h"
#include "libs/utils.h"
#include "libs/funcoes_cec_2015/cec15_test_func.h"

int maxLocal = 0;

int compare(const void *a, const void *b)
{
    individue *ia = (individue *)a;
    individue *ib = (individue *)b;
    printf("ia->fitness = %lf, ib->fitness = %lf\n", ia->fitness, ib->fitness);
    return ((double) ia->fitness > (double) ib->fitness);
}

void Ordena_Populacao(individue *populacao, int TAM, int dimensao)
{
    DEBUG(printf("\nOrdena_Populacao\n"););
    qsort(populacao, TAM, sizeof(individue), compare);
}

void printVet(int *vet, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        printf("%d", vet[i]);
    }
    printf("\n");
}

void zeraVetor(int *vet, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        vet[i] = 0;
    }
}

double fitness(individue individuo, int dimensao)
{
    DEBUG(printf("\nfitness\n"););
    double result;
    cec15_test_func(individuo.chromosome, &result, dimensao, 1, 3);
    return result;
}

// calcula dos valores de peso e beneficio
void calcula_dados(individue *populacao, int TAM_P, int dimensao)
{
    DEBUG(printf("\ncalcula_dados\n"););
    float peso = 0, beneficio = 0;
    int posicao = 0;
    for (int j = 0; j < TAM_P; j++)
    {
        populacao[j].fitness = fitness(populacao[j], dimensao);
        DEBUG(printf("individuo %d, fitness = %lf\n", j, populacao[j].fitness);)

    }
}

// gera a populacao com a primeira populacao sendo a populaca oda heuristica, e as restantes aleatorias
individue *generate_population(int n_populacoes, int dimension, domain domain_function)
{
    DEBUG(printf("\ngenerate_population\n"););
    individue *population = (individue *)malloc(n_populacoes + 1 * sizeof(individue));
    for (int i = 0; i < n_populacoes + 1; i++)
    {
        population[i].chromosome = (double *)malloc(dimension * sizeof(double));
        for (int j = 0; j < dimension; j++)
        {
            population[i].chromosome[j] = random_double(domain_function.min, domain_function.max);
        }
        population[i].fitness = 100000000;
    }

    // DEBUG(print_population(population, n_populacoes, dimension););
    return population;
}

// calcula a probabilidade para cada populacao de ser escolhida para cruzamento, guardando o intervalo
void calcula_percentPai(individue *populacao, int TAM_P)
{
    DEBUG(printf("\ncalcula_percentPai\n"););
    float total = 0, porcentPai = 0, acumula = 0;
    for (int i = 0; i < TAM_P; i++)
    {
        total += populacao[i].fitness;
    }

    for (int i = TAM_P - 1; i >= 0; i--)
    {
        populacao[i].inter_Pai_inicio = acumula;
        acumula += populacao[i].fitness / total;
        populacao[i].inter_Pai_fim = acumula;
    }
}

int sorteiaPai(individue *populacao, int TAM_P)
{
    DEBUG(printf("\nsorteiaPai\n"););
    float aleatorio = (rand() % 100) / 100.0;
    int indice = 0;
    for (int j = 0; indice < 0; j++)
    {
        if (aleatorio >= populacao[j].inter_Pai_inicio && aleatorio <= populacao[j].inter_Pai_fim)
            return j;
    }
    return indice;
}

void reproducao(individue *populacao, int TAM_P, int dimensao)
{
    DEBUG(printf("\nreproducao\n"););
    int pai, mae, pontoTroca;
    calcula_percentPai(populacao, TAM_P);

    for (int j = TAM_P; j < TAM_P * 2; j++)
    {
        pai = sorteiaPai(populacao, TAM_P);
        mae = sorteiaPai(populacao, TAM_P);
        while (pai == mae)
        {
            mae = sorteiaPai(populacao, TAM_P);
            if (pai == 0)
                mae = rand() % TAM_P;
        }
        pontoTroca = rand() % dimensao;
        // pontoTroca = dimensao/2;
        //   Primeiro for: pega parte dos genes do pai, no Segundo for: pega o restante da mae
        for (int i = 0; i < pontoTroca; i++)
        {
            populacao[j].chromosome[i] = populacao[pai].chromosome[i];
        }

        for (int i = pontoTroca; i < dimensao; i++)
        {
            populacao[j].chromosome[i] = populacao[mae].chromosome[i];
        }
    }
}

void mutacao(individue *populacao, int TAM_PF, int dimensao, domain domain_function)
{
    DEBUG(printf("\nmutacao\n"););
    int sofreuM, pontoM, posicao, *vetAux, taxa, TAM_P = TAM_PF / 2;

    vetAux = (int *)malloc(TAM_PF * sizeof(int));
    zeraVetor(vetAux, TAM_PF);
    taxa = TAM_P * 0.04;

    if (!taxa)
        taxa = 1;

    for (int i = 0; i < taxa; i++)
    {
        sofreuM = (rand() % TAM_PF);
        while (vetAux[sofreuM] == 1 && taxa < TAM_PF)
            sofreuM = (rand() % TAM_PF);
        pontoM = rand() % dimensao;

        populacao[sofreuM].chromosome[pontoM] = random_double(domain_function.min, domain_function.max);

        vetAux[sofreuM] = 1;
    }
    // calcula_dados(populacao, itens, TAM_PF, dimensao, beneficio_peso);
    // free(vetAux);
}

void controle_populacao(individue *populacao, int TAM_PF, int dimensao, domain dominio)
{
    DEBUG(printf("\ncontrole_populacao\n"););
    int cont = 0;
    float taxa;
    maxLocal = 0;
    // verifica se atingiu ou quase atingiu o maximo local
    for (int j = 0; j < TAM_PF; j++)
    {
        if (populacao[j].fitness == populacao[TAM_PF].fitness)
            maxLocal++;
    }
    taxa = maxLocal / (float)(TAM_PF);
    DEBUG(printf("taxa: %f", taxa););
    if (taxa > 0.8)
    {
        int indice, posicao, cont = 5;

        while (cont)
        {
            for (int i = 0; i < TAM_PF; i++)
            {
                indice = rand() % dimensao;
                populacao[i].chromosome[indice] = random_double(dominio.min, dominio.max);
            }
            cont--;
        }
        calcula_dados(populacao, TAM_PF, dimensao);
    }
}

void trataMelhor(individue *populacao, int TAM_P, int dimensao)
{
    DEBUG(printf("\ntrataMelhor\n"););
    int indice = -1, aux, posicao1, posicao2, indice_M = TAM_P * 2;
    // pega indice do maior beneficio
    for (int j = 0; j < TAM_P; j++)
    {
        if (populacao[j].fitness >= populacao[indice_M].fitness)
        {
            indice = j;
            j = TAM_P;
        }
    }

    if (populacao[indice].fitness != populacao[indice_M].fitness && indice != -1)
    {
        // printf("\nPosicao1:%d, posicao2:%d, dimensao:%d\n", indice,indice_M, dimensao);
        posicao1 = indice;
        posicao2 = indice_M;
        populacao[posicao2] = populacao[posicao1];
    }

    if (indice == -1)
    {
        posicao1 = (TAM_P - 1);
        posicao2 = indice_M;
        populacao[posicao1] = populacao[posicao2];

        // printf("\nIndiceM:%d, posicaoM:%d\n", indice_M, posicao2);
    }
}
void evolucao_genetica(int dimensao, domain dominio)
{
    int TAM_P = 5;                       // 50
    int parada = 500, TAM_PF = TAM_P * 2; // 1000
    individue *populacao;
    // alocando com o dobro de tamanho por conta da etapa de reproducao que ira dobrar a populacao, +1 pois na ultima posica oestara o melhor resultado atual de cada iteracao
    populacao = generate_population(TAM_PF, dimensao, dominio);
    while (parada)
    {
        DEBUG(printf("--------------------Geração %d--------------------", parada););
        reproducao(populacao, TAM_P, dimensao);
        mutacao(populacao, TAM_PF, dimensao, dominio);

        controle_populacao(populacao, TAM_PF, dimensao, dominio);
        calcula_dados(populacao, TAM_PF, dimensao);
        Ordena_Populacao(populacao, TAM_P, dimensao);

        trataMelhor(populacao, TAM_P, dimensao);
        calcula_dados(populacao, TAM_PF + 1, dimensao);
        Ordena_Populacao(populacao, TAM_P, dimensao);
        parada--;
    }
    calcula_dados(populacao, TAM_PF, dimensao);
    Ordena_Populacao(populacao, TAM_P, dimensao);
    printf("\n\nMelhor Resultado pelo evolutivo:");
    printf("Benefico:%.4lf\n", populacao[0].fitness);
    // printVet(populacao, dimensao);
    // printf("\n\nPopulacao final:\n");
    // print_populacao(populacao, TAM_P, dimensao, beneficio_peso);
}

int main(int argc, char *argv[])
{
    // srand(time(NULL));
    evolucao_genetica(10, (domain){-100, 100});
}
// comando em linha de comando para processar todas as instancias
// for i in instances_01_KP/large_scale/*; do echo -e "Instancia: $i\n"; ./genetica $i; echo -e "----------------\n"; done > output.txt