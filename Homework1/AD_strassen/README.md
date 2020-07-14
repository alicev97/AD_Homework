# DSSC - Algorithmic Design - Strassen's Algorithm
This repository contains some code to simplify the implementation and the testing of the Strassen's algorithm for matrix multiplication.

In order to test the differences in term of execution-time between the naive algorithm and the Strassen's algorithm, both the algorithms have been implemented in order to be able to deal with non-square matrices. The former is implemented by the function `naive_matrix_multiplication` in the file [matrix.c](matrix.c) and the latter by the function `strassen_matrix_multiplication` in the file [strassen.c](strassen.c). Furthermore there is a `strassen_matrix_multiplication_optim` which reduce the memory allocation.

A Makefile can be produced by using [cmake](https://cmake.org/) as follows:
```bash
cmake -G "Unix Makefiles" CMakeLists.txt
```
Afterwards you can compile the code by executing `make`. This produces an executable named `strassen_test` which can be executed in POSIX systems by using the command:
```bash
./strassen_test 
 Squared matrices:
n       Strassen's Alg. Optimized ver.  Naive Alg.      Same result
1       0.000001        0.000001        0.000000        1       1
2       0.000000        0.000000        0.000000        1       1
4       0.000000        0.000000        0.000000        1       1
8       0.000001        0.000000        0.000000        1       1
16      0.000004        0.000002        0.000003        1       1
32      0.000022        0.000019        0.000130        1       1
64      0.000240        0.000207        0.000207        1       1
128     0.001803        0.001942        0.002312        1       1
256     0.014165        0.013915        0.017561        1       1
512     0.093949        0.090110        0.135632        1       1
1024    0.640418        0.636878        1.142476        1       1
2048    4.531091        4.789046        11.931851       1       1


 Rectangular matrices:
        Strassen's Alg. Optimized ver.  Naive Alg.      Same result
        5.395239        5.348399        11.601279       1       1
```

The first block test the performances of the three functions on square matrices.

The first column in the output report the number of the rows and columns in the tested matrices. 

The second, the third and the fourth columns in the output reports the execution-time in seconds of the implementations of the Strassen's algorithm,  of the optimised version and of the naive algorithm respectively. 

Finally, the last column, which is excursively meant to validate the implementations, contains the value 1	1 if and only if the result of the naive algorithm, of the Strassen's algorithm and of the optimised version are the same.

The second block test the performances of the three functions on non-square matrices.