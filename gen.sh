#!/bin/bash

set -eu

mkdir -p data

g++ gen.cpp -O2 -std=c++23 -o gen

N=100

for ((i=1;i<=N;i++)); do
    ./gen "$i" > data/$(printf "%03d.in" "$i")
done

echo "Generated $N testcases."
