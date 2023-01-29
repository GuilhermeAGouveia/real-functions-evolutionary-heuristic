#!/bin/bash

for i in ./scripts/gnuplot/*.p; do
    echo $i
    gnuplot $i
done