#include <gtest/gtest.h>
#include "search_array.h"

// Test for binary_search(srd::vector<T>&, T key)->std::optional<int>
TEST(SearchArrayTest, BinarySearch) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_EQ(binary_search(vec, 5).value(), 4);
    EXPECT_EQ(binary_search(vec, 10), std::nullopt);
}

TEST(SearchArrayTest, BinaryJumpSearch) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_EQ(binary_jump_search(vec, 5).value(), 4);
    EXPECT_EQ(binary_jump_search(vec, 10), std::nullopt);
}
