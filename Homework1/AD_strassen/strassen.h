#ifndef __STRASSEN__

void strassen_matrix_multiplication(float **C, float const *const *const A,
                                    float const *const *const B, size_t n, size_t m, size_t p);

void strassen_matrix_multiplication_optim(float **C, float const *const *const A,
                                         float const *const *const B, size_t n, size_t m, size_t p);
#endif //__STRASSEN__
