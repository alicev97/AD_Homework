EXE = main.x
CFLAGS = -I include 
DIR=../../Homework2/AD_bin_heaps/
BINHEAP=-l binheap -l common -L $(DIR)

all: $(EXE)

%.o: %.c
	gcc -c $< -o $@ $(CFLAGS) $(BINHEAP)

src/node.o: include/node.h
src/graph.o: include/graph.h
src/queue.o: include/queue.h
src/total_orders.o: include/total_orders.h

main.o: src/graph.o src/node.o src/queue.o src/total_orders.o

main.x: main.o src/graph.o src/node.o src/queue.o src/total_orders.o
	gcc $^ -o $@ $(BINHEAP)

clean:
	rm -rf *.o src/*.o *.x

.PHONY: clean all 