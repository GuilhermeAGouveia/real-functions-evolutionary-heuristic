#!/bin/bash
dimension=0
for i in instances/vlsi_tsp/*.tsp; do
    dimension=$(cat $i | grep DIMENSION | cut -d' ' -f3)
    if [ $dimension -gt 10000 ]; then
        mv $i instances/vlsi_tsp/big
    else
        mv $i instances/vlsi_tsp/small 
    fi
done