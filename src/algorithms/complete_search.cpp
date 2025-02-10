#include <cstddef>
#include <vector>

#include "array_utils.h"
template <typename T>
/*
 * @breif Generate all possible subsets of a given set
 * @detail Creates a binary decision tree, each element can either be in or out of the subset
 * First Branch: Consider the case where current index element is not part of the subset
 * Second Branch: Make the current element part of the subset.
 * Cleanup: remove the element from the subset vector.
 * Time Complexity: O(2^n), Space Complexity: O(n)
 * @param vec: Input vector
 * @param index: Current index being considered
 * @param subset: Current subset being considered
 */
auto generateSubsets(std::vector<T>& vec, std::size_t index, std::vector<T>& subset) {
    // Base Case: when each element has been considered, index points past the last element
    if (index == vec.size()) {
        printVec(subset);
        return;
    }

    // Case 1: Exclude the current element being considered
    generateSubsets(vec, index + 1, subset);

    // Case2: Include the current element being considered
    subset.push_back(vec[index]);
    generateSubsets(vec, index + 1, subset);
    // Backtrack, return to previosu state, remove the element
    subset.pop_back();
    return;
}

auto main() -> int {
    std::vector<int> vec = {1, 2, 3};
    std::vector<int> subset;
    generateSubsets(vec, 0, subset);
    return 0;
}
