#include "select.h"
#include<stdio.h>

#include "swap.h"

#define ADDR(A, elem) (A+((elem)*elem_size))

void sorting(void *A,
          const size_t elem_size, 
          total_order leq,
          const unsigned int l,
          const unsigned int r)
{
    unsigned int max_j;

    for(unsigned int i = r; i > l; i--){
        max_j = l;
        for(unsigned int j = l+1; j <= i; j++){
            if(!leq(ADDR(A,j), ADDR(A, max_j))){
                max_j = j;
            }
        }
        swap(ADDR(A, i), ADDR(A, max_j), elem_size);
    }
}

unsigned int select_pivot(void *A,
                          const size_t elem_size, 
                          total_order leq,
                          const unsigned int l,
                          const unsigned int r)
{
    if ((r-l) < 10){ // base case
        sorting(A, elem_size, leq, l, r);
        return (l+r)/2;
    }

    const unsigned int chunks = (r-l)/5;
    unsigned int c_l, c_r;

    for(unsigned int c = 0; c < chunks; c++){ // for each chunk
        c_l = l + c*5;
        c_r = l + 4 + c*5;
        sorting(A, elem_size, leq, c_l, c_r); // sort the chunk
        swap(ADDR(A, (c_l + 2)), ADDR(A, (l + c)), elem_size); // place the middle element at the beginning of A
    }
    return select_index_aux(A, elem_size, leq, l, l+chunks-1, l+ chunks/2); // recursive step
}

unsigned int partition2(void *A, const size_t elem_size,
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
        if(!leq(ADDR(A, i),ADDR(A, l))){ // if A[i] > p
            swap(ADDR(A, i), ADDR(A, j), elem_size); // swap A[i] and A[j]
            j--; // decrease j
        } else { // if A[i] < A[p]
            i++; // increase i
        }
    }
    swap(ADDR(A,l), ADDR(A, j), elem_size); // swap p and A[j]
    return j;

}

unsigned int* threewaypartition(void *A,
                                const size_t elem_size, 
                                total_order leq,
                                const unsigned int l,
                                const unsigned int r,
                                const unsigned int p)
{
    swap(ADDR(A,l), ADDR(A, p), elem_size); // swap the pivot p and the left-most considered element
    unsigned int i = l+1;
    unsigned int k = i;
    unsigned int j = r;
    
    while(k <= j){
        if(leq(ADDR(A,k), ADDR(A,l)) && !(leq(ADDR(A,l), ADDR(A,k)))){ // A[k] < p
        	swap(ADDR(A, i), ADDR(A, k), elem_size);
            i++;
            k++;
        }
        else if(!(leq(ADDR(A,k), ADDR(A,l))) && leq(ADDR(A,l), ADDR(A,k))){ // A[k] > p
            swap(ADDR(A, k), ADDR(A, j), elem_size);
            j--;
        }
        else{
         	k++;
        }
    }
    swap(ADDR(A, l), ADDR(A, (i-1)), elem_size);
    unsigned int *piv = malloc(2*sizeof(unsigned int));
    piv[0] = i-1;
    piv[1]= j;
    return (piv);
}


unsigned int select_index_aux(void *A,
                          const size_t elem_size, 
                          total_order leq,
                          const unsigned int l,
                          const unsigned int r,
                          const unsigned int i)
{
    if ((r-l) < 10){ // base case
        sorting(A, elem_size, leq, l, r);
        return i;
    }  

    const unsigned int j = select_pivot(A, elem_size, leq, l, r);
    unsigned int* k = threewaypartition(A, elem_size, leq, l, r, j);
    unsigned int k1 = k[0];
    unsigned int k2 = k[1];
    free(k);

    if (i > k2){
        return select_index_aux(A, elem_size, leq, k2+1, r, i); // search in G
    }
    if (i < k1){
        return select_index_aux(A, elem_size, leq, l, k1-1, i); // search in S
    }
    return i; // found
   

}

unsigned int select_index(void *A, const unsigned int n, 
                          const unsigned int i,
                          const size_t elem_size, 
                          total_order leq)
{  
    return 	select_index_aux(A, elem_size, leq, 0, n, i);
}

void quick_sort_select_aux(void *A, const unsigned int n, 
                           const size_t elem_size, 
                           total_order leq,
                           unsigned int l,
                           unsigned int r)
{
    if (l < r){
        if ((r-l) <= 10){ // base case
            sorting(A, elem_size, leq, l, r);
            return;
        }
        
        const unsigned int m = select_index_aux(A, elem_size, leq, l, r, (l+r)/2);
        unsigned int* p = threewaypartition(A, elem_size, leq, l, r, m);
        unsigned int p1 = p[0];
        unsigned int p2 = p[1];
        free(p);
        if(p1 > l){
        quick_sort_select_aux(A, n, elem_size, leq, l, p1-1); 
        }
        if(p2<r){
        quick_sort_select_aux(A, n, elem_size, leq, p2+1, r); 
        }
    }
}

void quick_sort_select(void *A, const unsigned int n, 
                       const size_t elem_size, 
                       total_order leq)
{
    quick_sort_select_aux(A, n, elem_size, leq, 0, n-1); // call recursive function

}   
