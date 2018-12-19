#include <stdio.h>
#include <stdlib.h>

#include "array.h"

static void a1check(const int a1min, const int a1max,
                    const int a1sum, const int a1product)
{
    printf("min=%d max=%d sum=%d product=%d\n",
           a1min, a1max, a1sum, a1product);

    if (a1min != -9 || a1max != 44 || a1sum != 66 || a1product != -164229120)
        exit(EXIT_FAILURE);
}

int main(void)
{
    int a1[] = {4, 3, -2, 8, -9, 15, 44, -6, 12, -1, -2};

    a1check(array_min(a1, LENGTH_OF(a1)),
            array_max(a1, LENGTH_OF(a1)),
            array_sum(a1, LENGTH_OF(a1)),
            array_product(a1, LENGTH_OF(a1)));

    a1check(array_min_byfold(a1, LENGTH_OF(a1)),
            array_max_byfold(a1, LENGTH_OF(a1)),
            array_sum_byfold(a1, LENGTH_OF(a1)),
            array_product_byfold(a1, LENGTH_OF(a1)));

    a1check(array_min_byreduce(a1, LENGTH_OF(a1)),
            array_max_byreduce(a1, LENGTH_OF(a1)),
            array_sum_byreduce(a1, LENGTH_OF(a1)),
            array_product_byreduce(a1, LENGTH_OF(a1)));

    return EXIT_SUCCESS;
}
