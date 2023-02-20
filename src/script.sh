#!/usr/bin/env bash
resultado=0
minimo=10000000000
minimo_atual=0
semente=0
limit=10
make
source progress-bar.sh/progress-bar.sh
for i in $(seq 1 $limit); do
    if [ $(expr $i % 3) -eq 0 ]; then
        echo "Procurando."
    fi
    if [ $(expr $i % 3) -eq 1 ]; then
        echo "Procurando.."
    fi
    if [ $(expr $i % 3) -eq 2 ]; then
        echo "Procurando..."
    fi
    
    progress-bar $i
    resultado=$(./evol)
    semente_atual=$(echo $resultado | grep Semente | cut -d' ' -f2)
    minimo_atual=$(echo $resultado | grep Fitness | cut -d' ' -f15)
    if (( $(echo "$minimo > $minimo_atual" | bc -l) )); then
        echo "Novo minimo"
        echo $minimo_atual
        minimo=$minimo_atual
        semente=$semente_atual
    fi
    clear
done;

echo "Semente: $semente"
echo "Fitness: $minimo"