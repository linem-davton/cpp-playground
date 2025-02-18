
#include <algorithm>
#include <climits>
#include <vector>
#include "utils.h"

/*
 * Find the longest subsequence in the given vector.
 * The elements are not necessarily contiguous.
 * Example: vec = {6, 2, 5, 1, 7, 4, 8, 3}, the longest subsequence is {2, 5, 7, 8}.
 * Time complexity is O(n^2), where n is the size of the vector.
 * Space complexity is O(n).
 *
 * Idea: For each element in the vector, find the longest subsequence ending at that element.
 *      The longest subsequence ending at the current element is one more than the longest subsequence ending at one of the previous elements, which is smaller than the current element.
 */
auto longest_subsequence(const std::vector<int>& vec) {
    std::vector<unsigned int> out(vec.size(), INT_MAX);
    // Base case:
    out[0] = 1;

    for (std::size_t i = 1; i < vec.size(); i++) {
        unsigned int num = 0;  // Initialize the longest subsequence at current index.
                               // Explore all choices: Amoung all left elements, 1. Smaller than the current element, 2. Has the longest subsequence.
        for (std::size_t j = 0; j < i; j++) {
            if (vec[j] < vec[i]) {
                num = std::max(num, out[j]);  // Find the longest subsequence ending at the previous element.
            }
        }
        out[i] = num + 1;  // subsequence at current index is one more than the previous longest
    }
    return out;
}

auto main() -> int {
    std::vector<int> vec{6, 2, 5, 1, 7, 4, 8, 3};
    auto out = longest_subsequence(vec);
    printVec(out);
    printVec(vec);
}
