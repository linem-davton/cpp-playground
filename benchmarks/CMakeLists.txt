find_package(benchmark REQUIRED)
# Benchmark executables
add_executable(bench_matrix bench_matrix.cpp)
target_link_libraries(bench_matrix PRIVATE benchmark::benchmark matrices)
