#!/usr/bin/env sh

dir="$(dirname $(realpath $0))"

if [ "$1" = "-d" ]; then
    rm -rf "$dir"/build "$dir"/bin
fi

if [ -f "$dir/include/staticMatrix.h" -a -f "$dir/include/dynamicMatrix.h" ]; then
    mkdir -p "$dir"/build \
        && cd "$dir"/build \
        && cmake "$dir" \
        && cmake --build . --parallel \
        && ctest
else
    echo "There is no file staticMatrix.h or dynamicMatrix.h in include/ directory of project root!"
fi
