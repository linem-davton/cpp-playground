# Static libraries
add_library(matrices STATIC linear_algebra/matrices.cpp)

# Subdirectories
add_subdirectory(algorithms)
add_subdirectory(problems)
add_subdirectory(ds)
add_subdirectory(performance)

# Executables
add_executable(hello hello.cpp)
add_executable(fib fib.cpp)
add_executable(matrix matrix.cpp)
add_executable(jthreads jthreads.cpp)
add_executable(macros macros.cpp)
add_executable(bits bits.cpp)
add_executable(numerics numerics.cpp)
add_executable(lifetimes lifetimes.cpp)
add_executable(overload_resolution overload_resolution.cpp)
add_executable(time time.cpp)
add_executable(filesystem filesystem.cpp)
# Linking
target_link_libraries(matrix PRIVATE matrices)
