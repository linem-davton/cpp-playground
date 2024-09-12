#include "matrices.h"

using namespace mat;
// Generate random NxM matrix with values between min_val and max_val
// (inclusive) with uniform distribution

auto generateRandomMatrix(const Dimensions d, const limits l) -> MatrixInt {
  MatrixInt matrix(d.rows, VectorInt(d.cols, 0));
  matrix.reserve(d.rows);

  // Random number generation
  std::random_device rd;
  std::mt19937 gen(rd()); // Mersenne Twister engine
  std::uniform_int_distribution<> dis(l.min_val, l.max_val);

  // Fill the matrix with random numbers
  for (int i = 0; i < d.rows; ++i) {
    for (int j = 0; j < d.cols; ++j) {
      matrix[i][j] = dis(gen);
    }
  }

  return matrix;
}

auto matrixMultiply(const MatrixInt &A, const MatrixInt &B, const Dimensions ad,
                    const Dimensions bd) -> std::optional<MatrixInt> {
  if (ad.cols != bd.rows) {
    std::cerr << "Matrix multiplication not possible with given dimensions."
              << std::endl;
    return std::nullopt;
  }

  // Cache friendly matrix multiplication, inner loop accesses elements
  // sequentially with stride 1
  MatrixInt result(ad.rows, std::vector<int>(bd.cols, 0));
  for (int i = 0; i < ad.rows; ++i) {
    for (int k = 0; k < ad.cols; ++k) {
      for (int j = 0; j < bd.cols; ++j) {
        result[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  return result;
}

void printMatrix(const MatrixInt &matrix) {
  for (const auto &row : matrix) {
    for (const auto &elem : row) {
      std::cout << elem << " ";
    }
    std::cout << '\n';
  }
}
