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

#include "search_array.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include "array_utils.h"

auto main() -> int {
    // Create a vector of 10 elements
    auto vec = random_vector<int>(20);
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
        // auto index = binary_jump_search(vec, input);
        auto index = std_find(vec, input);
        if (index.has_value()) {
            std::cout << "Element " << input << " found at index: " << index.value() << "\n";
        } else {
            std::cout << "Element " << input << " not found\n";
        }
    }
}
