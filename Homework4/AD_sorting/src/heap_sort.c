#include "heap_sort.h"

void heap_sort(void *A, const unsigned int n, 
               const size_t elem_size, 
               total_order leq)
{
    binheap_type* H = build_heap(A, n, n, elem_size, geq_int);

    for(unsigned int i=n-1; i>0; i--){
        extract_min(H); // the function already place the min element at the end of the array
    }
}
