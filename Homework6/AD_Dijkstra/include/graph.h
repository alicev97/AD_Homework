#ifndef __GRAPH_H_
#define __GRAPH_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <binheap.h>

#include "node.h"
#include "queue.h"
#include "total_orders.h"

#define REP 10
#define MAX_W 100

typedef struct Graph{

    int num_nodes; // num of nodes
    ListofWeightedNodes* adj; // adjacency list

} Graph;

Graph* allocate_graph(int n);
void deallocate_graph(Graph* g);
void random_graph(Graph* g, float p);
void add_edge(Graph* g, int key, int neighbours, float weights);
void dijkstra(Graph *g, int s);
void dijkstra_heap(Graph *g, int s);
void print_graph(Graph* g);
void print_dist(Graph* g);
double test(void (*dijk)(Graph *, int), Graph* g, int s);
#endif