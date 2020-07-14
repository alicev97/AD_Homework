#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

// A nxm matrix, B mxp matrix -> C = AxB nxp matrix
void naive_matrix_multiplication(float **C, float const *const *const A,
                                float const *const *const B,
                                const size_t n, const size_t m, const size_t p)
{
  for (size_t y = 0; y < n; y++) {
    for (size_t x = 0; x < p; x++) {
      float value = 0.0;
      for (size_t z = 0; z < m; z++) {
        value += A[y][z]*B[z][x];
      }

      C[y][x] = value;
    }
  }
}

int same_matrix(float const *const *const A, float const *const *const B,
                const size_t rows, const size_t cols) {
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      if (A[i][j] != B[i][j]) {
        return 0;
      }
    }
  }

  return 1;
}

float **allocate_matrix(const size_t rows, const size_t cols) {
  float **M = (float **)malloc(sizeof(float *) * rows);

  for (size_t i = 0; i < rows; i++) {
    M[i] = (float *)malloc(sizeof(float) * cols);
  }

  return M;
}

void deallocate_matrix(float **A, const size_t rows) {
  for (size_t i = 0; i < rows; i++) {
    free(A[i]);
  }

  free(A);
}

float **allocate_random_matrix(const size_t rows, const size_t cols) {
  
  float **A = allocate_matrix(rows, cols);
  
  srand(10);
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      A[i][j] = (rand() - RAND_MAX / 2) % 5;
    }
  }

  return A;
}

float **allocate_zero_matrix(const size_t rows, const size_t cols){
  
  float **M = (float **)calloc(rows, sizeof(float *));

  for (size_t i = 0; i < rows; i++) {
    M[i] = (float *)calloc(cols, sizeof(float));
  }

  return M;
}

float **even_matrix(const float *const *const A, const size_t A_f_row, const size_t A_f_col, const size_t n)
{

  float **T = allocate_matrix(n+1,n+1);

  // copy A
  for(size_t i = 0; i < n; i++){
    for(size_t j = 0; j < n; j++){
      T[i][j] = A[A_f_row+i][A_f_col + j]; 
    }
  } 

  // add 0s on the last rows
  for(size_t j = 0; j <= n; j++){
    T[n][j] = 0;
  } 

  // add 0s on the last col
  for(size_t i = 0; i <= n; i++){    
    T[i][n] = 0;  
  }

  return T;

}


float **resize(const float *const *const A, const size_t rows, 
                            const size_t cols, const size_t rows_new, const size_t cols_new)
{

  float **T = allocate_matrix(rows_new, cols_new);

  // copy A
  for(size_t i = 0; i < rows; i++){
    for(size_t j = 0; j < cols; j++){
      T[i][j] = A[i][j]; 
    }
  }

  // add 0s on the new rows
  for(size_t i = rows; i < rows_new; ++i){
    for(size_t j = 0; j < cols_new; j++){
      T[i][j] = 0;   
    }
  }

  // add 0s on the new cols
  for(size_t j = cols; j < cols_new; j++){
  for(size_t i = 0; i < rows; i++){
      T[i][j] = 0; 
    }
  }

  return T;

}
