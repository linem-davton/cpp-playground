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

/* Buuble Sort
 * Time Complexity - O(n^2)
 * Swaps consercutive elements which are ordered in reverse order
 * Early Stop - If no swaps are done in one pass then array is already sorted
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
            std::cout << "BubbleSort: Iteration: " << i << " and " << j << '\n';
            printVec<T>(v);
        }

        if (!swapped) {
            std::cout << "BubbleSort: Array Sorted after iteration: " << i << " instead of: " << n - 1 << "\n";
            break;
        }
    }
}

/* Insertion Sort
 * Time Complexity - O(n^2), Space Complexity - O(1)
 *
 */

template <typename T>
void insertion_sort(std::vector<T>& vec) {
    int size = vec.size();

    for (int i = 1; i < size; i++) {
        int key = vec[i];
        // place the key in the correct position in left subarray,
        // that is key should be greater than all elements in left subarray
        int j = i - 1;
        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            j--;
            std::cout << "InsertionSort: Iteration " << i << " and " << j << '\n';
            printVec<T>(vec);
        }
        vec[j + 1] = key;
        std::cout << "InsertionSort: Iteration " << i << '\n';
        printVec<T>(vec);
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

    // Print the vectors before sorting , sort and print the vectors after sorting
    printVec<int>(vec);
    bubble_sort(vec);
    printVec<int>(vec);

    shuffle(vec);
    insertion_sort(vec);
    printVec<int>(vec);
    return 0;
}
