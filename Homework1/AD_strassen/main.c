#include <stdio.h>

#include "test.h"
#include "matrix.h"
#include "strassen.h"

int main(int argc, char *argv[]) {


  // squared matrices
  
  printf(" Squared matrices:\n");
  size_t n = 1 << 11;

  float **A = allocate_random_matrix(n, n);
  float **B = allocate_random_matrix(n, n);
  float **C0 = allocate_matrix(n, n);
  float **C1 = allocate_matrix(n, n);
  float **C2 = allocate_matrix(n, n);

  printf("n\tStrassen's Alg.\tOptimized ver.\tNaive Alg.\tSame result\n");
  for (size_t j = 1; j <= n; j *= 2) {

    printf("%ld\t", j);
    fflush(stdout);

    printf("%lf\t", test(strassen_matrix_multiplication, C1, A, B, j, j, j));
    fflush(stdout);
    printf("%lf\t", test(strassen_matrix_multiplication_optim, C2, A, B, j, j, j));
    fflush(stdout);
    printf("%lf\t", test(naive_matrix_multiplication, C0, A, B, j, j, j));
    fflush(stdout);
    printf("%d\t", same_matrix((float const *const *const)C0,
                               (float const *const *const)C1, j, j));
    printf("%d\n", same_matrix((float const *const *const)C0,
                               (float const *const *const)C2, j, j));
  }

  deallocate_matrix(A, n);
  deallocate_matrix(B, n);
  deallocate_matrix(C0, n);
  deallocate_matrix(C1, n);
  deallocate_matrix(C2, n);

  // rectangular matrices

  printf("\n\n Rectangular matrices:\n");
  n = 1370;
  size_t m = 2179;
  size_t p = 2001;

  A = allocate_random_matrix(n, m);
  B = allocate_random_matrix(m, p);
  C0 = allocate_matrix(n, p);
  C1 = allocate_matrix(n, p);
  C2 = allocate_matrix(n, p);

  printf("\tStrassen's Alg.\tOptimized ver.\tNaive Alg.\tSame result\n");
  printf("\t");

  printf("%lf\t", test(strassen_matrix_multiplication, C1, A, B, n, m, p));
  fflush(stdout);
  printf("%lf\t", test(strassen_matrix_multiplication_optim, C2, A, B, n, m, p));
  fflush(stdout);
  printf("%lf\t", test(naive_matrix_multiplication, C0, A, B, n, m, p));
  fflush(stdout);
  printf("%d\t", same_matrix((float const *const *const)C0,
                      (float const *const *const)C1, n, p));
  printf("%d\n", same_matrix((float const *const *const)C0,
                      (float const *const *const)C2, n, p));

  return 0;
}
