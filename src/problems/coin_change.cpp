/* Problem Statement:
 * Given an integer N, find the number of ways to make change for amount N, given that we have infinite supply of each of S = { c1, c2, .. , cm} valued coins.
 *
 * Example:
 * N = 5, S = {1, 2, 5}
 * Output: 4
 * Explanation: 4 ways to make change for 5.
 * 1. {1, 1, 1, 1, 1}
 * 2. {1, 1, 1, 2}
 * 3. {1, 2, 2}
 * 4. {5}
 *
 * N = 3, S = {2}
 * Output: 0
 * Explanation: No way to make change for 3 cents using only 2 cent coin
 *
 * N = 12, S = {2, 4, 5, 10}
 * Output: 6
 * Explanation: 5 ways to make change for 10 cents
 * 1. {2, 2, 2, 2, 2}
 * 2. {2, 2, 2, 4}
 * 3. {2,4,4}
 * 4. {4,4,4}
 * 5. {2, 2, 5}
 * 6. {10,2}
 */

// Recursive solution.
#include <algorithm>
#include <climits>
#include <iostream>
#include <set>
#include "utils.h"

// Find all paths to the node [], from the node N;
// Note this will consider all the permutations as different choices.
auto coinChange_totalSoln(const std::set<int>& coins, int& state, std::set<std::vector<int>>& all_choices, std::vector<int>& curr_choices, const int total) -> void {
    // Error handling
    if (state > total) {
        std::cerr << "Invalid state";
        return;
    }

    // Base Case
    if (state == total) {
        // Check is the permutation already exists.
        std::vector<int> choices(curr_choices.begin(), curr_choices.end());  // making a copy of current choices to as sort works in place.
        std::sort(choices.begin(), choices.end());
        auto result = all_choices.insert(choices);  // Disregard the pemutations
        if (result.second) {                        // New solution
            printVec(curr_choices);
        }
        return;
    }

    // Explore all valid choices at current state.
    auto old_state = state;
    for (const auto& coin : coins) {
        if (state + coin <= total) {
            state += coin;
            curr_choices.push_back(coin);
            coinChange_totalSoln(coins, state, all_choices, curr_choices, total);
            // Backtrack
            curr_choices.pop_back();
            state = old_state;
        }
    }
}

/*
 * Function return INT_MAX if there is no way to make the change.
 */
auto coinChange_min(const std::set<int>& coins, int state, std::vector<int>& memo) -> unsigned int {
    if (state < 0) {
        std::cerr << "Invalid state: State: " << state << "\n";
        return 0;
    }
    // Base case
    if (state == 0) {
        return 0;
    }
    if (memo[state] != -1) {
        return memo[state];
    }
    // Explore all choices
    unsigned int count = INT_MAX;
    for (const auto& coin : coins) {
        if (state - coin >= 0) {
            count = std::min(coinChange_min(coins, state - coin, memo) + 1, count);
        }
    }

    memo[state] = count;
    return count;
}

auto main() -> int {
    const std::set<int> coins{2, 4, 5, 10};
    int state = 0;
    int total = 3;
    std::vector<int> choices;
    std::set<std::vector<int>> all_choices;
    coinChange_totalSoln(coins, state, all_choices, choices, total);
    std::cout << "For Sum: " << total << " Total count: " << all_choices.size() << "\n";

    state = 0;
    std::vector<int> memo(total + 1, -1);
    int count = coinChange_min(coins, total, memo);
    std::cout << "For Sum: " << total << " Min soln: " << count << "\n";
    return 0;
}
