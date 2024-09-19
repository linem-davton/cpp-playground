#!/bin/bash

# exit on error, expand variables, and show commands being run, error if any command in pipeline fails
set -eo pipefail

# List of test presets
test_presets=("test-debug" "test-debug-sanitize" "test-release" "test-release-lto" "test-release-sanitize")

# Loop through each test preset and run tests
for preset in "${test_presets[@]}"; do
    echo -e "\033[1;32mRunning tests for preset: $preset \033[0m"
    ctest --preset=$preset
    if [ $? -ne 0 ]; then
        echo -e "\033[1;31mTests failed for preset: $preset\033[0m"
        exit 1
    fi
done

echo -e "\033[1;32mAll tests completed successfully.\033[0m"
