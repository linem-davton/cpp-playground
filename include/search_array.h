#pragma once

#include <algorithm>
#include <optional>
#include <vector>
/* Classic Binary Search
 * Time Complexity - O(log n), Space Complexity - O(1)
 * Note: Array should be sorted
 * Not guranteed to return the first or last matching element
 *
 */

template <typename T>
auto binary_search(const std::vector<T>& vec, T key) -> std::optional<int> {
    int size = vec.size();
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int mid = (high + low) / 2;
        if (vec[mid] == key) {
            return mid;
        }
        if (vec[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return std::nullopt;
}
/* Cache Efficient Binary Search
 * Note: Array should be sorted
 * Not guranteed to return the first or the last matching element
 */
template <typename T>
auto binary_jump_search(const std::vector<T>& vec, T key) -> std::optional<int> {
    int size = vec.size();

    int index = 0;
    for (int jump = size / 2; jump >= 1; jump /= 2) {
        while (index + jump < size && vec[index + jump] <= key) {
            index += jump;
        }
    }
    if (vec[index] == key) {
        return index;
    }
    return std::nullopt;
}
/* std::find() - returns iterator to first matching element, else vec.end()
 * Array doesn't need to be sorted.
 */

template <typename T>
auto std_find(const std::vector<T>& vec, T key) -> std::optional<int> {
    auto it = std::find(vec.begin(), vec.end(), key);
    if (it == vec.end()) {
        return std::nullopt;
    }
    return std::distance(vec.begin(), it);
}
