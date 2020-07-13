#!/usr/bin/env sh

while read l; do
    l="$(echo $l | sed 's/[^a-zA-Z\ ]//g')"
    for w in $l; do
        [ ${#w} -gt 1 ] && [ "$w" = "$(echo $w | rev)" ] && echo "$w"
    done
done
