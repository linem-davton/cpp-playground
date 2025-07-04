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

TopdownL1 gives a breakdown of the performance counters into disjoint and exhaustive categories:

- Frontend: Waiting for instructions, >30% is not cause of concern.,
- Backend: Waiting for memory, >30% is cause of concern.
- Bad speculation: Brach Mispredictions, >2% is cause of concern.
- Retiring: actually executing. >70% is good.

** Minor Page Faults **: Page requested is already in memory, but not in the process's address space. This is a normal operation and does not cause a performance hit.
** Major Page Faults **: Page requested is not in memory and needs to be loaded from disk. This causes a performance hit (Disk I/O).

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

## lcov

```C++
        :   // Random number generation
      28            2 :   std::random_device rd;
      29            2 :   std::mt19937 gen(rd()); // Mersenne Twister engine
      30            2 :   std::uniform_int_distribution<> dis(l.min_val, l.max_val);
      31              :
      32              :   // Fill the matrix with random numbers
      33         2002 :   for (int i = 0; i < d.rows; ++i) {
      34      2002000 :     for (int j = 0; j < d.cols; ++j) {
      35      2000000 :       matrix[i][j] = dis(gen);
      36              :     }
      37              :   }
      38              :
      39            2 :   return matrix;
      40            2 : }
      41              :
      42            1 : auto matrixMultiply(const MatrixInt &A, const MatrixInt &B, const Dimensions ad,
      43              :                     const Dimensions bd) -> std::optional<MatrixInt> {
      44            1 :   if (ad.cols != bd.rows) {
      45            0 :     std::cerr << "Matrix multiplication not possible with given dimensions."
      46            0 :               << std::endl;
      47            0 :     return std::nullopt;
      48              :   }
      49              :
      50              :   // Cache friendly matrix multiplication, inner loop accesses elements
      51              :   // sequentially with stride 1
      52            2 :   MatrixInt result(ad.rows, std::vector<int>(bd.cols, 0));
      53         1001 :   for (int i = 0; i < ad.rows; ++i) {
      54      1001000 :     for (int k = 0; k < ad.cols; ++k) {
      55   1001000000 :       for (int j = 0; j < bd.cols; ++j) {
      56   1000000000 :         result[i][j] += A[i][k] * B[k][j];
      57              :       }
      58              :     }
      59              :   }
      60            1 :   return result;
      61            1 : }
      62              :
      63            1 : void printMatrix(const MatrixInt &matrix) {
      64         1001 :   for (const auto &row : matrix) {
      65      1001000 :     for (const auto &elem : row) {
      66      1000000 :       std::cout << elem << " ";
      67              :     }
      68         1000 :     std::cout << '\n';
      69              :   }
      70            1 : }
      71              :
      72            1 : auto main() -> int {
      73            1 :   const int N1 = 1000;
      74            1 :   const int M1 = 1000;
      75            1 :   const int N2 = 1000;
      76            1 :   const int M2 = 1000;
      77            1 :   const int min_val = 1;
      78            1 :   const int max_val = 99;
      79              :
      80            1 :   const MatrixInt matrix1 = generateRandomMatrix({N1, M1}, {min_val, max_val});
      81            1 :   const MatrixInt matrix2 = generateRandomMatrix({N2, M2}, {min_val, max_val});
      82              :
      83            1 :   const auto result = matrixMultiply(matrix1, matrix2, {N1, M1}, {N2, M2});
      84            1 :   if (!result) {
      85            0 :     return 1;
      86              :   }
      87            1 :   printMatrix(result.value());
      88            1 : }

```
