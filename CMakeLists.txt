cmake_minimum_required(VERSION 3.28)
project(playground)


# Set the C++ standard to C++ 20 required
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Generate compile_commands.json for clangd
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)



# include_directories(${CMAKE_SOURCE_DIR}/third_party)
# include_directories(include_dir)

# Executables
add_executable(hello src/hello.cpp)
add_executable(fib src/fib.cpp)
add_executable(matrices src/matrices.cpp)
add_executable(jthreads src/jthreads.cpp)
add_executable(macros src/macros.cpp)
