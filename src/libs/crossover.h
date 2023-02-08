typedef enum
{
    MEDIA,
    MEDIA_GEOMETRICA,
    METADE,
    PONTO,
    FLAT,
    BLEND,
} crossover_type;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lista.h
 * Author: Guilherme Gouveia
 *
 * Created on January 26, 2021, 11:32 AM
 */
#ifndef CROSSOVER_H
#include "types.h"
#define CROSSOVER_H


individue cruzamento_media(individue parent1, individue parent2, int n_itens);
individue cruzamento_flat(individue parent1, individue parent2, int n_itens);
individue cruzamento_blend(individue parent1, individue parent2, int n_itens);
individue cruzamento_metade(individue parent1, individue parent2, int n_itens);
individue cruzamento_ponto(individue parent1, individue parent2, int n_itens);

#endif /* CROSSOVER_H */
