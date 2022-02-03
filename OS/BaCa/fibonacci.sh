#!/usr/bin/env sh

read N

n1=0
n2=1
i=0

if [ $N -eq 1 ]; then
    echo $n1
else
    while [ $i -lt $N ]; do
        echo $n1
        nth=$((n1+n2))
        n1=$n2
        n2=$nth
        i=$((i+1))
    done
fi
