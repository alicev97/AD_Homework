
#ifndef __NODE__H_
#define __NODE__H_

#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int key;
    float d; // distance from source
    struct Node* pred;

} Node;

typedef struct ListofWeightedNodes
{
    Node *node;
    float weight;
    struct ListofWeightedNodes *next;

} ListofWeightedNodes;

Node* allocate_nodes(int n);
ListofWeightedNodes* allocate_list(Node *nodes, int n, float weight);
void deallocate_list(ListofWeightedNodes* l);
void update_distance(Node* n, float d_new);
void swap(ListofWeightedNodes* a, ListofWeightedNodes* b);

#endif