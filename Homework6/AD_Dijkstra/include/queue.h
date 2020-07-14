#ifndef __QUEUE_H_
#define __QUEUE_H_

#include "node.h"

typedef struct Queue{

    ListofWeightedNodes *v; // list of nodes
    int num_nodes; // size

} Queue;

Queue * build_queue(ListofWeightedNodes *l, int n);
void deallocate_queue(Queue *q);

ListofWeightedNodes * extract_min_queue(Queue *q);
int is_empty(Queue *q);


#endif