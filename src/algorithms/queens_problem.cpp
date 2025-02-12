#include <vector>
#include "array_utils.h"

/*
 Background Theory:
Chessboard uses discrete coordinate space, integer rows and columns, slopes can only be +-1 for diagonals
In Discrete Space, a straight line represented by y = mx + c, where m is the slope, can only have rational slopes.
Diagnoal movements by definition have slope of +-1
For a given point (x1, y1) and (x2, y2), the slope is (y2 - y1) / (x2 - x1)
*/

/* Recursive Backtracking:
 Process row by row
 State: vec[i] = j means queen is placed at row i, column j
        Vector index represents row, value represents column
Choices: Place the queen in any column of the current row
Constraints: No two queens should be in the same row, column or diagonal
Time Complexity: O(n!), Space Complexity: O(n)
*/
auto queens_arrangement(std::vector<int>& vec, int row, int& count) -> void {
    if (row == (int)vec.size()) {
        printVec(vec);
        count++;
        return;
    }
    // Explore all possible columns (choices) for the current row (state)
    for (int i = 0; i < (int)vec.size(); i++) {
        vec[row] = i;       // place the queen at row, column i
        bool valid = true;  // check if the current arrangement is valid
        // Ensure that queen placement in current row does not violate any previously placed queens in rows 0 to row - 1
        for (int j = 0; j < row; j++) {
            // vec[j] == vec[row] (Same Column) checks if any previous row has queen in the same COLUMN
            // Exmaple: vec = [1, 3, 1, _]  // Queens in row 0 and row 2 are in the same column 1
            if (vec[row] == vec[j] || abs(vec[j] - vec[row]) == abs(j - row)) {
                valid = false;
                break;
            }
        }
        if (valid) {
            queens_arrangement(vec, row + 1, count);
        }
    }
}
auto main() -> int {
    std::vector<int> vec(4, 0);
    int count = 0;
    queens_arrangement(vec, 0, count);
    std::cout << "Total arrangements: " << count << std::endl;
    return 0;
}
