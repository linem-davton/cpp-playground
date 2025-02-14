#pragma once
#include <algorithm>
#include <iostream>
#include <random>
#include <type_traits>
#include <vector>
#include "utils.h"

template <typename T>
auto random_vector(int size) -> std::vector<T> {
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Type not supported");
    std::vector<T> v(size);
    std::random_device rd;
    std::mt19937 eng(rd());  // Mersenne Twister random number generator
    // check if T is of type int
    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<int> int_dist(0, size);
        for (int i = 0; i < size; i++) {
            v[i] = int_dist(eng);
        }
    } else if constexpr (std::is_floating_point_v<T>) {
        std::uniform_real_distribution<double> real_dist(1.0, size);
        for (int i = 0; i < size; i++) {
            v[i] = real_dist(eng);
        }
    }
    return v;
}
template <typename T>
auto shuffle(std::vector<T>& v) -> std::vector<T> {
    std::random_device rd;
    std::mt19937 rng(rd());  // Mersenne Twister random number generator
    std::shuffle(v.begin(), v.end(), rng);
    return v;
}
