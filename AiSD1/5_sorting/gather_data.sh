#!/usr/bin/env sh

algs="$1"
sizes="10 25 50 75 100 250 500 750 1000 2500 5000 7500 10000 25000 50000 75000 100000"

for alg in $algs; do
    echo "$alg"
    echo "x y" > data/"$alg".txt
    for size in $sizes; do
        echo "  $size"
        ./Generator.x "$size" | ./"$alg".x 0 >> data/"$alg".txt
    done
done
