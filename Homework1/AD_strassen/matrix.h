#ifndef __MATRIX__
#include <stdlib.h>


void naive_matrix_multiplication(float **C, float const *const *const A,
                                float const *const *const B,
                                const size_t n, const size_t m, const size_t p);

int same_matrix(float const *const *const A, float const *const *const B,
                const size_t rows, const size_t cols);

float **allocate_matrix(const size_t rows, const size_t cols);
float **allocate_random_matrix(const size_t rows, const size_t cols);
float **allocate_zero_matrix(const size_t rows, const size_t cols);
void deallocate_matrix(float **A, const size_t rows);

float **even_matrix(const float *const *const A, const size_t A_f_row, const size_t A_f_col, const size_t n);
float **resize(const float *const *const A, const size_t rows, 
            const size_t cols, const size_t rows_new, const size_t cols_new);
#endif //__MATRIX__
