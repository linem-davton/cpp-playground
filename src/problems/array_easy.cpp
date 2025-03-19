#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include "utils.h"

/*
 * Given an array of integers, find if the array contains any duplicates.
 * Solutions:
 * Brute Force - O(n^2)
 *   Iterate through the array and for each element, check if it is present in the rest of the array (i+1, n).
 * Sorting - O(nlogn)
 *   Sort, and check if adjacent elements are equal.
 * Hash Set - O(n)
 *  Iterate, check if element is in set, if true retun true, else add the element to set.
 */
auto hasDuplicate(std::vector<int>& vec) -> bool {
    std::unordered_set<int> s;

    for (const auto& elem : vec) {
        if (s.count(elem)) {
            return true;
        }
        s.insert(elem);
    }

    return false;
}

auto main() -> int {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printVec(v);
    std::cout << "Duplicates found in array: " << hasDuplicate(v) << std::endl;
}
