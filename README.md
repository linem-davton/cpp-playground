# CPP Playground

- [Getting Started](#getting-started)
- [Performance](#performance)
  - [Perf](#perf)
  - [Heaptrack](#heaptrack)
- [Documentation](#documentation)
- [References](#references)

## Getting Started

- Make a buld directory and run cmake to generate the build files.
- [CMake](CMake.md)Presets.json defines various debug and release configurations, including the compiler flags.

```BASH
mkdir build
cmake --preset=debug ..
cmake --build --preset=debug # uses ninja as the build tool
```

The executable is generated in the build/{preset}/src directory.

## Performance

### Perf

Build with `-fno-omit-frame-pointer` to disable frame pointer optimization, to make call graphs more accurate.(Not tested if disabling frame pointer optimization affects the call graph accuracy.)

```BASH
perf stat ./matrices # get performance statistics

# Call graph
perf record --call-graph dwarf -F 99 ./a.out # record call graph
perf script | speedscope -  # Vizualize the call graph and flame graph
```

speedscope: https://www.speedscope.app/

### Heaptrack

```BASH
heaptrack ./a.out # get heap memory statistics
heaptrack --analyze heaptrack*.zst # analyze the heap memory statistics
```

Heaptrack is a heap memory profiler that tracks all memory allocations and de-allocations in a program. Gui is available in the heaptrack-gui package.

### Strace

```
strace ./a.out # trace system calls
strace -c ./a.out # get summary of system calls
strace -f ./a.out # trace child processes
strace -e trace=open,close ./a.out # trace only open and close system calls
strace -e trace=network ./a.out # trace only network system calls
strace -k ./a.out # print call stack
```

### lcov

To see how many times a line was executed in the program.
Must compile with `-coverage` flag.

```BASH
g++ a.cpp -o a.out  -coverage
./a.out # generates coverage file , .gcda
lcov --capture --directory . --output-file coverage.info # Capture coverage data from curr and sub dirs
genhtml coverage.info --output-directory out # generate html report
google-chrome out/index.html # open the html repor
```

## Documentation

Detailed documentation is available in the [docs](docs) directory.

## References

- [Observability Tools](https://www.youtube.com/watch?v=C9vmS5xV23A)
- [Perf](https://www.brendangregg.com/perf.html)
