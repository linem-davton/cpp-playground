cmake_minimum_required(VERSION 3.28)
project(playground)


# Set the C++ standard to C++ 20 required
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-Wall -Wextra -Wpedantic -Werror -fno-omit-frame-pointer)
# Cmake adds -g to the compile options by default for Debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-Og --coverage)
    add_link_options(--coverage)
  # add_compile_options(-fsanitize=address,undefined,leak)
  # add_link_options(-fsanitize=address,undefined,leak)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O2)
endif()

# Third party libs


# include_directories(${CMAKE_SOURCE_DIR}/third_party)
# include_directories(include_dir)

# Executables
add_executable(hello src/hello.cpp)
add_executable(fib src/fib.cpp)
add_executable(matrices src/matrices.cpp)
add_executable(jthreads src/jthreads.cpp)
add_executable(macros src/macros.cpp)
