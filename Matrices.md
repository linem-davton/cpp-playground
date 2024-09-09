# Cache Freindly Matrix Multiplication

```cpp
  for (int i = 0; i < ad.rows; ++i) {
    for (int k = 0; k < ad.cols; ++k) {
      for (int j = 0; j < bd.cols; ++j) {
        result[i][j] += A[i][k] * B[k][j]; // Sequential access in inner loop
      }
    }
  }
```

Compare the above to

```cpp
  for (int i = 0; i < ad.rows; ++i) {
    for (int j = 0; j < bd.cols; ++j) {
      for (int k = 0; k < ad.cols; ++k) {
        result[i][j] += A[i][k] * B[k][j]; // Matrix B is accessed with stride and for matrices with enough columns (64Byte/4Byte = 16) cache misses will is likely to occur
      }
    }
  }
```

## Perf Benchmarks

1. For a 1000x1000 matrix multiplication, the cache friendly version is 2x faster than the non-cache friendly version.

```BASH
# Cache friendly version
 Performance counter stats for './matrices':

          1,265.40 msec task-clock                       #    0.999 CPUs utilized
                 3      context-switches                 #    2.371 /sec
                 0      cpu-migrations                   #    0.000 /sec
             5,059      page-faults                      #    3.998 K/sec
     5,711,206,903      cycles                           #    4.513 GHz
    23,296,760,994      instructions                     #    4.08  insn per cycle
     1,038,024,384      branches                         #  820.316 M/sec
         2,065,773      branch-misses                    #    0.20% of all branches
                        TopdownL1                 #      9.1 %  tma_backend_bound
                                                  #      1.9 %  tma_bad_speculation
                                                  #      7.4 %  tma_frontend_bound
                                                  #     81.6 %  tma_retiring

       1.266065582 seconds time elapsed

       1.259043000 seconds user
       0.007000000 seconds sys

```

```BASH
# Non-cache friendly version
 Performance counter stats for './matrices':

          1,767.02 msec task-clock                       #    1.000 CPUs utilized
                19      context-switches                 #   10.753 /sec
                 1      cpu-migrations                   #    0.566 /sec
             5,060      page-faults                      #    2.864 K/sec
     7,935,208,225      cycles                           #    4.491 GHz
    23,303,331,551      instructions                     #    2.94  insn per cycle
     1,039,062,098      branches                         #  588.030 M/sec
         2,072,940      branch-misses                    #    0.20% of all branches
                        TopdownL1                 #     34.5 %  tma_backend_bound
                                                  #      2.3 %  tma_bad_speculation
                                                  #      5.1 %  tma_frontend_bound
                                                  #     58.1 %  tma_retiring

       1.767886296 seconds time elapsed

       1.758612000 seconds user
       0.008998000 seconds sys
```
