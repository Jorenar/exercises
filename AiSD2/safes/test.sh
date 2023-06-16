#!/usr/bin/env sh

export TIMEFORMAT="Time: %R"

g++ -O3 safes.cpp

ulimit -s unlimited

for f in in/*.txt; do
    printf "\033[1m%s\033[0m\n" "$f"
    c="$(echo ${f%%.*} | cut -d_ -f2)"

    r="$(time ./a.out < $f)"

    if [ "$r" = "$c" ]; then
        printf "\033[32mPASS\033[0m"
    else
        printf "\033[91mERROR\033[0m: %s" "$r != $c"
    fi
    printf "\n\n"
done
