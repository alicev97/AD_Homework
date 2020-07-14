 #include "graph.h"

Graph* allocate_graph(int n){
    
    Graph *g = (Graph*) malloc(sizeof(Graph));
    g->num_nodes = n;
    Node* V = allocate_nodes(n);
    g->adj = allocate_list(V, n, 0);
    return g;
    
}

void deallocate_graph(Graph* g){
    deallocate_list(g->adj);
    free(g);
}

void add_edge(Graph* g, int key, int key_neighbours, float weights){

    ListofWeightedNodes* t = &(g->adj[key]);
    Node* neighbours = g->adj[key_neighbours].node;
    while(t->next != NULL){
        t = t->next;
    }
    t->next = allocate_list(neighbours, 1, weights);

}

void random_graph(Graph* g, float p){
    
    srand(7); // fix random seed

    for(size_t i = 0; i < g->num_nodes; i++){
        for(size_t j = 0; j < g->num_nodes; ++j){

            float e = rand() % MAX_W; // random weight
            if(e > p*MAX_W){
                add_edge(g, i, j, e);
            }
        }
    }
}

void init_SSSP (Graph* g){

    for(size_t v = 0; v < g->num_nodes; v++ ){
        g->adj[v].node->d = g->num_nodes * MAX_W;
        g->adj[v].node->pred = NULL;
    }
}

void relax(Node* u, Node* v, float w){

    if (u->d + w < v->d){
        update_distance(v, u->d + w);
        v->pred = u;
    }
}


void dijkstra(Graph *g, int s){

    init_SSSP(g);

    g->adj[s].node->d = 0;
    Queue* q = build_queue(g->adj, g->num_nodes);

    while (!is_empty(q)){
        ListofWeightedNodes* u = extract_min_queue(q); 
        ListofWeightedNodes* current = u;

        while(current->next != NULL){
            current = current->next;
            relax(u->node, current->node, current->weight);
        }
    }
    deallocate_queue(q);
}

void int_printer(const void *value)
{
  printf("%f", (*((const ListofWeightedNodes *)value)).node->d);
}

void dijkstra_heap(Graph *g, int s){

    init_SSSP(g);
    g->adj[s].node->d = 0;

    binheap_type *h = build_heap((void *) g->adj, g->num_nodes, g->num_nodes, sizeof(ListofWeightedNodes), leq_list);

    while(!is_heap_empty(h)){

        ListofWeightedNodes *u = (ListofWeightedNodes *) extract_min(h);
        ListofWeightedNodes *t = u;
        
        while (t->next != NULL)
        {
            t = t->next;
            relax(u->node, t->node, t->weight);
        }
        
    }

}
void print_graph(Graph* g){

    ListofWeightedNodes* t;
    
    for(size_t i = 0; i< g->num_nodes; i++){
        t = &(g->adj[i]);
        printf("%d: \t", t->node->key);

        while(t->next != NULL){
            printf("%d; %f \n \t", t->node->key, t->weight);
            t = t->next;
        }
        printf("%d; %f \n", t->node->key, t->weight);

        printf("\n\n");
    }
}

void print_dist(Graph* g){

    for(size_t i = 0; i < g->num_nodes; i++){
        printf("%d: %f\n", g->adj[i].node->key, g->adj[i].node->d);
    }
}

double test(void (*dijk)(Graph *, int), Graph* g, int s){

  struct timespec start, end;

  clock_gettime(CLOCK_REALTIME, &start); // start the time
  for(size_t i = 0; i < REP; i++){
    dijk(g, s);
  }
  clock_gettime(CLOCK_REALTIME, &end); // stop the time

  return (((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1E9)/REP);
}