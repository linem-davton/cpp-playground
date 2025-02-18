
#include <algorithm>
#include <climits>
#include <cstddef>
#include <iostream>
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
        out[i] = 1;  // Initialize the longest subsequence at current index.
                     // Explore all choices: Amoung all left elements, 1. Smaller than the current element, 2. Has the longest subsequence.
        for (std::size_t j = 0; j < i; j++) {
            if (vec[j] < vec[i]) {
                out[i] = std::max(out[i], out[j] + 1);  // Find the longest subsequence ending at the previous element.
            }
        }
    }
    return out;
}
/*
 * Main idea: Maintain a sorted longest subsequence,
 *            At each element, replace the smallest greater element in the subsequence with the current element, if it exists, else add the current element to the subsequence.
 * WARNING - The contents of the subsequence vector are not the longest subsequence, in fact they are not even a subsequence, it just happens that the size of the vector is the length of the longest subsequence.
 * Elemets of subsequence(i) - the last element of the subsequence of length i+1. (if multiple subsequence of length i+1 exists, snmallest subsequence is considered).
 *
 * Processes vector from left to right, and maintains the vector of (smallest) ending element of various possible subsequence lenghths. (Note there might be multiple subsequence of same length, the algo prefers smallest such subsequenc).
 * nlogn - comes from std::lower_bound operation.
 * Time complexity is O(n * log(n)), where n is the size of the vector.
 * Space complexity is O(n).
 */
auto longest_subsequence_optimzed(const std::vector<int>& vec) -> std::size_t {
    // Maintain the sorted longest subsequence
    std::vector<int> subsequence;

    for (const auto& elem : vec) {
        // elem replaces the smallest greates elememt is the subsequence, so as to have the longest_subsequence
        auto it = std::lower_bound(subsequence.begin(), subsequence.end(), elem);
        if (it == subsequence.end()) {
            subsequence.push_back(elem);
        } else {
            *it = elem;
        }
    }
    printVec(subsequence);
    return subsequence.size();
}

auto main() -> int {
    std::vector<int> vec{6, 2, 5, 1, 7, 4, 8, 3};
    auto out = longest_subsequence(vec);
    printVec(out);
    printVec(vec);

    auto max_itr = std::max_element(out.begin(), out.end());
    auto max_idx = std::distance(out.begin(), max_itr);
    std::cout << "Longest subsequence: " << *max_itr << " at index: " << max_idx << "\n";

    std::cout << "Optimized algo: " << longest_subsequence_optimzed(vec) << "\n";
    return 0;
}
