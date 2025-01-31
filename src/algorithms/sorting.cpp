#include <iostream>
#include <string>
#include <vector>
#include "array_utils.h"

template <typename T>
void swap(T& a, T& b) {
    T temp;
    temp = a;
    a = b;
    b = temp;
}

/* Time Complexity - O(n^2)
 * Swaps consercutive elements which are ordered in reverse order
 */
template <typename T>
void bubble_sort(std::vector<T>& v) {
    int n = v.size();
    for (int i = 0; i < n; i++) {
        // One pass of internal loop should swap atleast one element, if not then array is already sorted
        bool swapped = false;
        for (int j = 0; j < n - 1; j++) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
                swapped = true;
            }
            std::cout << "Array after iteration " << i << " and " << j << '\n';
            printVec<T>(v);
        }

        if (!swapped) {
            std::cout << "Array is already sorted after iteration: " << i << " instead of: " << n - 1 << "\n";
            break;
        }
    }
}

auto main(int argc, char* argv[]) -> int {
    int size = 0;
    if (argc > 1) {
        size = std::stoi(argv[1]);
    } else {
        std::cout << "Enter the size of array \n";
        std::cin >> size;
    }
    std::vector<int> vec = random_vector<int>(size);
    // std::vector<double> vec1 = random_vector<double>(size);

    printVec<int>(vec);
    // printVec<double>(vec1);

    bubble_sort(vec);
    // bubble_sort(vec1);

    printVec<int>(vec);
    // printVec<double>(vec1);
    return 0;
}
