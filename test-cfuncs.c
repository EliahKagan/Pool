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

static void increment(int *const elemp)
{
    ++*elemp;
}

static void increase_by(int *const elemp, void *const deltap)
{
    *elemp += *(int *)deltap;
}

static void increase_acc(const int x, void *const accp)
{
    *(int *)accp += x;
}

static void decrease_acc(const int x, void *const accp)
{
    *(int *)accp -= x;
}

static int s_acc = 0;

static void increase_s_acc(const int x)
{
    s_acc += x;
}

static void decrease_s_acc(const int x)
{
    s_acc -= x;
}

static void test1(void)
{
    int a1[] = {4, 3, -2, 8, -9, 15, 44, -6, 12, -1, -2};
    enum { n1 = LENGTH_OF(a1) };

    /* TODO: Maybe give the foreach tests their own function. */
    enum { acc_start = 100 };
    int acc = acc_start;
    int delta = 2;

    a1check(array_min(a1, n1), array_max(a1, n1),
            array_sum(a1, n1), array_product(a1, n1));

    a1check(array_min_byfold(a1, n1), array_max_byfold(a1, n1),
            array_sum_byfold(a1, n1), array_product_byfold(a1, n1));

    a1check(array_min_byreduce(a1, n1), array_max_byreduce(a1, n1),
            array_sum_byreduce(a1, n1), array_product_byreduce(a1, n1));

    printf("%d %d %d\n", array_count(a1, n1, 10), array_count(a1, n1, 3),
                         array_count(a1, n1, -2));

    printf("%d %d %d %d %d %d\n",
            array_find(a1, n1, -2), array_rfind(a1, n1, -2),
            array_find(a1, n1, 12), array_rfind(a1, n1, 12),
            array_find(a1, n1, 7), array_rfind(a1, n1, 7));

    array_foreach(a1, n1, increase_s_acc);
    array_foreach_mut(a1, n1, increment);
    array_foreach(a1, n1, decrease_s_acc);
    printf("%d\n", s_acc);
    if (s_acc != -n1) exit(EXIT_FAILURE);

    array_foreach_r(a1, n1, increase_acc, &acc);
    array_foreach_mut_r(a1, n1, increase_by, &delta);
    array_foreach_r(a1, n1, decrease_acc, &acc);
    printf("%d\n", acc);
    if (acc != acc_start - n1 * delta) exit(EXIT_FAILURE);
}

int main(void)
{
    test1();
    return EXIT_SUCCESS;
}
