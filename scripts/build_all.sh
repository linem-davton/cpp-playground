#!/bin/bash

# exit on error, expand variables, and show commands being run, error if any command in pipeline fails
set -eo pipefail

# --- choose presets ---------------------------------------------------------
if (( $# == 0 )); then                       # no args → default list
    build_presets=(debug debug-sanitize release release-lto release-sanitize)
else                                         # args → use exactly what was passed
    build_presets=("$@")                     # supports one or many arguments
fi
# ----------------------------------------------------------------------------


# Declare an array to hold the PIDs
declare -a pids

for preset in "${build_presets[@]}"; do
    echo -e "\033[1;32mBuilding for preset: $preset \033[0m"
    cmake --preset=$preset && cmake --build --preset=$preset &
    pids+=($!) # Save the PID of the last background process

done

# Wait for all background processes to finish
for pid in "${pids[@]}"; do
    if ! wait $pid; then
        echo -e "\033[1;31mBuild failed for one of the presets. \033[0m"
        exit 1
    fi
done

echo -e "\033[1;32mAll configs built successfully.\033[0m"
