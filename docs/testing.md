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

## Test Conditions

- A Test fails if any assertion within the `TEST()` fails.

## Test Fixtures

## References

1. [Google Test](https://google.github.io/googletest/)
2. [Video Tutorial Google Test](https://www.youtube.com/watch?v=JJqRlSTQlh4)
