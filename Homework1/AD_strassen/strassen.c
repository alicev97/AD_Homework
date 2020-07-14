#include "matrix.h"
#include<stdio.h>

/*
 * this function performs the element-wise
 * subtraction of B from A and put the resulting
 * sub-matrix in C. The parameters *_f_row and *_f_col
 * represents the first row and the first column,
 * respectively, of the sub-matrix we want to deal with.
 */
void sub_matrix_blocks(float **C, float const *const *const A,
                       float const *const * const B,
                       const size_t C_f_row, const size_t C_f_col,
                       const size_t A_f_row, const size_t A_f_col,
                       const size_t B_f_row, const size_t B_f_col,
                       const size_t n)
{
    for (size_t y = 0; y < n; y++) {
      for (size_t x = 0; x < n; x++) {
          C[y+C_f_row][x+C_f_col] =
               A[y+A_f_row][x+A_f_col] - B[y+B_f_row][x+B_f_col];
      }
    }
}

/*
 * this function performs the element-wise
 * sum of A and B and put the resulting
 * sub-matrix in C. The parameters *_f_row and *_f_col
 * represents the first row and the first column,
 * respectively, of the sub-matrix we want to deal with.
 */
void sum_matrix_blocks(float **C, float const *const *const A,
                       float const *const * const B,
                       const size_t C_f_row, const size_t C_f_col,
                       const size_t A_f_row, const size_t A_f_col,
                       const size_t B_f_row, const size_t B_f_col,
                       const size_t n)
{
    for (size_t y = 0; y < n; y++) {
      for (size_t x = 0; x < n; x++) {
          C[y+C_f_row][x+C_f_col] =
               A[y+A_f_row][x+A_f_col] + B[y+B_f_row][x+B_f_col];
      }
    }
}

/*
 * this function implements the naive algorithm
 * for matrix multiplication between sub-matrixes.
 * The result is placed in the sub-matrix C.
 * The parameters *_f_row and *_f_col
 * represents the first row and the first column,
 * respectively, of the sub-matrix we want to deal with.
 */
void naive_aux(float **C, float const *const *const A,
               float const *const * const B,
               const size_t C_f_row, const size_t C_f_col,
               const size_t A_f_row, const size_t A_f_col,
               const size_t B_f_row, const size_t B_f_col,
               const size_t n)
{
  for (size_t y = 0; y < n; y++) {
    for (size_t x = 0; x < n; x++) {
      float value = 0.0;
      for (size_t z = 0; z < n; z++) {
        value += A[y + A_f_row][z + A_f_col]*B[z + B_f_row][x + B_f_col];
      }

      C[y + C_f_row][x + C_f_col] = value;
    }
  }
}

/*
 * this function implements the Strassen's algorithm
 * for matrix multiplication between sub-matrixes.
 * The result is placed in the sub-matrix C.
 * The parameters *_f_row and *_f_col
 * represents the first row and the first column,
 * respectively, of the sub-matrix we want to deal with.
 */
