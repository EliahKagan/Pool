#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "check.h"

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

static void test_array_foreach(int *const a, const int n)
{
    enum { acc_start = 100 };
    int acc = acc_start, delta = 2;
    s_acc = 0;

    array_foreach(a, n, increase_s_acc);
    array_print(a, n);
    array_print_alt(a, n);
    array_foreach_mut(a, n, increment);
    array_print(a, n);
    array_print_alt(a, n);
    array_foreach(a, n, decrease_s_acc);
    printf("%d\n", s_acc);
    if (s_acc != -n) exit(EXIT_FAILURE);
    putchar('\n');

    array_foreach_r(a, n, increase_acc, &acc);
    array_print(a, n);
    array_print_alt(a, n);
    array_foreach_mut_r(a, n, increase_by, &delta);
    array_print(a, n);
    array_print_alt(a, n);
    array_foreach_r(a, n, decrease_acc, &acc);
    printf("%d\n", acc);
    if (acc != acc_start - n * delta) exit(EXIT_FAILURE);
    putchar('\n');
}

static void test_array(void)
{
    struct fold_results r1 = {-9, 44, 66, -164229120};
    int a1[] = {4, 3, -2, 8, -9, 15, 44, -6, 12, -1, -2};
    enum { n1 = LENGTH_OF(a1) };

    check_folds(&r1, array_min(a1, n1), array_max(a1, n1),
                     array_sum(a1, n1), array_product(a1, n1));

    check_folds(&r1, array_min_byfold(a1, n1), array_max_byfold(a1, n1),
                     array_sum_byfold(a1, n1), array_product_byfold(a1, n1));

    check_folds(&r1,
                array_min_byreduce(a1, n1), array_max_byreduce(a1, n1),
                array_sum_byreduce(a1, n1), array_product_byreduce(a1, n1));

    check(3, "counts", array_count(a1, n1, 10), array_count(a1, n1, 3),
                       array_count(a1, n1, -2),
            0, 1, 2);

    check(6, "indices", array_find(a1, n1, -2), array_rfind(a1, n1, -2),
                        array_find(a1, n1, 12), array_rfind(a1, n1, 12),
                        array_find(a1, n1, 7), array_rfind(a1, n1, 7),
            2, 10, 8, 8, 0, 0);

    putchar('\n');

    test_array_foreach(a1, n1);
}

static void test_list(void)
{

}

int main(void)
{
    test_array();
    test_list();
    return EXIT_SUCCESS;
}
