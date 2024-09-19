# CPP Playground

- [Getting Started](#getting-started)
- [Requirements](#requirements)
- [Performance](#performance)
  - [Perf](#perf)
  - [Heaptrack](#heaptrack)
  - [lcov](#lcov)
  - [Google Benchmark](#google-benchmark)
- [Testing](#testing)
  - [Google Test](#google-test)
- [Documentation](#documentation)
- [References](#references)

## Getting Started

- Make a buld directory and run cmake to generate the build files.
- [CMake](CMake.md)Presets.json defines various debug and release configurations, including the compiler flags.

```BASH
mkdir build
cmake --preset=debug
cmake --build --preset=debug # uses ninja as the build tool
```

The executable is generated in the build/{preset}/src directory.

## Requirements

- [CMake](https://cmake.org/)
- [GCC](https://gcc.gnu.org/)
- [Ninja](https://ninja-build.org/)
- [Google Test](https://google.github.io/googletest/)
- [Google Benchmark](https://github.com/google/benchmark)
- [Heaptrack](https://github.com/KDE/heaptrack)
- [lcov](http://ltp.sourceforge.net/coverage/lcov.php)
- [Perf](https://docs.kernel.org/arch/arm64/perf.html#perf)
- [Strace](https://man7.org/linux/man-pages/man1/strace.1.html)

## Performance

### Perf

Build with `-fno-omit-frame-pointer` to disable frame pointer optimization, to make call graphs more accurate.(Not tested if disabling frame pointer optimization affects the call graph accuracy.)

```BASH
perf stat ./matrices # get performance statistics
perf stat -e cache-references,cache-misses,LLC-loads,LLC-load-misses ./matrices # get cache statistics

# Call graph
perf record --call-graph dwarf -F 99 ./a.out # record call graph
perf script | speedscope -  # Vizualize the call graph and flame graph
```

Perf benchmarks for matrix multiplication are available in the [matrices](docs/matrices.md) directory.

Speedscope: https://www.speedscope.app/

### Strace

```
strace ./a.out # trace system calls
strace -c ./a.out # get summary of system calls
strace -f ./a.out # trace child processes
strace -e trace=open,close ./a.out # trace only open and close system calls
strace -e trace=network ./a.out # trace only network system calls
strace -k ./a.out # print call stack
```

### Heaptrack

```BASH
heaptrack ./a.out # get heap memory statistics
heaptrack --analyze heaptrack*.zst # analyze the heap memory statistics
```

Heaptrack is a heap memory profiler that tracks all memory allocations and de-allocations in a program. Gui is available in the heaptrack-gui package.

### lcov

To see how many times a line was executed in the program.
Must compile with `--coverage` flag.

```BASH
g++ a.cpp -o a.out --coverage
./a.out # generates coverage file , .gcda
lcov --capture --directory . --output-file coverage.info # Capture coverage data from curr and sub dirs
genhtml coverage.info --output-directory out # generate html report
google-chrome out/index.html # open the html repor
```

### Google Benchmark

Google Benchmark is a microbenchmark library for C++. Test performance of functions.

```BASH
./matrices_benchmark --benchmark_filter=BM_MatrixMul # run only the benchmark with the name BM_MatrixMul
```

## Testing

### Google Test

Setting up [GTest with CMake](https://google.github.io/googletest/quickstart-cmake.html)

Configure CMakeLists.txt to use GTest.

```cmake
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing() # set at the top level CMakeLists.txt to generate CTestTestfile.cmake in correct directory
```

To build tests, add the following to CMakeLists.txt.

```cmake
# first test
add_executable(test_matrix test_matrix.cpp)
target_link_libraries(test_matrix PRIVATE matrices GTest::gtest_main)
# second test

include(GoogleTest)
gtest_discover_tests(test_matrix)
```

To run the tests, use the following command.

```bash
ctest --test-dir build/debug/tests # the location of CTestTestfile.cmake
ctest --preset=debug -V # run all tests
```

## Documentation

Detailed documentation is available in the [docs](docs) directory.

## References

- [Observability Tools](https://www.youtube.com/watch?v=C9vmS5xV23A)
- [Perf](https://www.brendangregg.com/perf.html)
- [Google Test](https://google.github.io/googletest/)
- [Google Benchmark](https://github.com/google/benchmark)
