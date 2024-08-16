cmake_minimum_required(VERSION 3.10)
project(playground)


# Set the C++ standard to C++ 20 required
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Third party libs


# include_directories(${CMAKE_SOURCE_DIR}/third_party)
include_directories(include_dir)

# Executables
add_executable(mulithreading src/multithread.cpp)
add_executable(macros src/macros.cpp)
