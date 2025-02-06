find_package(benchmark REQUIRED)

# Benchmark executables
add_executable(bench_matrix bench_matrix.cpp)
target_link_libraries(bench_matrix PRIVATE benchmark::benchmark matrices)

add_executable(bench_arrays bench_arrays.cpp)
target_link_libraries(bench_arrays PRIVATE benchmark::benchmark)
