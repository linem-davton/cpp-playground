#include "matrices.h"
#include <gtest/gtest.h>

TEST(MatrixTest, MatrixGen) {
  const int N1 = 10;
  const int M1 = 10;
  const int min_val = 1;
  const int max_val = 99;
  const mat::MatrixInt matrix1 =
      mat::generateRandomMatrix({N1, M1}, {min_val, max_val});

  EXPECT_EQ(matrix1.size(), N1);
  EXPECT_EQ(matrix1[0].size(), M1);
}
TEST(MatrixTest, MatrixMul) {
  std::vector<std::vector<int>> A = {{1, 2}, {3, 4}};

  std::vector<std::vector<int>> B = {{5, 6}, {7, 8}};

  // Expected result of A * B
  std::vector<std::vector<int>> expected = {{19, 22}, {43, 50}};

  const auto result = mat::matrixMultiply(A, B, {2, 2}, {2, 2});
  EXPECT_EQ(result.value(), expected);
}
