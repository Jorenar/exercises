#!/usr/bin/env sh

i=0
s=0

while read n; do
    if [ -n "$n" ]; then
        i=$((i+1))
        N="$N $n"
        s=$((s+n))
    fi
done

a=$((s/i))

s=0

for j in $N; do
    s=$(( s + ($j - $a)*($j - $a) ))
done

echo $a
echo $((s/i))
