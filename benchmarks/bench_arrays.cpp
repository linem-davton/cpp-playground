#include <benchmark/benchmark.h>
#include <algorithm>
#include "array_utils.h"
#include "search_array.h"

static void BM_BinarySearch(benchmark::State &state) {
    const int size = state.range(0);
    auto vec = random_vector<int>(size);
    int val = vec[3];
    std::sort(vec.begin(), vec.end());
    for (auto _ : state) {
        binary_search(vec, val);
    }
}

static void BM_BinaryJumpSearch(benchmark::State &state) {
    const int size = state.range(0);
    auto vec = random_vector<int>(size);
    int val = vec[3];
    std::sort(vec.begin(), vec.end());
    for (auto _ : state) {
        binary_jump_search(vec, val);
    }
}

static void BM_StdFind(benchmark::State &state) {
    const int size = state.range(0);
    auto vec = random_vector<int>(size);
    int val = vec[3];
    std::sort(vec.begin(), vec.end());
    for (auto _ : state) {
        std::find(vec.begin(), vec.end(), val);
    }
}
static void BM_StdBinarySearch(benchmark::State &state) {
    const int size = state.range(0);
    auto vec = random_vector<int>(size);
    int val = vec[3];
    std::sort(vec.begin(), vec.end());
    for (auto _ : state) {
        std::binary_search(vec.begin(), vec.end(), val);
    }
}

// Register the function to be benchmarked, with params.
BENCHMARK(BM_BinarySearch)->RangeMultiplier(10)->Range(10, 10 << 12)->Unit(benchmark::kMicrosecond);      // Array Sizes 100, 200, 500
BENCHMARK(BM_BinaryJumpSearch)->RangeMultiplier(10)->Range(10, 10 << 12)->Unit(benchmark::kMicrosecond);  // Array Sizes 100, 200, 500
BENCHMARK(BM_StdBinarySearch)->RangeMultiplier(10)->Range(10, 10 << 12)->Unit(benchmark::kMicrosecond);   // Array Sizes 100, 200, 500
BENCHMARK(BM_StdFind)->RangeMultiplier(10)->Range(10, 10 << 12)->Unit(benchmark::kMicrosecond);           // Array Sizes 100, 200, 500

BENCHMARK_MAIN();
