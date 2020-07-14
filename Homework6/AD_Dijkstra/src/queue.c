#include "queue.h"

Queue * build_queue(ListofWeightedNodes *l,int n){
    Queue *q = malloc(sizeof(Queue));
    q->v = l;
    q->num_nodes = n; 
    
    return q;
}

void deallocate_queue(Queue* q){

    free(q);

}

int is_empty(Queue* q){

    if(q->num_nodes == 0){
        return 1;
    }
    return 0;
}

ListofWeightedNodes* extract_min_queue(Queue *q){

    ListofWeightedNodes *min = &(q->v[0]);

    for(size_t i = 1; i < q->num_nodes; i++){
        if(q->v[i].node->d < min->node->d)
            min = &(q->v[i]);
    }

    swap(min, &(q->v[q->num_nodes-1]));
    q->num_nodes--;

    return &(q->v[q->num_nodes]);

}
  