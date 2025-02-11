#include <algorithm>
#include <cstddef>
#include <vector>
#include "array_utils.h"

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
template <typename T>
auto generateSubsets_recursion(std::vector<T>& vec, std::size_t index, std::vector<T>& subset) -> void {
    // bound check
    if (vec.size() > 25) {
        std::cerr << "Vector size too large for subset enumeration";
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
        std::cerr << "Vector size too large for subset enumeration";
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

/* @breif Custom implementation of std::next_permutation
 * Time Complexity: O(n), Space Complexity: O(1)
 * @detail Algorithm: Works in three steps -
 * 1. Find the first non decreasing sequence from right
 * 2. Swap the found index, with the smallest greate element in right subarray.
 * 3. Reverse the array after the swapped index.
 * 4. Terminate when the array is reverse sorted.
 * @param vec: Input vector
 */

template <typename T>
auto nextPermutation(std::vector<T>& vec) -> bool {
    // Terminate when the array is reverse sorted.
    // Find the first non decreasing sequence from right,
    int size = vec.size();
    int index = -1;
    for (int i = size - 2; i >= 0; i--) {
        if (vec[i] < vec[i + 1]) {
            index = i;
            break;  // Found the first non decreasing sequence from right
        }
    }
    if (index == -1) {
        return false;
    }
    // Swap vec[i] with the smallest greatest element in right array.
    int small_greatest = index + 1;
    for (int i = size - 1; i > index; i--) {
        if (vec[index] < vec[i] && vec[i] < vec[small_greatest]) {
            small_greatest = i;
        }
    }
    std::swap(vec[index], vec[small_greatest]);

    // Reverse the array after swapped index
    std::reverse(vec.begin() + index + 1, vec.end());
    return true;
}

/*
 * @breif Generate all possible permutations of a given set using std::next_permutation
 * Time Complexity: O(n!), Space Complexity: O(n)
 * @param vec: Input vector
 */
template <typename T>
auto generatePermuations_iter(std::vector<T>& vec) -> void {
    std::sort(vec.begin(), vec.end());
    do {
        // handle the permutation
        printVec(vec);
    } while (nextPermutation(vec));
}
