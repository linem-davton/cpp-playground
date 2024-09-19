#include <benchmark/benchmark.h>
#include <matrices.h>

static void BM_MatrixCreation(benchmark::State &state) {
  const int N = state.range(0);
  for (auto _ : state) {
    mat::generateRandomMatrix({N, N}, {1, 99});
  }
}

static void BM_MatrixMul(benchmark::State &state) {
  const int N = state.range(0);
  mat::MatrixInt A = mat::generateRandomMatrix({N, N}, {1, 99});
  mat::MatrixInt B = mat::generateRandomMatrix({N, N}, {1, 99});
  for (auto _ : state) {
    mat::matrixMultiply(A, B, {N, N}, {N, N});
  }
}
BENCHMARK(BM_MatrixCreation)
    ->Arg(100)
    ->Arg(200)
    ->Arg(500)
    ->Unit(benchmark::kMicrosecond); // Example sizes 100x100, 200x200, 500x500

BENCHMARK(BM_MatrixMul)
    ->RangeMultiplier(2) // Multiply range by 2
    ->Range(32, 1024)    // Matrix sizes from 32x32 to 1024x1024, steps of 2
    ->Unit(benchmark::kMillisecond); // Time unit is millisecond

BENCHMARK_MAIN();
