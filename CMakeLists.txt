cmake_minimum_required(VERSION 3.28)
project(playground)


# Set the C++ standard to C++ 20 required
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Generate compile_commands.json for clangd
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

 include_directories(include)

# subdirectories
add_subdirectory(src)

enable_testing()

# Include Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(tests)

# include_directories(${CMAKE_SOURCE_DIR}/third_party)
# include_directories(include_dir)