void strassen_aux(float **C, float const *const *const A,
                  float const *const * const B,
                  const size_t C_f_row, const size_t C_f_col,
                  const size_t A_f_row, const size_t A_f_col,
                  const size_t B_f_row, const size_t B_f_col,
                  const size_t n)
{
   if (n <= 128) {
        naive_aux(C, A, B,
                  C_f_row, C_f_col,
                  A_f_row, A_f_col,
                  B_f_row, B_f_col,
                  n);

        return;
    }
    
    // if n in odd
    if(n%2 == 1)
    {
      // make matrices even
      float **A_new = even_matrix(A, A_f_row, A_f_col, n);
      float **B_new = even_matrix(B, B_f_row, B_f_col, n);
      float **C_new = allocate_matrix(n+1,n+1);
      
      // recursive call on even matrices
      strassen_aux(C_new, (const float * const* const) A_new, (const float * const* const) B_new,
                  0, 0, 0, 0, 0, 0, n+1);

      // copy C_new back into C
      for(size_t i = C_f_row; i < C_f_row + n; i++){
        for(size_t j = C_f_col; j < C_f_col + n; j++){
          C[i][j] = C_new[i][j];
        }
      }

      deallocate_matrix(A_new, n);
      deallocate_matrix(B_new, n);
      deallocate_matrix(C_new, n);
      return;
    }
    
    // here n is always even! we can use Strassen's algorithm

    size_t n2 = n/2; // This is the size of the blocks

    float ***S = (float ***)malloc(sizeof(float **) * 10);
    for (size_t i = 0; i < 10; i++) {
        S[i] = allocate_matrix(n2, n2);
    }

    float ***P = (float ***)malloc(sizeof(float **) * 7);
    for (size_t i = 0; i < 7; i++) {
        P[i] = allocate_matrix(n2, n2);
    }

    // S1 = B12 - B22
    sub_matrix_blocks(S[0], B, B,
                      0, 0,
                      B_f_row, B_f_col + n2,
                      B_f_row + n2, B_f_col + n2,
                      n2);

    // P1 = A11 x S1
    strassen_aux(P[0], A, (const float* const *const) S[0],
                 0, 0,
                 A_f_row, A_f_col,
                 0, 0,
                 n2);

    // S2 = A11 + A12
    sum_matrix_blocks(S[1], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row, A_f_col + n2,
                      n2);


    // P2 = S2 x B22
    strassen_aux(P[1], (const float* const *const) S[1], B,
                 0, 0,
                 0, 0,
                 B_f_row + n2, B_f_col + n2,
                 n2);

    // S3 = A21 + A22
    sum_matrix_blocks(S[2], A, A,
                      0, 0,
                      A_f_row + n2, A_f_col,
                      A_f_row + n2, A_f_col + n2,
                      n2);

    // P3 = S3 x B11
    strassen_aux(P[2], (const float* const *const) S[2], B,
                 0, 0,
                 0, 0,
                 B_f_row, B_f_col,
                 n2);

    // S4 = B21 - B11
    sub_matrix_blocks(S[3], B, B,
                      0, 0,
                      B_f_row + n2, B_f_col,
                      B_f_row, B_f_col,
                      n2);

    // P4 = A22 x S4
    strassen_aux(P[3], A, (const float* const *const) S[3],
                 0, 0,
                 A_f_row + n2, A_f_col + n2,
                 0, 0,
                 n2);

    // S5 = A11 + A22
    sum_matrix_blocks(S[4], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row + n2, A_f_col + n2,
                      n2);

    // S6 = B11 + B22
    sum_matrix_blocks(S[5], B, B,
                      0, 0,
                      B_f_row, B_f_col,
                      B_f_row + n2, B_f_col + n2,
                      n2);

    // P5 = S5 x S6
    strassen_aux(P[4], (const float* const *const) S[4],
                 (const float* const *const) S[5],
                 0, 0,
                 0, 0,
                 0, 0,
                 n2);

    // S7 = A12 - A22
    sub_matrix_blocks(S[6], A, A,
                      0, 0,
                      A_f_row, A_f_col + n2,
                      A_f_row + n2, A_f_col + n2,
                      n2);

    // S8 = B21 + B22
    sum_matrix_blocks(S[7], B, B,
                      0, 0,
                      B_f_row + n2, B_f_col,
                      B_f_row + n2, B_f_col + n2,
                      n2);

    // P6 = S7 x S8
    strassen_aux(P[5], (const float* const *const) S[6],
                 (const float* const *const) S[7],
                 0, 0,
                 0, 0,
                 0, 0,
                 n2);

    // S9 = A11 - A21
    sub_matrix_blocks(S[8], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row + n2, A_f_col,
                      n2);

    // S10 = B11 + B12
    sum_matrix_blocks(S[9], B, B,
                      0, 0,
                      B_f_row, B_f_col,
                      B_f_row, B_f_col + n2,
                      n2);

    // P7 = S9 x S10
    strassen_aux(P[6], (const float* const *const) S[8],
                 (const float* const *const) S[9],
                 0, 0,
                 0, 0,
                 0, 0,
                 n2);

    // C11 = P5 + P4 - P2 + P6
    sum_matrix_blocks(C, (const float* const *const) P[4],
                      (const float* const *const) P[3],
                      C_f_row, C_f_col,
                      0, 0,
                      0, 0,
                      n2);
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[1],
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      n2);
    sum_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[5],
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      n2);

    // C12 = P1 + P2
    sum_matrix_blocks(C, (const float* const *const) P[0],
                      (const float* const *const) P[1],
                      C_f_row, C_f_col+n2,
                      0, 0,
                      0, 0,
                      n2);

    // C21 = P3 + P4
    sum_matrix_blocks(C, (const float* const *const) P[2],
                      (const float* const *const) P[3],
                      C_f_row+n2, C_f_col,
                      0, 0,
                      0, 0,
                      n2);

    // C22 = P5 + P1 - P3 - P7
    sum_matrix_blocks(C, (const float* const *const) P[4],
                      (const float* const *const) P[0],
                      C_f_row+n2, C_f_col+n2,
                      0, 0,
                      0, 0,
                      n2);
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[2],
                      C_f_row+n2, C_f_col+n2,
                      C_f_row+n2, C_f_col+n2,
                      0, 0,
                      n2);
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[6],
                      C_f_row+n2, C_f_col+n2,
                      C_f_row+n2, C_f_col+n2,
                      0, 0,
                      n2);
}


