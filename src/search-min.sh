#!/usr/bin/env bash

# Options
n_execucoes=10 # Default value
function_number=3 # Default value
time_limit=10 # Default value
usage() { echo "Usage: $0 [-n <Numero de execuções>] [-f <Numero da função de teste de 1 a 15>] [-t <Tempo máximo de cada execução>]" 1>&2; exit 1; }

while getopts ":n:f:t:" o; do
    case "${o}" in
        n)
            n_execucoes=${OPTARG}
            ;;
        f)
            function_number=${OPTARG}
            ;;
        t)
            time_limit=${OPTARG}
            ;;
        *)
            usage
            ;;
    esac
done
shift $((OPTIND-1))

# Math

# Function to calculate the mean of an array
# Usage: mean "${array[@]}"
mean() {
    local sum=0
    local count=0
    for i in "$@"; do
        sum=$(echo "$sum + $i" | bc)
        count=$(echo "$count + 1" | bc)
    done
    echo "$sum / $count" | bc -l
}

# Function to calculate the standard deviation of an array
# Usage: std "${array[@]}"
std() {
    local mean=$(mean "$@")
    local sum=0
    local count=0
    for i in "$@"; do
        sum=$(echo "$sum + ($i - $mean)^2" | bc)
        count=$(echo "$count + 1" | bc)
    done
    echo "sqrt($sum / $count)" | bc -l
}

# Main code

clean_line() { printf "\r"; }
mount_progress_bar() {
    local progress=$1
    clean_line
    set_color_progress $progress
    progress-bar $progress
}
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

make
clear
source libs/progress-bar/progress-bar.sh
echo -e "Buscando em ${n_execucoes} execuções para função ${function_number}...\n"
tput civis

resultado=0

minimo=10000000000
valor_atual=0
maximo=0

array_values=()

semente=0

vertical_center=$((($(tput lines) - 3 )/ 2))
for i in $(seq 1 $vertical_center); do
    printf "\n"
done

mount_progress_bar 0 $n_execucoes
for i in $(seq 1 $n_execucoes); do
    resultado=$(./evol 10 5 200 $function_number $time_limit)
    semente_atual=$(echo $resultado | grep Semente | cut -d' ' -f2)
    valor_atual=$(echo $resultado | grep Fitness | cut -d' ' -f15)
    array_values+=($valor_atual)
    if (( $(echo "$minimo > $valor_atual" | bc -l) )); then
        minimo=$valor_atual
        semente=$semente_atual
    fi

    if (( $(echo "$maximo < $valor_atual" | bc -l) )); then
        maximo=$valor_atual
    fi

    mount_progress_bar $((i*100/n_execucoes))

done;
clean_line
tput reset
tput setaf 2
echo -e "\nResultado para função $function_number:\n"
echo "Semente do menor: $semente"
echo "Minimo: $minimo"
echo "Maximo: $maximo"
echo "Média: $(mean "${array_values[@]}")"
echo "Desvio padrão: $(std "${array_values[@]}")"