cmake_minimum_required(VERSION 3.28)
project(playground)

# Set the C++ standard to C++ 20 required
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Generate compile_commands.json for clangd, done in CMakePresets.json
set(CMAKE_CXX_STANDARD 20)

enable_testing() # set global flag to generate CTestTestfile.cmake in correct directory

# Include Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Set the output directories for executables and libraries globally
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(include)
# Add the subdirectories
add_subdirectory(src)
add_subdirectory(tests)

# include_directories(${CMAKE_SOURCE_DIR}/third_party)
# include_directories(include_dir)


