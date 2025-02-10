# Writing Tests

The project uses Google Test for testing. Place the test files in the `tests` directory.

Boilerplate code for a test file:

```Cpp
#include <gtest/gtest.h>

// Test Functions
TEST(TestSuiteName, TestName) {
    // Test Code
    ASSERT_EQ(1, 1);
}
```

## Test Functions

> [!Note]
> TEST() functions are C++ functions that are registered with Google Test. They are not called directly, they **don't return** anything.
> Google Test runs them when the test program is executed.

- `TEST(TestSuiteName, TestName)` is a macro that defines a test function.
- `TestSuiteName` and `TestName` can be any valid C++ identifier but without `_`.
- Each test is uniquely identified by the combination of `TestSuiteName` and `TestName`.

## Running Tests

To run the tests with ctest.

```bash
ctest --test-dir build/debug/tests # the location of CTestTestfile.cmake
ctest --preset=debug -V         # run all tests
```

To run the tests with the test executable.

```bash
./build/debug/bin/test_name
```

## Test Conditions

- A Test fails if any assertion within the `TEST()` fails.

## Test Fixtures

## CMake with Google Test

Setting up [GTest with CMake](https://google.github.io/googletest/quickstart-cmake.html)

Configure CMakeLists.txt to use GTest.

```cmake
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing() # set at the top level CMakeLists.txt to generate CTestTestfile.cmake in correct directory
```

To build tests, add the following to CMakeLists.txt.

```cmake
# first test
add_executable(test_matrix test_matrix.cpp)
target_link_libraries(test_matrix PRIVATE matrices GTest::gtest_main)

# second test
add_executable(test_vector test_vector.cpp)
target_link_libraries(test_vector PRIVATE vectors GTest::gtest_main)

# discover tests
include(GoogleTest)
gtest_discover_tests(test_matrix)
gtest_discover_tests(test_vector)
```

## References

1. [Google Test](https://google.github.io/googletest/)
2. [Video Tutorial Google Test](https://www.youtube.com/watch?v=JJqRlSTQlh4)
