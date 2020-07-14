# DSSC - Algorithmic Design - Sorting Algorithms
This repository contains some code to simplify the implementation and testing of sorting algorithms.

The following algorithms have been implemented: Insertion Sort, Quick Sort, Bubble Sort,  Heap Sort, and two versions of the Selection Sort, with and without the select algorithm to identify the pivot. 

In the file [main.c](src/main.c) the differences in term of execution-time between the sorting algorithms are tested.

The insertion sort algorithm is implemented in the file [insertion_sort.c](src/insertion_sort.c) according to the API defined in [insertion_sort.h](src/insertion_sort.h); the quick sort algorithm in the file [quick_sort.c](src/quick_sort.c) and, so forward, for all the algorithms.


A Makefile can be produced by using [cmake](https://cmake.org/) as follows:
```bash
cmake -G "Unix Makefiles" CMakeLists.txt
```
If you have implemented the [`binheap` library](https://github.com/albertocasagrande/AD_bin_heaps), you can use it to code heap sort by using the command:
```bash
cmake -G "Unix Makefiles" -DBINHEAP_PATH=<BINHEAP_INSTALL_DIR> CMakeLists.txt
```
See [here](https://github.com/albertocasagrande/AD_bin_heaps) to have more details about `<BINHEAP_INSTALL_DIR>`.

Afterwards you can compile the code by executing `make`. This produces an executable named `test_sorting` which can be executed in POSIX systems by using the command:
```bash
./test_sorting
Size    Insertion Sort                          
        (Random Case)   (Best Case)     (Worst Case)
2^2     0.000001        0.000000        0.000000
2^3     0.000000        0.000000        0.000001
2^4     0.000001        0.000000        0.000002
2^5     0.000004        0.000000        0.000008
2^6     0.000016        0.000000        0.000030
2^7     0.000099        0.000001        0.000147
2^8     0.000485        0.000001        0.000601
2^9     0.001105        0.000002        0.002029
2^10    0.004751        0.000005        0.009874
2^11    0.017265        0.000007        0.033373
2^12    0.068158        0.000019        0.132500
2^13    0.263445        0.000041        0.532543


Size    Quick Sort                      Quick Sort + Select
        (Random Case)   (Worst Case)    (Random Case)   (Worst Case)
2^2     0.000001        0.000001        0.000001        0.000000
2^3     0.000001        0.000001        0.000001        0.000001
2^4     0.000002        0.000003        0.000004        0.000003
2^5     0.000004        0.000005        0.000011        0.000009
2^6     0.000008        0.000011        0.000027        0.000025
2^7     0.000016        0.000028        0.000069        0.000064
2^8     0.000036        0.000074        0.000164        0.000154
2^9     0.000085        0.000202        0.000382        0.000416
2^10    0.000182        0.000565        0.000836        0.000965
2^11    0.000465        0.002061        0.002207        0.002311
2^12    0.000832        0.004359        0.003973        0.005150
2^13    0.002036        0.012406        0.009191        0.012071


Size    Insertion Sort  Quick Sort      Bubble Sort     Selection Sort  Heap Sort
        (Random Case)   (Random Case)
2^2     0.000000        0.000001        0.000001        0.000000        0.000002
2^3     0.000001        0.000001        0.000001        0.000001        0.000002
2^4     0.000001        0.000002        0.000002        0.000001        0.000003
2^5     0.000005        0.000004        0.000009        0.000003        0.000006
2^6     0.000025        0.000011        0.000034        0.000012        0.000015
2^7     0.000096        0.000022        0.000131        0.000033        0.000034
2^8     0.000389        0.000041        0.000409        0.000120        0.000068
2^9     0.001062        0.000089        0.001426        0.000372        0.000134
2^10    0.004078        0.000183        0.005653        0.001421        0.000321
2^11    0.017377        0.000408        0.024712        0.005568        0.000680
2^12    0.070417        0.000871        0.102375        0.022235        0.001476
2^13    0.273496        0.001834        0.420235        0.086244        0.003159


Size    Quick Sort      Quick Sort +    Heap Sort
                          Select
        (Random Case)   (Random Case)
2^14    0.003938        0.016112        0.006808
2^15    0.009535        0.030652        0.014771
2^16    0.024786        0.060925        0.030988
2^17    0.070645        0.117893        0.064598
2^18    0.231815        0.236771        0.134741
2^19    0.807254        0.512524        0.282131
2^20    3.087047        0.942366        0.591548
```

The first column in the output report the size of the tested array. The remaining columns in the output report the execution-time in seconds of the implementations of sorting algorithms. Whenever the resulting arrays are not sorted (e.g., due to a bug) the word "KO" follows the execution-time.

In order to better compare quick sort and heap sort on the random cases, a futher set of tests on larger arrays are also performed.
