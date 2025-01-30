/*
 * VVarious Array Search Algorithms
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
#include <vector>
#include "array_utils.h"

std::vector<int> random_vector(int size) {
    std::vector<int> v(size);
    for (int i = 0; i < size; i++) {
        v[i] = i;
    }
    return v;
}

auto main() -> int {
    // Create a vector of 10 elements
    std::vector<int> v{10};
    std::iota(v.begin(), v.end(), 0);
}
