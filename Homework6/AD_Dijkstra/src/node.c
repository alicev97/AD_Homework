#include "node.h"

Node* allocate_nodes(int n){
    
    Node* nodes = malloc(sizeof(Node)*n); // initilize the array
    for(size_t i = 0; i < n; i++){ // initialize the nodes
        nodes[i].key = i;
    }

    return nodes;
}

ListofWeightedNodes* allocate_list(Node *nodes, int n, float weight){

    ListofWeightedNodes* l = malloc(sizeof(ListofWeightedNodes)*n); // array of ListofWeightedNodes

    for(size_t i = 0; i < n; ++i){
        l[i].node = &(nodes[i]);
        l[i].weight = weight;
        l[i].next = NULL;
    }

    return l;
}

void deallocate_list(ListofWeightedNodes* l){
    free(l);
}

void update_distance(Node* n, float d_new){
    n->d = d_new;
}

void swap(ListofWeightedNodes* a, ListofWeightedNodes* b){

    ListofWeightedNodes* t = malloc(sizeof(ListofWeightedNodes));
    
    *t = *a;
    *a = *b;
    *b = *t;

    free(t);
}