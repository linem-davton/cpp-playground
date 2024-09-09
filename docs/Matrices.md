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

### Debug Builds

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

### Release Builds

Cache Freindly with Release build with `-O2` optimization flag.

```BASH
 Performance counter stats for './matrices':

            442.76 msec task-clock                       #    0.998 CPUs utilized
                 1      context-switches                 #    2.259 /sec
                 0      cpu-migrations                   #    0.000 /sec
             5,060      page-faults                      #   11.428 K/sec
     1,960,741,610      cycles                           #    4.428 GHz
     6,221,499,663      instructions                     #    3.17  insn per cycle
     1,027,226,285      branches                         #    2.320 G/sec
         1,038,215      branch-misses                    #    0.10% of all branches
                        TopdownL1                 #     18.9 %  tma_backend_bound
                                                  #      1.9 %  tma_bad_speculation
                                                  #      5.5 %  tma_frontend_bound
                                                  #     73.7 %  tma_retiring

       0.443480715 seconds time elapsed

       0.434405000 seconds user
       0.009008000 seconds sys
```

Non-cache Freindly with Release build with `-O2` optimization flag.

```BASH
 Performance counter stats for './matrices':

            741.00 msec task-clock                       #    0.999 CPUs utilized
                 2      context-switches                 #    2.699 /sec
                 0      cpu-migrations                   #    0.000 /sec
             5,060      page-faults                      #    6.829 K/sec
     3,379,589,124      cycles                           #    4.561 GHz
     9,224,019,517      instructions                     #    2.73  insn per cycle
     1,027,612,383      branches                         #    1.387 G/sec
         1,038,018      branch-misses                    #    0.10% of all branches
                        TopdownL1                 #     47.9 %  tma_backend_bound
                                                  #      1.2 %  tma_bad_speculation
                                                  #      2.3 %  tma_frontend_bound
                                                  #     48.6 %  tma_retiring

       0.741694100 seconds time elapsed

       0.735622000 seconds user
       0.006005000 seconds sys

```
