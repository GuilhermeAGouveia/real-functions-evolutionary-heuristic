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

#ifndef TYPES_H
#define TYPES_H

typedef struct individue_
{
    double *chromosome;
    double fitness;
    float inter_Pai_inicio;
    float inter_Pai_fim;
} individue;


typedef struct population_
{
    individue *individues;
    int size;
    struct population_ **neighbours;

} population;

typedef struct domain
{
    double min;
    double max;
} domain;

#endif /* TYPES_H */
