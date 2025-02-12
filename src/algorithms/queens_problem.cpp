#include <vector>
#include "array_utils.h"

/* Problem Statement:
 * Given an integer N, find all possible arrangements of N queens on an NxN chessboard
 */

/*
Background Theory:
  Chessboard uses discrete coordinate space, integer rows and columns, slopes can only be +-1 for diagonals
  In Discrete Space, a straight line represented by y = mx + c, where m is the slope, can only have rational slopes.
  Diagnoal movements by definition have slope of +-1
  For a given point (x1, y1) and (x2, y2), the slope is (y2 - y1) / (x2 - x1).

Existence of Solution:
  For N>=4, there always exists a solution, for N=1,2,3, there is no solution
  It is infeasible to find all solutions for N>30, as numbers are too large (What is this number and its growth rate?)
  However, it is possible to find just one solution for very large N (1Million+ queens) using SAT solvers.
*/

/*
Recursive Backtracking:
  Process row by row
  State:  vec[i] = j means queen is placed at row i, column j
          Vector index represents row, value represents column
  Choices: Place the queen in any column of the current row
  Constraints: No two queens should be in the same row, column or diagonal
  Time Complexity: O(n!), Space Complexity: O(n)
*/

/*
Results:
Finding all solutions:
      O(N!) becomes infeasible for N>15
Findings Any one Silution using Backtracking Recursion:
  N ≈ 30 → Fast (~seconds)
  N ≈ 40 → Moderate (~minutes)
  N ≈ 45 → Very slow (~hours)
  N ≈ 50 → Unfeasible (~days or more)
*/

auto queens_arrangement(std::vector<int>& vec, int row, int& count) -> void {
    if (row == (int)vec.size()) {
        printVec(vec);  // Found a valid arrangement
        count++;
        return;
    }
    // Explore all possible choices (column) for the current state(row)
    for (int i = 0; i < (int)vec.size(); i++) {
        // Update the state
        vec[row] = i;  // place the queen at row, column i
        bool valid = true;

        // Check if choice is valid: Ensure that queen placement in column i is valid
        for (int j = 0; j < row; j++) {
            // vec[j] == vec[row] (Same Column) checks if any previous row has queen in the same COLUMN
            // Exmaple: vec = [1, 3, 1, _]  // Queens in row 0 and row 2 are in the same column 1
            if (vec[row] == vec[j] || abs(vec[j] - vec[row]) == abs(j - row)) {
                valid = false;
                break;  // Queen cannot be placed in column i, move to the next column
            }
        }
        // For valid choice Recurse: Queen placement is valid in row and column i, move to the next row
        if (valid) {
            queens_arrangement(vec, row + 1, count);
        }
        // Backtracing: Reset the state
        vec[row] = -1;  // Not needed for queens_arrangement, but useful for other problems
    }
}

auto main() -> int {
    const int board_size = 10;
    std::vector<int> vec(board_size, -1);
    int count = 0;
    queens_arrangement(vec, 0, count);
    std::cout << "Total arrangements: " << count << '\n';
    return 0;
}
