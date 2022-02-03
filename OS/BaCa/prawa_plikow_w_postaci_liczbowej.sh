#!/usr/bin/env sh

read -r line # disregard 'total N'
while IFS= read -r line; do
    ext=
    if [ "$(echo $line | cut -c1)" != "l" ]; then
        [ "$(echo $line | cut -c4)" = "x" ] && ext='*'
        [ "$(echo $line | cut -c1)" = "d" ] && ext='/' # override exe with dir
    fi

    a=0
    b=0
    c=0

    [ "$(echo $line | cut -c2)" = "r" ] && a=$((a+4))
    [ "$(echo $line | cut -c3)" = "w" ] && a=$((a+2))
    [ "$(echo $line | cut -c4)" = "x" ] && a=$((a+1))

    [ "$(echo $line | cut -c5)" = "r" ] && b=$((b+4))
    [ "$(echo $line | cut -c6)" = "w" ] && b=$((b+2))
    [ "$(echo $line | cut -c7)" = "x" ] && b=$((b+1))

    [ "$(echo $line | cut -c8)" = "r" ] && c=$((c+4))
    [ "$(echo $line | cut -c9)" = "w" ] && c=$((c+2))
    [ "$(echo $line | cut -c10)" = "x" ] && c=$((c+1))

    echo "$line" | awk -v e=$ext -v p=$a$b$c '{ printf("%s%s %s\n", $9, e, p) }'

#    line="$(echo $line | awk -F' -> ' '{print $1}')$ext"
#    echo "$line" | awk '{out=""; for(i=9;i<=NF;i++){out=out$i" "}; printf("%s", out); \
#        k=0;for(i=0;i<=8;i++)k+=((substr($1,i+2,1)~/[rwx]/)*2^(8-i));if(k)printf("%0o\n",k)}'
done
