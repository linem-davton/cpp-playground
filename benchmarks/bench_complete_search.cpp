
#include <benchmark/benchmark.h>
#include <algorithm>
#include "array_utils.h"
#include "complete_search.h"

static void BM_NextPermutation(benchmark::State &state) {
    const int size = state.range(0);
    auto vec = random_vector<int>(size);
    std::sort(vec.begin(), vec.end());

    for (auto _ : state) {
        nextPermutation(vec);
    }
}

static void BM_STDNextPermutation(benchmark::State &state) {
    const int size = state.range(0);
    auto vec = random_vector<int>(size);
    std::sort(vec.begin(), vec.end());

    for (auto _ : state) {
        std::next_permutation(vec.begin(), vec.end());
    }
}

// Register the function to be benchmarked, with params.

// Complete Search
BENCHMARK(BM_NextPermutation)->RangeMultiplier(10)->Range(10, 10 << 12)->Unit(benchmark::kMicrosecond);     // Array Sizes 100, 200, 500
BENCHMARK(BM_STDNextPermutation)->RangeMultiplier(10)->Range(10, 10 << 12)->Unit(benchmark::kMicrosecond);  // Array Sizes 100, 200, 500
BENCHMARK_MAIN();