/*
 * this functions is exclusively meant to provide an
 * easy to use API
 */
void strassen_matrix_multiplication(float **C, float const *const *const A,
                                    float const *const *const B, size_t n, size_t m, size_t p)
{
  // if squared matrices
  if((n == m) && (m ==p)){
    strassen_aux(C, A, B,
               0, 0,
               0, 0,
               0, 0,
               n);
    return;
  }

  // if not squared matrices

  // find the min dimension
  size_t min = n;
  if(m < min){
    min = m;
  }
  if(p < min){
    min = p;
  }

  // new dim
  size_t n_new = n;
  size_t m_new = m;
  size_t p_new = p;
  int r;
  r = n%min;
  if(r != 0){
    n_new += (min -r);
  }
  r = m%min;
  if(r != 0){
    m_new += (min -r);
  }
  r = p%min;
  if(r != 0){
    p_new += (min-r);
  }

  // resize matrix
  float **A_new = resize(A, n, m, n_new, m_new);
  float **B_new = resize(B, m, p, m_new, p_new);
  float **C_new = allocate_zero_matrix(n_new, p_new);

  // apply the naive algorithm on blocks and multiply these blocks with strassen algorithm
  for(size_t i = 0; i < n_new; i += min){
    for(size_t j = 0; j < p_new; j += min){
      for(size_t z = 0; z < m_new; z += min){

        float **T = allocate_matrix(min, min);
        strassen_aux(T, (const float * const* const) A_new, (const float * const* const) B_new, 0, 0, i, z, z, j, min);
        sum_matrix_blocks(C_new, (const float * const* const) C_new, (const float * const* const) T, i, j,
                            i, j, 0, 0, min);
        deallocate_matrix(T, min);
      }
    }
  }
 
  // copy back c_new into C
  for (size_t i = 0; i < n; i++){
    for(size_t j = 0; j < p; j++){
      C[i][j]= C_new[i][j];
    }
  }

  deallocate_matrix(A_new, n);
  deallocate_matrix(B_new, m);
  deallocate_matrix(C_new, n);

}



/*
 * this function implements the Strassen's algorithm
 * for matrix multiplication between sub-matrixes.
 * It reduce the memory allocation by reusing
 * the matrices S and P
 * The result is placed in the sub-matrix C.
 * The parameters *_f_row and *_f_col
 * represents the first row and the first column,
 * respectively, of the sub-matrix we want to deal with.
 */
