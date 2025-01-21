# Static libraries
add_library(matrices STATIC linear_algebra/matrices.cpp)

# Subdirectories
add_subdirectory(algorithms)

# Executables
add_executable(hello hello.cpp)
add_executable(fib fib.cpp)
add_executable(matrix matrix.cpp)
add_executable(jthreads jthreads.cpp)
add_executable(macros macros.cpp)

# Linking
target_link_libraries(matrix PRIVATE matrices)
