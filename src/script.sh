#!/usr/bin/env bash
clean_line() { printf "\r"; }
set_color_progress() {
    if (( $1 < 25 )); then
        tput setaf 1
    elif (( $1 < 50 )); then
        tput setaf 3
    elif (( $1 < 75 )); then
        tput setaf 3
    else
        tput setaf 4
    fi
}
resultado=0
minimo=10000000000
minimo_atual=0
semente=0
limit=10
make
source libs/progress-bar.sh/progress-bar.sh
clear
echo -e "Buscando...\n"
tput civis
vertical_center=$((($(tput lines) - 3 )/ 2))
for i in $(seq 1 $vertical_center); do
    printf "\n"
done
for i in $(seq 1 $limit); do
    set_color_progress $((i*100/limit))
    progress-bar $i $limit

    resultado=$(./evol)
    semente_atual=$(echo $resultado | grep Semente | cut -d' ' -f2)
    minimo_atual=$(echo $resultado | grep Fitness | cut -d' ' -f15)
    if (( $(echo "$minimo > $minimo_atual" | bc -l) )); then
        minimo=$minimo_atual
        semente=$semente_atual
    fi
    printf "\r";

done;
tput reset
tput setaf 2
echo -e "\nResultado:\n"
echo "Semente: $semente"
echo "Fitness: $minimo"
