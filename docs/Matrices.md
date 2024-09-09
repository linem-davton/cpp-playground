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

## Strace

System call made by the program

```BASH
strace  -c ./matrices

% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 88.90    0.014725           1      8000           write
  5.02    0.000832           8        99           brk
  2.60    0.000430         430         1           execve
  2.05    0.000339          15        22           mmap
  0.41    0.000068          13         5           openat
  0.24    0.000039           6         6           mprotect
  0.18    0.000029           7         4           read
  0.17    0.000028           5         5           close
  0.17    0.000028           4         6           fstat
  0.07    0.000012           6         2           pread64
  0.07    0.000012          12         1         1 access
  0.04    0.000006           6         1           arch_prctl
  0.03    0.000005           5         1           set_tid_address
  0.03    0.000005           5         1           set_robust_list
  0.03    0.000005           5         1           rseq
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         1           futex
  0.00    0.000000           0         1           prlimit64
  0.00    0.000000           0         1           getrandom
------ ----------- ----------- --------- --------- ----------------
100.00    0.016563           2      8159         1 total
```
