# Writing Google Benchmarks

## Function Benchmarks

By convention the benchmarks functions are named with `BM_` prefix, although not mandatory.
However, each benchmark function must:

1. Accept a `benchmark::State&` parameter.
2. Must return `void`.
3. Loop over `state` parameter using for (auto \_: state).This ensures Google Benchmark controls the number of iterations automatically.
4. Register using `Benchmark(function_name)`, and pass parmaters here (if needed).

> [!Tip]
> To avoid compiler optimizations, wrap the function to be bechmarked with benchmark::DoNotOptimize().

Example:

```Cpp
static void BM_BenchmarkFunction(benchmark::State &state) {
    // Code here runs only once.

    for (auto _ : state) {
    // The code inside the for loop is executed multiple times.
    benchmark::DoNotOptimize(binary_search(vec, val));
}
}
```

## Passing Paramters

`state.range()` can be used to access parameters passed to the benchmark function.

```cpp
// the bechmark function will be called thrice, with following params. Each call be be run multiple iterations.
BENCHMARK(BM_BinarySearch)->Arg(1000)->Arg(10000)->Arg(100000);

// Multiple Params
BENCHMARK(BM_MatrixMultiplication)->Args({100, 100})->Args({500, 500})->Args({1000, 1000});

// Scaling the params within lower and upper bound
BENCHMARK(BM_VectorPushBack)->RangeMultiplier(2)->Range(8, 1024); // Runs with sizes: 8, 16, 32, 64, 128...
```
