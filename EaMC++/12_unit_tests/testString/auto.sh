#!/usr/bin/env sh

dir="$(dirname $(realpath $0))"

if [ "$1" = "-d" ]; then
    rm -rf "$dir"/build "$dir"/bin
fi

if [ -f "$dir/src/String.cpp" ]; then
    mkdir -p "$dir"/build \
        && cd "$dir"/build \
        && cmake "$dir" \
        && cmake --build . --parallel \
        && ctest
else
    echo "There is no file String.cpp in src/ directory of project root!"
fi
