#pragma once
#include <iostream>
#include <optional>
#include <random>
#include <vector>

namespace mat {

struct Dimensions {
  int rows;
  int cols;
};

struct limits {
  int min_val;
  int max_val;
};

using VectorInt = std::vector<int>;
using MatrixInt = std::vector<std::vector<int>>;

// Generate random NxM matrix with values between min_val and max_val
// (inclusive) with uniform distribution
auto generateRandomMatrix(const Dimensions d, const limits l) -> MatrixInt;

auto matrixMultiply(const MatrixInt &A, const MatrixInt &B, const Dimensions ad,
                    const Dimensions bd) -> std::optional<MatrixInt>;

void printMatrix(const MatrixInt &matrix);
} // namespace mat
