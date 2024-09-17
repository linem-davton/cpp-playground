#include "matrices.h"
#include <gtest/gtest.h>

TEST(MatrixTest, MatrixMultiply) {
  const int N1 = 1000;
  const int M1 = 1000;
  const int N2 = 1000;
  const int M2 = 1000;
  const int min_val = 1;
  const int max_val = 99;

  const mat::MatrixInt matrix1 =
      mat::generateRandomMatrix({N1, M1}, {min_val, max_val});
  const mat::MatrixInt matrix2 =
      mat::generateRandomMatrix({N2, M2}, {min_val, max_val});

  const auto result = mat::matrixMultiply(matrix1, matrix2, {N1, M1}, {N2, M2});
  if (!result) {
    FAIL();
  }
  SUCCEED();
}
