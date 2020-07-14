#include "bubble_sort.h"

#define ADDR(A, elem) (A+((elem)*elem_size))

void bubble_sort(void *A, const unsigned int n, 
                 const size_t elem_size, 
                 total_order leq)
{
    for(unsigned int i = n-1; i > 0; i--){
        for(unsigned int j = 0; j < i; j++){
            if(!leq(ADDR(A, j), ADDR(A, j+1))){ //A[j] > A[j+1]
                swap(ADDR(A,j), ADDR(A, j+1), elem_size);
            }
        }
    }
}