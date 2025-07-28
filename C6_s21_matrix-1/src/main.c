#include "s21_matrix.h"

int main() {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 1.0;
  A.matrix[0][2] = 1.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 1.0;
  A.matrix[1][2] = 1.0;
  A.matrix[2][0] = 1.0;
  A.matrix[2][1] = 1.0;
  A.matrix[2][2] = 1.0;
  int res = s21_calc_complements(&A, &result);
  printf("%d\n", res);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      printf("%f ", A.matrix[i][j]);
    }
    printf("\n");
  }
  return 0;
}