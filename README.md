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

- [CMake](CMake.md)Presets.json defines various debug and release configurations, including the compiler flags.
- `scripts` directory contains scripts to build, test, and benchmark the project.

```BASH
git clone git@github.com:linem-davton/cpp-playground.git
cd cpp-playground
mkdir build
./scripts/install_dep.sh # install dependencies
./scripts/build.sh # build the project
./scripts/test_all.sh # run all tests
./scripts/bench_all.sh # run all benchmarks , can be time consuming

```

The executables are generated in the build/{preset}/bin directory.

## Requirements

[Install Script](install_dep.sh) installs the following requirements (apt package manager).
Perf is not available on WSL2. Works on native Linux.

- [CMake](https://cmake.org/)
- [GCC](https://gcc.gnu.org/)
- [GDB](https://www.gnu.org/software/gdb/)
- [Ninja](https://ninja-build.org/)
- [Google Test](https://google.github.io/googletest/)
- [Google Benchmark](https://github.com/google/benchmark)
- [Heaptrack](https://github.com/KDE/heaptrack)
- [lcov](http://ltp.sourceforge.net/coverage/lcov.php)
- [Perf](https://docs.kernel.org/arch/arm64/perf.html#perf)
- [Strace](https://man7.org/linux/man-pages/man1/strace.1.html)

## Adding Executables

Place the header files in the `include` directory.
Place the source files in the `src` directory, or in a new subdirectory in the `src` directory.
Configure CMake by Adding the following to the CMakeLists.txt file in `src` dir to build the executable.

```cmake
add_executable(a.out a.cpp) # add executable
target_link_libraries(a.out PRIVATE <libs>) # link libraries
```

## Adding Libraries

Add header files in the `include` directory.
Place the source files in a new subdirectory in the `src` directory.
Configure CMake by Adding the following to the CMakeLists.txt file in the new subdirectory to build the library.

```CMake
add_library(lib_name STATIC lib.cpp <other.cpp>) # <other.cpp> is placeholder for other source files
```

## Adding Tests

The project uses Google Test for testing. Place the test files in the `tests` directory.
Add the following to the CMakeLists.txt file in the `tests` directory to build the test.

```CMake
add_executable(test_name test.cpp) # add test
target_link_libraries(test_name PRIVATE <libs> GTest::gtest_main) # <libs> is place holder for other libs
```

## Adding Benchmarks

The project uses Google Benchmark for benchmarking. Place the benchmark files in the `benchmarks` directory.
Add the following to the CMakeLists.txt file in the `benchmarks` directory to build the benchmark.

```CMake
add_executable(benchmark_name benchmark.cpp) # add benchmark
target_link_libraries(benchmark_name PRIVATE <libs> benchmark::benchmark) # <libs> is place holder for other libs
```

- Add the benchmark to the list of benchmarks in `bench_all.sh` script.

## Performance

### Perf

I have not be able to get perf to work on WSL2. Works on native Linux.

```BASH
perf stat ./matrices # get performance statistics
perf stat -e cache-references,cache-misses,LLC-loads,LLC-load-misses ./matrices # get cache statistics
```

Sample perf stat outputs for matrix multiplication, in the [matrices](docs/matrices.md) directory.

#### Call Graph

Build with `-fno-omit-frame-pointer` to disable frame pointer optimization, to make call graphs more accurate.(Not tested if disabling frame pointer optimization affects the call graph accuracy.)

```BASH
# Call graph
perf record --call-graph dwarf -F 99 ./a.out # record call graph
perf script | speedscope -  # Vizualize the call graph and flame graph
```

Perf benchmarks for matrix multiplication are available in the [matrices](docs/matrices.md) directory.

Speedscope: https://www.speedscope.app/

### Strace

```BASH
strace ./a.out # trace system calls
strace -c ./a.out # get summary of system calls
strace -f ./a.out # trace child processes
strace -e trace=open,close ./a.out # trace only open and close system calls
strace -e trace=network ./a.out # trace only network system calls
strace -k ./a.out # print call stack
```

### Heaptrack

```BASH
sudo apt install heaptrack
```

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
