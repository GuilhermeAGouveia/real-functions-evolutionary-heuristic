int roleta_pais(individue *populacao, int nPopulacoes)
{
    int roleta[100000];
    double beneficioTodosIndividuos = 0;
    for (int i = 0; i < nPopulacoes; i++)
    {
        beneficioTodosIndividuos += populacao[i].fitness;
    }

    int base = 0;
    for (int i = 0; i < nPopulacoes; i++)
    {
        int beneficioIndividuo = populacao[i].fitness;
        int limit = ceil((double)(beneficioTodosIndividuos - beneficioIndividuo) / (double)beneficioTodosIndividuos * 100.00);
        for (int j = base; (j < base + limit); j++)
        {
            roleta[j] = i;
        }
        base += limit;
    }
    return roleta[rand() % 100];
}


void select_parents(individue *populacao, int n_populacoes, int *parents)
{
    int pai1 = roleta_pais(populacao, n_populacoes), pai2;
    do {
        pai2 = roleta_pais(populacao, n_populacoes);
    } while (pai1 == pai2);
    parents[0] = pai1;
    parents[1] = pai2;
}
