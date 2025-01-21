#include <algorithm>
#include <iostream>
#include <vector>

void print(std::vector<int> v) {
    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << '\n';
}
auto main() -> int {
    std::vector v = {5, 4, 2, 1, 3, 8, 9, 7, 6};
    // sorting the array
    std::sort(v.begin(), v.end());
    std::cout << "Array after sorting: " << '\n';
    print(v);
    // rotating the subarray within the array
    /*  The array elements between the first and last argument of the function will be rotated.
     *  the new first element of the subarray will be the second argument of the function,
     *  the subarray between second and last argument will be moved to the beginning of the subarray, and
     *  the subarray between the first argument and the second argument will be moved to the end of the subarray.
     */
    std::rotate(v.begin() + 2, v.begin() + 4, v.begin() + 7);
    std::cout << "Array after rotating: " << '\n';
    print(v);
    // stable partitioning
    /*  The array elements between the first and last argument of the function will be partitioned.
     *  The elements that satisfy the condition of the function will be moved to the beginning of the subarray,
     *  and the elements that do not satisfy the condition of the function will be moved to the end of the subarray.
     */
    std::stable_partition(v.begin(), v.end(), [](int i) { return i % 2 == 0; });
    std::cout << "Array after partitioning: " << '\n';
    print(v);
    // stable partitioning of the subarray wuthin the array
    std::sort(v.begin(), v.end());  // sort first
    std::stable_partition(v.begin() + 2, v.begin() + 5, [](int i) { return i % 2 == 0; });
    std::cout << "Array after partitioning the subarray: " << '\n';
    print(v);
    return 0;
}
