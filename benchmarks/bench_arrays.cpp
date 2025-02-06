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

BENCHMARK(BM_BinarySearch)->RangeMultiplier(10)->Range(100, 100 << 20)->Unit(benchmark::kMicrosecond);  // Array Sizes 100, 200, 500
BENCHMARK(BM_BinaryJumpSearch)->Arg(100)->Arg(200)->Arg(500)->Unit(benchmark::kMicrosecond);            // Example sizes 100x100, 200x200, 500x500
BENCHMARK(BM_StdFind)->Arg(100)->Arg(200)->Arg(500)->Unit(benchmark::kMicrosecond);                     // Example sizes 100x100, 200x200, 500x500

BENCHMARK_MAIN();
