#include <algorithm>
#include <cstddef>
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

auto twoSum(std::vector<int>& nums, int target) -> std::vector<int> {
    // Can we do better.
    // Sort the array and use two pointers
    // Store the original value and index
    std::vector<std::pair<int, int>> arr;
    arr.reserve(nums.size());
    for (std::size_t i = 0; i < nums.size(); i++) {
        arr.emplace_back(nums[i], i);
    }
    std::sort(arr.begin(), arr.end());
    int i = 0;
    int j = nums.size() - 1;

    while (j > i) {
        auto sum = arr[i].first + arr[j].first;
        if (sum == target) {
            return {std::min(arr[i].second, arr[j].second), std::max(arr[i].second, arr[j].second)};
        } else if (sum > target) {
            j--;
        } else {
            i++;
        }
    }
    return {};
}

auto main() -> int {
    std::vector<int> v{-1, -2, -3, -4, -5};
    printVec(v);
    std::cout << "Duplicates found in array: " << hasDuplicate(v) << std::endl;
    auto res = twoSum(v, -8);
    printVec(res);
}
