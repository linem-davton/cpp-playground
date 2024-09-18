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
    ->Arg(500); // Example sizes 100x100, 200x200, 500x500

BENCHMARK(BM_MatrixMul)
    ->RangeMultiplier(2)
    ->Range(32, 1024) // Matrix sizes 100x100 to 500x500
    ->Unit(benchmark::kMillisecond);

// Or a range of values for sizes
// BENCHMARK(BM_MatrixCreation)->RangeMultiplier(2)->Range(64, 512);  // Matrix
// sizes 64x64 to 512x512 BENCHMARK(BM_MatrixMul)->RangeMultiplier(2)->Range(64,
// 512);

BENCHMARK_MAIN();
