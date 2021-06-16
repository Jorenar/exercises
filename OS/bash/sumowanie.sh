#!/usr/bin/env sh

grep -o '\ [0-9]\+\>' | paste -sd+ | bc
