#include <iostream>
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
        for (int j = 0; j < n - 1; j++) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

int main() {
    double a, b;
    int size;
    std::cout << "Input two number \n";
    std::cin >> a >> b;
    swap(a, b);
    std::cout << "Swapped " << a << " " << b << "\n";
    /* Create a random vector of size n */
    std::cout << "Enter the size of array \n";
    std::cin >> size;
    std::vector<int> vec = random_vector<int>(size);
    std::vector<double> vec1 = random_vector<double>(size);
    printVec<int>(vec);
    printVec<double>(vec1);
    bubble_sort(vec);
    bubble_sort(vec1);
    printVec<int>(vec);
    printVec<double>(vec1);
    return 0;
}
