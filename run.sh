#!/bin/bash

set -eu

g++ judge.cpp -std=c++23 -O2 -o judge
g++ solve.cpp -std=c++23 -O2 -o solve

passed=0
total=0

for infile in $(find data -name "*.in" | sort); do
    echo "===== $infile ====="

    if python3 reactive.py "$infile"; then
        echo "PASS"
        passed=$((passed + 1))
    else
        echo "FAIL"
    fi

    total=$((total + 1))
    echo
done

echo "$passed / $total passed."
