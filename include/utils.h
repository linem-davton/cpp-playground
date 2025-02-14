#pragma once

#include <iostream>
#include <vector>
template <typename T>
void printMap(T map) {
    for (const auto& pair : map) {
        std::cout << "Key: " << pair.first << " Val: " << pair.second << "\n";
    }
}

template <typename T>
void printVec(const std::vector<T>& vec) {
    for (const T& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << '\n';
}
