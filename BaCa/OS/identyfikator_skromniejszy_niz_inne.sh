#!/usr/bin/env bash

declare -A count

read w
count[$w]=1
list=$w

while read x; do
    (( count[$x]++ ))
    [ ${count[$x]} = 1 ] && list="$list $x"
done

m=${count[$w]}

for x in $list; do
    [ ${count[$x]} -lt $m ] && m=${count[$x]} && w=$x
done

echo "$w $m"

# awk                                \
# '                                  \
#     BEGIN { b=0 }                  \
#                                    \
#     {                              \
#         if (!a[$0]++) {            \
#             s[b++]=$0              \
#         }                          \
#     }                              \
#                                    \
#     END {                          \
#         m=s[0];                    \
#         for (i in s) {             \
#             if (a[s[i]] < a[m]) {  \
#                 m=s[i]             \
#             }                      \
#         }                          \
#         print m, a[m]              \
#     }                              \
# '
