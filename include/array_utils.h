#pragma once
#include <iostream>
#include <random>
#include <type_traits>
#include <vector>

template <typename T>
void printVec(const std::vector<T>& vec) {
    for (int elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << '\n';
}
template <typename T>
auto random_vector(int size) -> std::vector<T> {
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Type not supported");
    std::vector<T> v(size);
    std::random_device rd;
    std::mt19937 eng(rd());  // Mersenne Twister random number generator
    // check if T is of type int
    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<int> uniform_dist(0, size);
        for (int i = 0; i < size; i++) {
            v[i] = uniform_dist(eng);
        }
    } else if constexpr (std::is_floating_point_v<T>) {
        std::uniform_real_distribution<double> uniform_dist(0, size);
        for (int i = 0; i < size; i++) {
            v[i] = uniform_dist(eng);
        }
    }
    return v;
}
