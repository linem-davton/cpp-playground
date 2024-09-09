# CPP Playground

- [Getting Started](#getting-started)
- [Performance](#performance)
  - [Perf](#perf)
  - [Heaptrack](#heaptrack)
- [Documentation](#documentation)
- [References](#references)

## Getting Started

- Make a buld directory and run cmake to generate the build files.

```BASH
mkdir build
cd build
cmake ..
make -j6 # 6 threads
```

## Performance

### Perf

Build with `-fno-omit-frame-pointer` to disable frame pointer optimization, to make call graphs more accurate.(Not tested if disabling frame pointer optimization affects the call graph accuracy.)

```BASH
perf stat ./matrices # get performance statistics

# Call graph
perf record --call-graph dwag -F 99 ./a.out # record call graph
perf script | speedscope -  # Vizualize the call graph and flame graph
```

speedscope: https://www.speedscope.app/

### Heaptrack

```BASH
heaptrack ./a.out # get heap memory statistics
heaptrack --analyze heaptrack*.zst # analyze the heap memory statistics
```

Heaptrack is a heap memory profiler that tracks all memory allocations and de-allocations in a program. Gui is available in the heaptrack-gui package.

## Documentation

Detailed documentation is available in the [docs](docs) directory.

## References

- [Observability Tools](https://www.youtube.com/watch?v=C9vmS5xV23A)
