#include<stdio.h>
#include "graph.h"


int main(int argc, char *argv[])
{   

    Graph *g;
    Graph *h;

    printf("Dim.\tArray-Based\tHeap-Based\n");

    for (size_t i=2; (1<<i)<=(1<<12); i++){
        const unsigned int num = 1<<i;
        g = allocate_graph(num);
        h = allocate_graph(num);
        random_graph(g, 0.4);
        random_graph(h, 0.4);
        printf("2^%ld\t", i);
        fflush(stdout);
        printf("%f\t", test(dijkstra, g, 0));
        fflush(stdout);
        printf("%f\n", test(dijkstra_heap, h, 0));
        fflush(stdout);
        deallocate_graph(g);
        deallocate_graph(h);
    }
}