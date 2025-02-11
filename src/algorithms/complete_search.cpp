#include "complete_search.h"
#include <vector>

auto main() -> int {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::vector<int> subset;
    // generateSubsets_recursion(vec, 0, subset);
    // generateSubsets_masking(vec);
    // generatePermuations_iter(vec);
    generatePermuations_recursion(vec, 0);
    return 0;
}
