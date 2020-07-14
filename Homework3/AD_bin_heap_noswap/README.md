# DSSC - Algorithmic Design - Binary Heap Library
This project is a simple array-implementation of binary heaps in the C-programming language.

It contains the type  `binheap_type` in the file [binheap.h](include/binheap.h) and all the functions dealing it in the file [binheap.c](src/binheap.c). The meaning of the 
function parameters and the semantics of the functions themselves are detailed in [binheap.h](include/binheap.h).

A set of tests can be produced as described below.

You can generate the Makefile by using [cmake](https://cmake.org/) as follows:
```bash
cmake -G "Unix Makefiles" CMakeLists.txt
```
Afterwards you can compile the code by executing `make`. This produces a set of programs, named `test_delete_min`, `test_insert`, etc., which can be 
executed in POSIX systems simply by writing `./` and the name of the program in the terminal. 

For instance, in order to execute `test_delete_min`, use the following command:

```bash
./test_delete_min
Setting up test sets...done

Build the data structure and keep removing the minimum
n       On Heaps        On Arrays
0       0.000039        0.000001
1820    0.021389        0.568486
3640    0.046344        2.286824
5461    0.074294        5.165859
7281    0.103055        9.175836
9102    0.128928        14.397502
10922   0.151187        21.054970
12743   0.196217        29.253425
14563   0.223901        39.000155
16384   0.257146        46.919083
```

## Installing the library

In order to install the library, you can set the install directory `<BINHEAP_INSTALL_DIR>` by executing:
```bash
cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=<BINHEAP_INSTALL_DIR> CMakeLists.txt
```
If you don't do it, the library and its headers will be installed in `/usr/local/`.

After that simply write:

```bash
make install
```
