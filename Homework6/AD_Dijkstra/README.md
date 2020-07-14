# DSSC - Algorithmic Design - Dijkstra’s Algorithm

This repository contains an implementation of the Dijkstra’s algorithm.

The Dijkstra’s algorithm has been implemented in two different ways: an array-based version and a heap-based version.

In the [main.c](main.c) file both the version are tested on a set of instances of the problem and their execution times are compared.

You can compile the code by executing `make`. This produces an executable named `main.x` which can be executed in POSIX systems by using the command:

```bash
./main.x
Dim.    Array-Based     Heap-Based
2^2     0.000001        0.000002
2^3     0.000002        0.000002
2^4     0.000006        0.000006
2^5     0.000017        0.000019
2^6     0.000058        0.000047
2^7     0.000167        0.000133
2^8     0.000256        0.000192
2^9     0.000964        0.000722
2^10    0.003798        0.002693
2^11    0.014524        0.010239
2^12    0.061285        0.041449
```

The first column in the output report the number of nodes of the tested graph. The remaining columns in the output report the execution-time in seconds of the two implementations of Dijkstra’s algorithm.