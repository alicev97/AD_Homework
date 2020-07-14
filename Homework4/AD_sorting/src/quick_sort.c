#include "quick_sort.h"

#define ADDR(A, elem) (A+((elem)*elem_size))

unsigned int partition(void *A, const unsigned int n,
                        const size_t elem_size,
                        total_order leq,
                        const unsigned int l,
                        const unsigned int r,
                        const unsigned int p)
{
    unsigned int i = l;
    unsigned int j = r;

    swap(ADDR(A, i), ADDR(A, p), elem_size); // swap the pivot p and the left-most element in A
    i++;
    while(i <= j){
        if(!leq(ADDR(A, i),ADDR(A, p))){ // if A[i] > A[p]
            swap(ADDR(A, i), ADDR(A, j), elem_size); // swap A[i] and A[j]
            j--; // decrease j
        } else { // if A[i] < A[p]
            i++; // increase i
        }
    }
    swap(ADDR(A,p), ADDR(A, j), elem_size); // swap p and A[j]
    return j;

}

void quick_sort_aux(void *A, const unsigned int n, 
                const size_t elem_size, 
                total_order leq,
                const unsigned int l,
                const unsigned int r)
{
    if (l < r){
        unsigned int p = partition(A, n, elem_size, leq, l, r, l);
        if(p>0){
        quick_sort_aux(A, n, elem_size, leq, l, p-1);
        }
        if(p<n){
        quick_sort_aux(A, n, elem_size, leq, p+1, r);
        }
    }
}

void quick_sort(void *A, const unsigned int n, 
                const size_t elem_size, 
                total_order leq)
{
    quick_sort_aux(A, n, elem_size, leq, 0, n);
}