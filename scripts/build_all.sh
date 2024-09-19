#!/bin/bash

# exit on error, expand variables, and show commands being run, error if any command in pipeline fails
set -eo pipefail

build_presets=("debug" "debug-sanitize" "release" "release-lto" "release-sanitize")

for preset in "${build_presets[@]}"; do
    echo -e "\033[1;32mBuilding for preset: $preset \033[0m"
    cmake --preset=$preset
    cmake --build --preset=$preset
    if [ $? -ne 0 ]; then
        echo -e "\033[1;31mBuild failed for preset: $preset \033[0m"
        exit 1
    fi
done

echo -e "\033[1;32mAll configs built successfully.\033[0m"