void strassen_optim_aux(float **C, float const *const *const A,
                        float const *const * const B,
                        const size_t C_f_row, const size_t C_f_col,
                        const size_t A_f_row, const size_t A_f_col,
                        const size_t B_f_row, const size_t B_f_col,
                        const size_t n)
{
   if (n <= 128) {
        naive_aux(C, A, B,
                  C_f_row, C_f_col,
                  A_f_row, A_f_col,
                  B_f_row, B_f_col,
                  n);

        return;
    }
    
    // if n in odd
    if(n%2 == 1)
    {
      // make matrices even
      float **A_new = even_matrix(A, A_f_row, A_f_col, n);
      float **B_new = even_matrix(B, B_f_row, B_f_col, n);
      float **C_new = allocate_matrix(n+1,n+1);
      
      // recursive call on even matrices
      strassen_optim_aux(C_new, (const float * const* const) A_new, (const float * const* const) B_new,
                  0, 0, 0, 0, 0, 0, n+1);

      // copy C_new back into C
      for(size_t i = C_f_row; i < C_f_row + n; i++){
        for(size_t j = C_f_col; j < C_f_col + n; j++){
          C[i][j] = C_new[i][j];
        }
      }

      deallocate_matrix(A_new, n);
      deallocate_matrix(B_new, n);
      deallocate_matrix(C_new, n);
      return;
    }
    
    // here n is always even! we can use Strassen's algorithm

    size_t n2 = n/2; // This is the size of the blocks

    float ***S = (float ***)malloc(sizeof(float **) * 2);
    for (size_t i = 0; i < 2; i++) {
        S[i] = allocate_matrix(n2, n2);
    }

    float ***P = (float ***)malloc(sizeof(float **) * 7);
    for (size_t i = 0; i < 7; i++) {
        P[i] = allocate_matrix(n2, n2);
    }

    // S1 = B12 - B22
    sub_matrix_blocks(S[0], B, B,
                      0, 0,
                      B_f_row, B_f_col + n2,
                      B_f_row + n2, B_f_col + n2,
                      n2);

    // P1 = A11 x S1
    strassen_aux(P[0], A, (const float* const *const) S[0],
                 0, 0,
                 A_f_row, A_f_col,
                 0, 0,
                 n2);

    // S2 = A11 + A12
    sum_matrix_blocks(S[0], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row, A_f_col + n2,
                      n2);


    // P2 = S2 x B22
    strassen_aux(P[1], (const float* const *const) S[0], B,
                 0, 0,
                 0, 0,
                 B_f_row + n2, B_f_col + n2,
                 n2);

    // C12 = P1 + P2
    sum_matrix_blocks(C, (const float* const *const) P[0],
                      (const float* const *const) P[1],
                      C_f_row, C_f_col+n2,
                      0, 0,
                      0, 0,
                      n2);

    // S3 = A21 + A22
    sum_matrix_blocks(S[0], A, A,
                      0, 0,
                      A_f_row + n2, A_f_col,
                      A_f_row + n2, A_f_col + n2,
                      n2);

    // P3 = S3 x B11
    strassen_aux(P[2], (const float* const *const) S[0], B,
                 0, 0,
                 0, 0,
                 B_f_row, B_f_col,
                 n2);

    // S4 = B21 - B11
    sub_matrix_blocks(S[0], B, B,
                      0, 0,
                      B_f_row + n2, B_f_col,
                      B_f_row, B_f_col,
                      n2);

    // P4 = A22 x S4
    strassen_aux(P[3], A, (const float* const *const) S[0],
                 0, 0,
                 A_f_row + n2, A_f_col + n2,
                 0, 0,
                 n2);

    // C21 = P3 + P4
    sum_matrix_blocks(C, (const float* const *const) P[2],
                      (const float* const *const) P[3],
                      C_f_row+n2, C_f_col,
                      0, 0,
                      0, 0,
                      n2);

    // S5 = A11 + A22
    sum_matrix_blocks(S[0], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row + n2, A_f_col + n2,
                      n2);

    // S6 = B11 + B22
    sum_matrix_blocks(S[1], B, B,
                      0, 0,
                      B_f_row, B_f_col,
                      B_f_row + n2, B_f_col + n2,
                      n2);

    // P5 = S5 x S6
    strassen_aux(P[4], (const float* const *const) S[0],
                 (const float* const *const) S[1],
                 0, 0,
                 0, 0,
                 0, 0,
                 n2);

    // S7 = A12 - A22
    sub_matrix_blocks(S[0], A, A,
                      0, 0,
                      A_f_row, A_f_col + n2,
                      A_f_row + n2, A_f_col + n2,
                      n2);

    // S8 = B21 + B22
    sum_matrix_blocks(S[1], B, B,
                      0, 0,
                      B_f_row + n2, B_f_col,
                      B_f_row + n2, B_f_col + n2,
                      n2);

    // P6 = S7 x S8
    strassen_aux(P[5], (const float* const *const) S[0],
                 (const float* const *const) S[1],
                 0, 0,
                 0, 0,
                 0, 0,
                 n2);

    // C11 = P5 + P4 - P2 + P6
    sum_matrix_blocks(C, (const float* const *const) P[4],
                      (const float* const *const) P[3],
                      C_f_row, C_f_col,
                      0, 0,
                      0, 0,
                      n2);
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[1],
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      n2);
    sum_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[5],
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      n2);

    // S9 = A11 - A21
    sub_matrix_blocks(S[0], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row + n2, A_f_col,
                      n2);

    // S10 = B11 + B12
    sum_matrix_blocks(S[1], B, B,
                      0, 0,
                      B_f_row, B_f_col,
                      B_f_row, B_f_col + n2,
                      n2);

    // P7 = S9 x S10
    strassen_aux(P[1], (const float* const *const) S[0],
                 (const float* const *const) S[1],
                 0, 0,
                 0, 0,
                 0, 0,
                 n2);

    // C22 = P5 + P1 - P3 - P7
    sum_matrix_blocks(C, (const float* const *const) P[4],
                      (const float* const *const) P[0],
                      C_f_row+n2, C_f_col+n2,
                      0, 0,
                      0, 0,
                      n2);
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[2],
                      C_f_row+n2, C_f_col+n2,
                      C_f_row+n2, C_f_col+n2,
                      0, 0,
                      n2);
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[1],
                      C_f_row+n2, C_f_col+n2,
                      C_f_row+n2, C_f_col+n2,
                      0, 0,
                      n2);
}


