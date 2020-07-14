#include "insertion_sort.h"


#define ADDR(A, elem) (A+((elem)*elem_size))

void insertion_sort(void *A, const unsigned int n, 
                    const size_t elem_size, 
                    total_order leq)
{
    unsigned int j;
    for(unsigned int i = 1; i<n; i++){
        j = i;
        while(j>0 && leq(ADDR(A, j), ADDR(A, j-1))){
            swap(ADDR(A, j), ADDR(A, j-1), elem_size);
            j--;
        }
    }
}