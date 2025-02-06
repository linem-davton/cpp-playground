/*
 * Various Array Search Algorithms
 * 1. std::find
 * 2. std::find_if
 * 3. std::find_if_not
 * 4. std::adjacent_find
 * 5. std::count
 * 6. std::count_if
 * 7. std::search
 *
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <optional>
#include <vector>
#include "array_utils.h"

/* Classic Binary Search
 * Time Complexity - O(log n), Space Complexity - O(1)
 * Note: Array should be sorted
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
auto main() -> int {
    // Create a vector of 10 elements
    auto vec = random_vector<int>(20);
    // Print the vector
    std::sort(vec.begin(), vec.end());
    printVec<int>(vec);
    int input = 0;
    while (true) {
        std::cout << "Enter the number to search, -1 to exit\n";
        std::cin >> input;
        if (input == -1) {
            break;
        }
        // auto index = binary_search(vec, input);
        auto index = binary_jump_search(vec, input);
        if (index.has_value()) {
            std::cout << "Element " << input << " found at index: " << index.value() << "\n";
        } else {
            std::cout << "Element " << input << " not found\n";
        }
    }
}
