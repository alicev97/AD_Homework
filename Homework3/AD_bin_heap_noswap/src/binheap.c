#include "binheap2.h"
#include <string.h>
#include <stdio.h>

#define PARENT(node) ((node-1)/2)
#define LEFT_CHILD(node) (2*(node)+1)
#define RIGHT_CHILD(node) (2*(node+1))

#define VALID_NODE(H, node) ((H)->num_of_elem>(node))

#define ADDR(H, node) ((H)->A+(node)*(H)->key_size)
#define INDEX_OF(H, addr) (((addr)-((H)->A))/(H)->key_size) 

#define POS(H, node) ((H)->key_pos[node])
#define NODE(H, pos) ((H)->rev_pos[pos])

int is_heap_empty(const binheap_type *H)
{
    return H->num_of_elem==0;
}

const void *min_value(const binheap_type *H)
{
    if (is_heap_empty(H)){
        return NULL;
    }

    return ADDR(H, NODE(H,0)); // the min is stored in the root aka A[0]
}

void swap_pos(binheap_type *H, unsigned int n_a, unsigned int n_b)
{   
    // get the positions
    unsigned int p_a = POS(H, n_a);
    unsigned int p_b = POS(H, n_b);
    unsigned int t = POS(H, n_a);

    // swap the positions
    POS(H, n_a) =  POS(H, n_b);
    POS(H, n_b) = t;

    // swap the nodes
    NODE(H, p_a) = n_b;
    NODE(H, p_b) = n_a;
}

void heapify(binheap_type *H, unsigned int node)
{
    unsigned int dst_node = node, p_node, child, p_child;

    do{
        dst_node = node;
        p_node = POS(H, node);

        // find the minimum among the node and its children
        p_child = RIGHT_CHILD(p_node);
        if(VALID_NODE(H, p_child)){
            child = NODE(H, p_child);
            if (H->leq(ADDR(H, child), ADDR(H, dst_node))){
                dst_node = child;
            }
        }
        
        p_child = LEFT_CHILD(p_node);
        if(VALID_NODE(H, p_child)){
            child = NODE(H, p_child);
            if (H->leq(ADDR(H,child), ADDR(H, dst_node))){
                dst_node = child;
            }
        }

        // if the minimum is not in node swap the keys
        if(dst_node != node){
            swap_pos(H, dst_node, node);
        }
    } while (dst_node != node);
}

const void *extract_min(binheap_type *H)
{
    if (is_heap_empty(H)){
        return NULL;
    }

    swap_pos(H, NODE(H,0), NODE(H, H->num_of_elem-1)); // swapping the keys among the rood A[0] and the right-most leaf of the last level A[num_of_elem-1]
    H->num_of_elem--; // deleting the right-most leaf of the last level A[num_of_elem-1]
    heapify(H, NODE(H, 0)); // fix heap property

    return ADDR(H, NODE(H, H->num_of_elem)); // return a pointer to the deleated element
}

const void *find_the_max(void *A, 
                         const unsigned int num_of_elem, 
                         const size_t key_size, 
                         total_order_type leq)
{
    if (num_of_elem == 0){
        return NULL;
    }

    const void *max_value = A;

    // for all the values in A
    for(const void *addr=A+key_size; addr!=A +((num_of_elem-1)*key_size); addr+=key_size){
        // if addr > max_value
        if(!leq(addr, max_value)){
            max_value = addr;
        }
    }

    return max_value;
}

binheap_type *build_heap(void *A, 
                         const unsigned int num_of_elem,
                         const unsigned int max_size,  
                         const size_t key_size, 
                         total_order_type leq)
{
    binheap_type *H = (binheap_type *)malloc(sizeof(binheap_type));

    H->A = A;
    H->num_of_elem = num_of_elem;
    H->max_size = max_size;
    H->key_size = key_size;
    H->leq = leq;
    H->max_order_value = malloc(key_size);
    H->key_pos = (unsigned int*)malloc(max_size*sizeof(unsigned int));
    H->rev_pos = (unsigned int*)malloc(max_size*sizeof(unsigned int));

    // fill key_pos and rev_pos
    for(unsigned int i = 0; i < max_size; i++){
        H->key_pos[i] = i;
        H->rev_pos[i] = i;
    }

    if(num_of_elem==0){
        return H;
    }

    // get the maximum among A[:num_of_elem-1] and store it in max_order_value
    const void *value = find_the_max(A, num_of_elem, key_size, leq);
    memcpy(H->max_order_value, value, key_size);

    // fix the heap property form the second last level up to the root
    for(unsigned int i = num_of_elem/2; i>0; i--){
        heapify(H,NODE(H, i));
    }
    heapify(H,NODE(H,0));

    return H;
}

void delete_heap(binheap_type *H)
{
    free(H->max_order_value);
    free(H);
}

const void *decrease_key(binheap_type *H, void *node, const void *value)
{
    if(H->num_of_elem == 1)
        return NULL; //We are inserting the root

    unsigned int node_idx = INDEX_OF(H, node);
    unsigned int p_node = POS(H, node_idx);

    // if node does not belong to H or *value* >= node return NULL
    if (!VALID_NODE(H, node_idx) || !(H->leq(value, node))){
        return NULL;
    }

    memcpy(node, value, H->key_size);

    unsigned int parent_idx = NODE(H, PARENT(p_node));
    void *parent = ADDR(H, parent_idx);

    // while node != root and *parent > *node 
    while ((p_node != 0) && (!H->leq(parent, node)))
    {
        // swap parent and node keys
        swap_pos(H, parent_idx, node_idx);

        // focus on the node's parent
        p_node = POS(H, node_idx);

        if(!(VALID_NODE(H,PARENT(p_node)))){
            break;
        }
        parent_idx = NODE(H, PARENT(p_node));
        parent = ADDR(H, parent_idx);
        

    }
    
    return NULL;
}

const void *insert_value(binheap_type *H, const void *value)
{   
    // if the heap is already full
    if (H-> max_size == H->num_of_elem){
        return NULL;
    }
    
    // if the new value > *max_order_value
    if(H-> num_of_elem == 0 || !H->leq(value, H->max_order_value)){
        memcpy(H->max_order_value, value, H->key_size);
    }

    // get the position of the new node
    unsigned int new_node =NODE(H, H->num_of_elem);
    void *new_node_addr = ADDR(H, new_node);
    memcpy(new_node_addr, H->max_order_value, H->key_size);

    // increase the size of the heap
    H->num_of_elem++;

    // decrease the key of the new node
    return decrease_key(H, new_node_addr, value);
}

void print_heap(const binheap_type *H, 
                void (*key_printer)(const void *value))
{   
    unsigned int next_level_node = 1; // stores the index of the left-most node of the next level
    for (unsigned int node = 0; node < H->num_of_elem; node++){
        if (node==next_level_node){
            printf("\n");
            next_level_node=LEFT_CHILD(node);
        } else{
            printf("\t");
        }
        key_printer(ADDR(H, NODE(H,node)));
    }
    printf("\n");
}