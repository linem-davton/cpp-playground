find_package(benchmark REQUIRED)

# Static libraries
add_library(matrices STATIC linear_algebra/matrices.cpp)

# Executables
add_executable(hello hello.cpp)
add_executable(fib fib.cpp)
add_executable(matrix matrix.cpp)
add_executable(jthreads jthreads.cpp)
add_executable(macros macros.cpp)

# Benchmarks
add_executable(bench_matrix bench_matrix.cpp)
target_link_libraries(bench_matrix PRIVATE benchmark::benchmark matrices)

# Linking
target_link_libraries(matrix PRIVATE matrices)
