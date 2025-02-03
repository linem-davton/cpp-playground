/* Various std::vector algorithms
 *
 *
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include "array_utils.h"

void printVec(std::vector<int> v) {
    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << '\n';
}

auto main() -> int {
    // Intialization of vector
    std::vector<int> a;                             // Empty vector
    std::vector<int> b(10);                         // Vector of size 5, reserves memory for 10 elements, but all elements are uninitialized, same b.reserve(10)
    std::vector<int> c(10, 0);                      // Vector with 10 elements, all initialized to 0
    std::vector<int> v{5, 4, 2, 1, 3, 8, 9, 7, 6};  // Vector with intializer list

    std::vector<int> d(v);                           // Copying the vector v to d
    std::vector<int> e(v.begin() + 2, v.end() - 1);  // Copying the vector v from 3rd element to 2nd last element

    // Filling the vector with values
    std::fill(b.begin(), b.end(), 1);        // Fill the vector with 1
                                             // .begin() pints to first element, .end() points after the last element
    std::iota(c.begin(), c.begin() + 5, 2);  // Fill the vector with 2, 3, 4,5,6 ,0,0...

    printVec(b);
    printVec(c);
    printVec(v);
    printVec(d);
    printVec(e);

    // sorting the array
    std::sort(v.begin(), v.end());
    std::cout << "Array after sorting: " << '\n';
    printVec(v);
    // rotating the subarray within the array
    /*  The array elements between the first and last argument of the function will be rotated.
     *  the new first element of the subarray will be the second argument of the function,
     *  the subarray between second and last argument will be moved to the beginning of the subarray, and
     *  the subarray between the first argument and the second argument will be moved to the end of the subarray.
     */
    std::rotate(v.begin() + 2, v.begin() + 4, v.begin() + 7);
    std::cout << "Array after rotating: " << '\n';
    printVec(v);
    // stable partitioning
    /*  The array elements between the first and last argument of the function will be partitioned.
     *  The elements that satisfy the condition of the function will be moved to the beginning of the subarray,
     *  and the elements that do not satisfy the condition of the function will be moved to the end of the subarray.
     */
    std::stable_partition(v.begin(), v.end(), [](int i) { return i % 2 == 0; });
    std::cout << "Array after partitioning: " << '\n';
    printVec(v);

    // stable partitioning of the subarray wuthin the array
    std::sort(v.begin(), v.end());  // sort first
    std::stable_partition(v.begin() + 2, v.begin() + 6, [](int i) { return i % 2 == 0; });
    std::cout << "Array after partitioning the subarray: " << '\n';
    printVec(v);

    // Random shuffle
    shuffle(v);
    std::cout << "Array after shuffling: " << '\n';
    printVec(v);

    // Sorting smallest 3 elements of the array
    /* Partial sorting of the array can be used to gather the smallest N elements of the array at the beginning of the array, pushing the rest of the elements to the end of the array. */
    std::partial_sort(v.begin(), v.begin() + 3, v.end());  // sort the smallest 3 elements
    std::cout << "Array after sorting the smallest 3 elements: " << '\n';
    printVec(v);

    /* Another approach to use Nth element algo in combination of std::sort to sort the smallest N elements of the array */
    /* Use Nth element algo in combination of std::sort to sort the smallest N elements of the array */
    shuffle(v);
    std::nth_element(v.begin(), v.begin() + 2, v.end());  // 3rd smallest element is at 3rd position
    std::cout << "Array after Nth element" << '\n';
    printVec(v);
    std::cout << "Array after sorting the smallest 3 elements: " << '\n';
    std::sort(v.begin(), v.begin() + 2);  // sort the smallest 3 elements
    printVec(v);
    return 0;
}
