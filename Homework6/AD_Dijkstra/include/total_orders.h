#ifndef __TOTAL_ORDERS__
#define __TOTAL_ORDERS__

#include <stdlib.h>
#include "node.h"

typedef int (*total_order_type)(const void *a, const void *b);

int leq_float(const void *a, const void *b);
int leq_int(const void *a, const void *b);
int geq_int(const void *a, const void *b);
int leq_list(const void *a, const void *b);

#endif