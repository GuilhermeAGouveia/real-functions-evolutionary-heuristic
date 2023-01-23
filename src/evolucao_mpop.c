#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG(x) x

typedef struct city
{
    int id;
    float x;
    float y;
} type_city;

void print_cidades(type_city *cidades, int n_cidades)
{
    for (int i = 0; i < n_cidades; i++)
        printf("%d %f %f", cidades[i].id, cidades[i].x, cidades[i].y);
}

type_city *read_cidades(char *filename, int *n_cidades, int *capacidad)
{
    void *tmp;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        puts("Couldn't open file");
        exit(0);
    }

    for (int i = 0; i < 3; i++)
        fgets(tmp, 100, fp);
 
    DEBUG(puts("aqui1"));
    sprintf(tmp, "DIMENSION: %d", n_cidades);
    for (int i = 0; i < 2; i++)
        fgets(tmp, 100, fp);
    DEBUG(printf("Número de elementos: %d\n", *n_cidades));

    type_city *cidades = (type_city *)malloc(*n_cidades * sizeof(type_city));

    for (int i = 0; i < *n_cidades; i++)
    {
        fscanf(fp, "%f %f", &cidades[i].x, &cidades[i].y);
        cidades[i].id = i;
    }

    fclose(fp);

    return cidades;
}

int main(int argc, char *argv[])
{
    int n_cidades, capacidad;

    if (argc != 2)
    {
        printf("Uso: %s <nome do arquivo de entrada>", argv[0]);
        return 1;
    }

    type_city *cidades = read_cidades(argv[1], &n_cidades, &capacidad);

    print_cidades(cidades, n_cidades);
    free(cidades);
    return 0;
}