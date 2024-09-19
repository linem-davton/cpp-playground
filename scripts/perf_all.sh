#!/bin/bash


# perf all benchmarks for all build presets
#
executables=("bench_matrix" "fib" "jthreads" "macros matrix" "test_matrix")

build_presets=("debug" "debug-sanitize" "release" "release-lto" "release-sanitize")

for preset in "${build_presets[@]}"; do
  echo -e "\n\n\033[1;32mPerf for preset: $preset \033[0m"
  for executable in "${executables[@]}"; do
    sudo perf stat -e task-clock,cycles,instructions,branches,branch-misses \
    -e cache-references,cache-misses,LLC-loads,LLC-load-misses \
    -e page-faults,context-switches,cpu-migrations \
    ./build/$preset/bin/$executable > /dev/null
  done
done
