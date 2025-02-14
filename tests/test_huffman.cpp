#include <gtest/gtest.h>
#include <map>
#include "huffman.h"

// Test for binary_search(srd::vector<T>&, T key)->std::optional<int>
TEST(HuffmanTest, CorrectnessTest) {
    FrequencyTable input{{"A", 25}, {"B", 25}, {"C", 20}, {"D", 15}, {"E", 10}, {"F", 5}};
    auto out = huffman(input);

    std::map<std::string, std::string> soln{{"A", "10"}, {"B", "01"}, {"C", "00"}, {"D", "110"}, {"E", "1111"}, {"F", "1110"}};
    EXPECT_EQ(out, soln);
}
