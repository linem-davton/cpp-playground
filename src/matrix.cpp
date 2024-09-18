// computing matrix multiplication of two random matrices
//

#include "matrices.h"

using namespace mat;

auto main() -> int {
  const int N1 = 1000;
  const int M1 = 1000;
  const int N2 = 1000;
  const int M2 = 1000;
  const int min_val = 1;
  const int max_val = 99;

  const MatrixInt matrix1 = generateRandomMatrix({N1, M1}, {min_val, max_val});
  const MatrixInt matrix2 = generateRandomMatrix({N2, M2}, {min_val, max_val});

  const auto result = matrixMultiply(matrix1, matrix2, {N1, M1}, {N2, M2});
  if (!result) {
    return 1;
  }
  // printMatrix(result.value());
}
