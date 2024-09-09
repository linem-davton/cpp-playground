// computing matrix multiplication of two random matrices
//
#include <iostream>
#include <optional>
#include <random>
#include <vector>

using std::vector;

struct Dimensions {
  int rows;
  int cols;
};

struct limits {
  int min_val;
  int max_val;
};

// Generate random NxM matrix with values between min_val and max_val
// (inclusive) with uniform distribution
std::vector<std::vector<int>> generateRandomMatrix(Dimensions d, limits l) {
  std::vector<vector<int>> matrix(d.rows, std::vector<int>(d.cols));

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

using VectorInt = std::vector<int>;
using MatrixInt = std::vector<std::vector<int>>;

auto matrixMultiply(MatrixInt A, MatrixInt B, Dimensions ad,
                    Dimensions bd) -> std::optional<std::vector<VectorInt>> {
  if (ad.cols != bd.rows) {
    std::cerr << "Matrix multiplication not possible with given dimensions."
              << std::endl;
    return std::nullopt;
  }

  MatrixInt result(ad.rows, std::vector<int>(bd.cols, 0));
  for (int i = 0; i < ad.rows; ++i) {
    for (int k = 0; k < ad.cols; ++k) { // M1 == N2
      for (int j = 0; j < bd.cols; ++j) {
        result[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  return result;
}

void printMatrix(MatrixInt matrix) {
  for (auto row : matrix) {
    for (auto elem : row) {
      std::cout << elem << " ";
    }
    std::cout << '\n';
  }
}

auto main() -> int {
  // intialize two random matrices

  const int N1 = 1000;
  const int M1 = 1000;
  const int N2 = 1000;
  const int M2 = 1000;
  const int min_val = 1;
  const int max_val = 99;

  MatrixInt matrix1 = generateRandomMatrix({N1, M1}, {min_val, max_val});
  MatrixInt matrix2 = generateRandomMatrix({N2, M2}, {min_val, max_val});

  auto result = matrixMultiply(matrix1, matrix2, {N1, M1}, {N2, M2});
  if (!result) {
    return 1;
  }

  // printMatrix(result.value());
}