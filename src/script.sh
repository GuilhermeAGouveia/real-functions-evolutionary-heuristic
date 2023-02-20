#!/bin/bash

# Executa o comando "./evol" e armazena a saída na variável "output"
output=$(./evol)

# Extrai o melhor resultado da saída usando o comando "grep"
best_result=$(echo "$output" | grep -o 'Melhor resultado: [0-9]*')

# Imprime o melhor resultado
echo "O melhor resultado é $best_result"
