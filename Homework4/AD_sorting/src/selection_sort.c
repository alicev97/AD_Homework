#include "selection_sort.h"

#define ADDR(A, elem) (A+((elem)*elem_size))

void selection_sort(void *A, const unsigned int n, 
                    const size_t elem_size, 
                    total_order leq)
{
    unsigned int max_j;

    for(unsigned int i = n-1; i > 0; i--){
        max_j = 0;
        for(unsigned int j = 1; j <= i; j++){
            if(!leq(ADDR(A,j), ADDR(A, max_j))){
                max_j = j;
            }
        }
        swap(ADDR(A, i), ADDR(A, max_j), elem_size);
    }
}