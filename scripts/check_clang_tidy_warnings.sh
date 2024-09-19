#!/bin/bash

# Run Clang-Tidy and capture output
clang-tidy src/*.cpp -- -Iinclude -std=c++17 2>&1 | tee clang-tidy-output.txt

# Check for warnings in the output
if grep -q "warning:" clang-tidy-output.txt; then
    echo "Clang-Tidy found warnings:"
    grep "warning:" clang-tidy-output.txt
    exit 1
fi