/*
 * this functions is exclusively meant to provide an
 * easy to use API
 */
void strassen_matrix_multiplication_optim(float **C, float const *const *const A,
                                         float const *const *const B, size_t n, size_t m, size_t p)
{
  // if squared matrices
  if((n == m) && (m ==p)){
    strassen_optim_aux(C, A, B,
                        0, 0,
                        0, 0,
                        0, 0,
                        n);
    return;
  }
  // if not squared matrices

  // find the min dimension
  size_t min = n;
  if(m < min){
    min = m;
  }
  if(p < min){
    min = p;
  }

  // new dim
  size_t n_new = n;
  size_t m_new = m;
  size_t p_new = p;
  int r;
  r = n%min;
  if(r != 0){
    n_new += (min -r);
  }
  r = m%min;
  if(r != 0){
    m_new += (min -r);
  }
  r = p%min;
  if(r != 0){
    p_new += (min-r);
  }

  // resize matrix
  float **A_new = resize(A, n, m, n_new, m_new);
  float **B_new = resize(B, m, p, m_new, p_new);
  float **C_new = allocate_zero_matrix(n_new, p_new);

  // apply the naive algorithm on blocks and multiply these blocks with strassen algorithm
  for(size_t i = 0; i < n_new; i += min){
    for(size_t j = 0; j < p_new; j += min){
      for(size_t z = 0; z < m_new; z += min){

        float **T = allocate_matrix(min, min);
        strassen_optim_aux(T, (const float * const* const) A_new, (const float * const* const) B_new, 0, 0, i, z, z, j, min);
        sum_matrix_blocks(C_new, (const float * const* const) C_new, (const float * const* const) T, i, j,
                            i, j, 0, 0, min);
        deallocate_matrix(T, min);
      }
    }
  }
 
  // copy back c_new into C
  for (size_t i = 0; i < n; i++){
    for(size_t j = 0; j < p; j++){
      C[i][j]= C_new[i][j];
    }
  }

  deallocate_matrix(A_new, n);
  deallocate_matrix(B_new, m);
  deallocate_matrix(C_new, n);

}

