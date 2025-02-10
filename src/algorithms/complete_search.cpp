#include <cstddef>
#include <vector>

#include "array_utils.h"
template <typename T>
/*
 * @breif Generate all possible subsets of a given set using recursion
 * @detail Creates a binary decision tree, each element can either be in or out of the subset
 * First Branch: Consider the case where current index element is not part of the subset
 * Second Branch: Make the current element part of the subset.
 * Cleanup: remove the element from the subset vector.
 * Time Complexity: O(2^n), Space Complexity: O(n)
 * @param vec: Input vector
 * @param index: Current index being considered
 * @param subset: Current subset being considered
 */
auto generateSubsets_recursion(std::vector<T>& vec, std::size_t index, std::vector<T>& subset) -> void {
    // bound check
    if (vec.size() > 25) {
        std::cout << "Vector size too large for subset enumeration";
        return;
    }

    // Base Case: when each element has been considered, index points past the last element
    if (index == vec.size()) {
        printVec(subset);
        return;
    }

    // Case 1: Exclude the current element being considered
    generateSubsets_recursion(vec, index + 1, subset);

    // Case2: Include the current element being considered
    subset.push_back(vec[index]);
    generateSubsets_recursion(vec, index + 1, subset);
    // Backtrack, return to previosu state, remove the element
    subset.pop_back();
    return;
}

/*
 * @breif Generate all possible subsets of a given set using bitmasking
 * @detail Uses bitmasking to generate all possible subsets of a given set
 * Each bit in the mask represents the presence of the corresponding element in the subset
 * Time Complexity: O(2^n), Space Complexity: O(n)
 * @param vec: Input vector
 */
template <typename T>
auto generateSubsets_masking(std::vector<T>& vec) -> void {
    auto n = vec.size();
    // bound check
    if (n > 25) {
        std::cout << "Vector size too large for subset enumeration";
        return;
    }
    auto total_subsets = 1 << n;  // 2^n

    // iterate over all possible masks, 2^n iterations
    for (int mask = 0; mask <= total_subsets; mask++) {
        std::vector<T> subset;
        // iterate over all index, and include it in subset if the corresponding bit is set.
        for (unsigned int i = 0; i < n; i++) {
            if (mask & (1 << i)) {  // check if mask has the ith bit set
                subset.push_back(vec[i]);
            }
        }
        printVec(subset);
    }
};

auto main() -> int {
    std::vector<int> vec = {1, 2, 3};
    std::vector<int> subset;
    generateSubsets_recursion(vec, 0, subset);
    generateSubsets_masking(vec);
    return 0;
}
