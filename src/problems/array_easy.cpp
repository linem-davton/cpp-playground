#include <iostream>
#include <set>
#include <vector>
#include "utils.h"
auto hasDuplicate(std::vector<int> &vec) -> bool {
    std::set<int> s(vec.begin(), vec.end());
    return s.size() != vec.size();  // if size of set is not equal to size of vector, then there is a duplicate
}

auto main() -> int {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1};
    printVec(v);
    std::cout << "Duplicates found in array: " << hasDuplicate(v) << std::endl;
}
