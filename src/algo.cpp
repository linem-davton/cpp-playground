#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

void print(std::vector<int> v) {
    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << '\n';
}

template <typename T>
auto shuffle(std::vector<T> v) -> std::vector<T> {
    std::random_device rd;
    std::mt19937 rng(rd());  // Mersenne Twister random number generator
    std::shuffle(v.begin(), v.end(), rng);
    return v;
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
    std::stable_partition(v.begin() + 2, v.begin() + 6, [](int i) { return i % 2 == 0; });
    std::cout << "Array after partitioning the subarray: " << '\n';
    print(v);

    // Random shuffle
    v = shuffle(v);
    std::cout << "Array after shuffling: " << '\n';
    print(v);

    // Sorting smallest 3 elements of the array
    /* Partial sorting of the array can be used to gather the smallest N elements of the array at the beginning of the array, pushing the rest of the elements to the end of the array. */
    std::partial_sort(v.begin(), v.begin() + 3, v.end());  // sort the smallest 3 elements
    std::cout << "Array after sorting the smallest 3 elements: " << '\n';
    print(v);

    /* Another approach to use Nth element algo in combination of std::sort to sort the smallest N elements of the array */
    /* Use Nth element algo in combination of std::sort to sort the smallest N elements of the array */
    v = shuffle(v);
    std::nth_element(v.begin(), v.begin() + 2, v.end());  // 3rd smallest element is at 3rd position
    std::cout << "Array after Nth element" << '\n';
    print(v);
    std::cout << "Array after sorting the smallest 3 elements: " << '\n';
    std::sort(v.begin(), v.begin() + 2);  // sort the smallest 3 elements
    print(v);
    return 0;
}
