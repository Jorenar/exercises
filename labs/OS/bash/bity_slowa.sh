#!/usr/bin/env sh

w=$(getconf LONG_BIT)

n=$(echo "(2^($w-1)-1)" | bc)

echo "Długość słowa:      $w"
echo "Największa liczba:  $n"
echo "Najmniejsza liczba: $((n+1))"
