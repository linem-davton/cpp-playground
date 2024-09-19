#!/bin/bash

# run benchmarks for all build presets
#set -eo pipefail

benchmarks_executable=("bench_matrix")
build_presets=("debug" "debug-sanitize" "release" "release-lto" "release-sanitize")

for preset in "${build_presets[@]}"; do
  echo -e "\n\n\033[1;32mBechmarking for preset: $preset \033[0m"
  for benchmark in "${benchmarks_executable[@]}"; do
    ./build/$preset/bin/$benchmarks_executable
  done
done
