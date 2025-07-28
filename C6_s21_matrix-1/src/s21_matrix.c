#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = OK;
  if (rows > 0 && columns > 0) {
    (result->rows) = rows;
    (result->columns) = columns;
    (result->matrix) = calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; ++i)
      (result->matrix[i]) = calloc(columns, sizeof(double));
  } else {
    status = FAIL;
    (result->rows) = 0;
    (result->columns) = 0;
  }
  return status;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->rows > 0 && A->columns > 0) {
    for (int i = 0; i < (A->rows); ++i) free(A->matrix[i]);
    free(A->matrix);
    (A->rows) = (A->columns) = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = SUCCESS;
  if ((A->rows) != (B->rows) || (A->columns) != (B->columns)) {
    status = FAILURE;
  } else if ((A->rows) <= 0 || (A->columns) <= 0) {
    status = FAILURE;
  } else {
    for (int i = 0; (i < (A->rows) && status == SUCCESS); ++i) {
      for (int j = 0; (j < (A->columns) && status == SUCCESS); ++j) {
        if ((A->matrix[i][j]) - (B->matrix[i][j]) > s21_EPS) status = FAILURE;
      }
    }
  }
  return status;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  if (((A->rows) <= 0) || ((B->rows) <= 0) || ((A->columns) <= 0) ||
      ((B->columns) <= 0)) {
    status = FAIL;
  } else if ((A->rows) == (B->rows) && (A->columns) == (B->columns)) {
    status = s21_create_matrix(A->rows, A->columns, result);
    if (status == OK) {
      for (int i = 0; i < (A->rows); ++i) {
        for (int j = 0; j < (A->columns); ++j)
          (result->matrix[i][j]) = (A->matrix[i][j]) + (B->matrix[i][j]);
      }
    }
  } else {
    status = ERROR;
  }
  return status;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  if (((A->rows) <= 0) || ((B->rows) <= 0) || ((A->columns) <= 0) ||
      ((B->columns) <= 0)) {
    status = FAIL;
  } else if ((A->rows) == (B->rows) && (A->columns) == (B->columns)) {
    status = s21_create_matrix(A->rows, A->columns, result);
    if (status == OK) {
      for (int i = 0; i < (A->rows); ++i) {
        for (int j = 0; j < (A->columns); ++j)
          (result->matrix[i][j]) = (A->matrix[i][j]) - (B->matrix[i][j]);
      }
    }
  } else {
    status = ERROR;
  }
  return status;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = OK;
  status = s21_create_matrix(A->rows, A->columns, result);
  if (status == OK) {
    for (int i = 0; i < (A->rows); ++i) {
      for (int j = 0; j < (A->columns); ++j)
        (result->matrix[i][j]) = (A->matrix[i][j]) * number;
    }
  }
  return status;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  if (((A->rows) <= 0) || ((B->rows) <= 0) || ((A->columns) <= 0) ||
      ((B->columns) <= 0)) {
    status = FAIL;
  } else if ((A->columns) == (B->rows)) {
    status = s21_create_matrix(A->rows, B->columns, result);
    if (status == OK) {
      for (int i = 0; i < (result->rows); ++i) {
        for (int j = 0; j < (result->columns); ++j) {
          (result->matrix[i][j]) = 0;
          for (int k = 0; k < (B->rows); ++k)
            (result->matrix[i][j]) += (A->matrix[i][k]) * (B->matrix[k][j]);
        }
      }
    }
  } else {
    status = ERROR;
  }
  return status;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = OK;
  status = s21_create_matrix(A->columns, A->rows, result);
  if (status == OK) {
    for (int i = 0; i < (A->columns); ++i) {
      for (int j = 0; j < (A->rows); ++j)
        (result->matrix[i][j]) = (A->matrix[j][i]);
    }
  }
  return status;
}

int s21_determinant(matrix_t *A, double *result) {
  int status = OK;
  if (A == NULL || A->matrix == NULL || (A->rows) <= 0 || (A->columns) <= 0) {
    status = FAIL;
  } else if ((A->rows) != (A->columns)) {
    status = ERROR;
  } else {
    (*result) = 0;
    if ((A->rows) == 1) {
      (*result) = A->matrix[0][0];
    } else if (A->rows == 2) {
      (*result) = (A->matrix[0][0]) * (A->matrix[1][1]);
      (*result) -= (A->matrix[0][1]) * (A->matrix[1][0]);
    } else {
      double sign = 1.0, res = 0;
      for (int j = 0; j < (A->columns); ++j) {
        s21_calc_minor(A, 0, j, &res);
        (*result) += sign * (A->matrix[0][j]) * res;
        sign *= -1.0;
      }
    }
  }
  return status;
}

void s21_calc_minor(matrix_t *A, int x, int y, double *res) {
  matrix_t tmp = {0};
  int status = s21_create_matrix((A->rows) - 1, (A->columns) - 1, &tmp);
  if (status == OK) {
    int ii = 0, jj = 0;
    for (int i = 0; i < (A->rows); ++i) {
      for (int j = 0; j < (A->columns); ++j) {
        if (i == x || j == y) continue;
        if (ii >= tmp.rows) break;
        if (jj >= tmp.columns) {
          ++ii;
          jj = 0;
        }
        tmp.matrix[ii][jj] = (A->matrix[i][j]);
        ++jj;
      }
    }
    s21_determinant(&tmp, res);
    s21_remove_matrix(&tmp);
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = OK;
  if (A == NULL || A->matrix == NULL || (A->rows) <= 0 || (A->columns) <= 0) {
    status = FAIL;
  } else if ((A->rows) != (A->columns)) {
    status = ERROR;
  } else {
    status = s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < (A->columns); ++i) {
      for (int j = 0; j < (A->rows); ++j) {
        double tmp = 0;
        s21_calc_minor(A, i, j, &tmp);
        if ((i + j) % 2 == 1) {
          (result->matrix[i][j]) = -tmp;
        } else {
          (result->matrix[i][j]) = tmp;
        }
      }
    }
  }
  return status;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = OK;
  if (A == NULL || A->matrix == NULL || (A->rows) <= 0 || (A->columns) <= 0) {
    status = FAIL;
  } else {
    double det = 0;
    status = s21_determinant(A, &det);
    if (status == OK && det != 0) {
      matrix_t tmp = {0}, transp = {0};
      det = 1.0 / det;
      s21_calc_complements(A, &tmp);
      s21_transpose(&tmp, &transp);
      s21_mult_number(&transp, det, result);
      s21_remove_matrix(&tmp);
      s21_remove_matrix(&transp);
    } else {
      status = ERROR;
    }
  }
  return status;
}