#include <iostream>
#include <optional>
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
 * Time Complexity - O(n^2), Space Complexity - O(1)
 * Every pass moves the largest element to the end of the array
 * Swaps consercutive elements which are not in order
 * Early Stop - If no swaps are done in one pass then array is already sorted
 * Note: Don't ever use it!
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

/* Selection Sort
 * Sorts array left to right, swap the fist unsorted element with the minimum element in the right subarray
 * Time Complexity - O(n^2), Space Complexity - O(1)
 * Note: Not stable
 */
template <typename T>
void selection_sort(std::vector<T>& vec) {
    int size = vec.size();
    for (int i = 0; i < size; i++) {
        int minID = i;  // Assume the first element is the minimum
        // find the minimum element in the right subarray
        for (int j = i + 1; j < size; j++) {
            if (vec[j] < vec[minID]) {
                minID = j;
            }
        }
        // Now we have the index of minimum element in the right subarray
        // Swap the first element of right subarray with the minimum element
        swap(vec[i], vec[minID]);
    }
}
/* Insertion Sort
 * Sorts array left to right, place the first unsorted element in the correct position in the left subarray
 * Time Complexity - O(n^2), Space Complexity - O(1)
 * Note: Used in std::sort for small arrays
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

/*  Counting Sort
 *  Used for sorting integers in a specific range say 0 to k
 *  Time Complexity - O(n+k), Space Complexity - O(k)
 *  k is the range of the input
 *  Note: Not a comparison based sorting algorithm
 *  Not good when k >> n, good when n >> k
 */

void selection_sort(std::vector<int>& vec) {
    // make sure all elements are positive
    int min_val = *std::min_element(vec.begin(), vec.end());
    if (min_val < 0) {
        throw std::invalid_argument("All elements should be positive");
    }
    // create an array on size of max element in the array
    int max_val = *std::max_element(vec.begin(), vec.end());
    // Need index from 0 to max_val, so size should be max_val + 1
    // Fill the array, where value at index i is the count of i in the input array
    std::vector<int> count(max_val + 1, 0);
    for (int val : vec) {
        count[val]++;
    }
    // Fill the original array with sorted elements
    // Each value `i` is inserted into the array exactly
    // `count[i]` times, ensuring a stable and sorted order.
    int j = 0;
    for (int i = 0; i < max_val; i++) {
        while (count[i] > 0) {
            vec[j] = i;
            j++;
            count[i]--;
        }
    }
}
/* Binary Search
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

auto main(int argc, char* argv[]) -> int {
    int size = 0;
    if (argc > 1) {
        size = std::stoi(argv[1]);
    } else {
        std::cout << "Enter the size of array \n";
        std::cin >> size;
    }
    std::vector<int> vec = random_vector<int>(size);

    // Print the vectors before sorting , sort and print the vectors after sorting
    printVec<int>(vec);
    bubble_sort(vec);
    printVec<int>(vec);

    shuffle(vec);
    selection_sort(vec);
    printVec<int>(vec);

    shuffle(vec);
    insertion_sort(vec);
    printVec<int>(vec);

    // Binary Search Example
    int input = 0;

    std::cout << "Enter the number to search, -1 to exit\n";
    std::cin >> input;
    while (input != -1) {
        auto index = binary_search(vec, input);
        if (index.has_value()) {
            std::cout << "Element found at index: " << index.value() << "\n";
        } else {
            std::cout << "Element " << input << " not found\n";
        }

        std::cout << "Enter the number to search, -1 to exit\n";
        std::cin >> input;
    }
    return 0;
}
