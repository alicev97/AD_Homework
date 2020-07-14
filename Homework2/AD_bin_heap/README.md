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
0       0.000007        0.000002
1820    0.033414        0.516071
3640    0.070322        2.120490
5461    0.113505        4.820329
7281    0.152892        8.469055
9102    0.194851        13.336475
10922   0.249596        19.168667
12743   0.318915        27.254389
14563   0.383865        35.247459
16384   0.424199        45.010224
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
