set terminal png size 1280,720 enhanced font "Helvetica,20"
set output './output/population_evolution_per_generation.png'
set title "Evolução da população através das gerações"
set xlabel "Geração"
set ylabel "Fitness do individuo"
plot "../../statistics/coords.dat" pt 7
