#include "array.h"

#include <assert.h>
#include <limits.h>

#include "predicates.h"

int array_min(const int *a, int n)
{
    int acc = INT_MAX;

    for (assert(n > 0); n-- > 0; ++a)
        if (*a < acc) acc = *a;

    return acc;
}

int array_max(const int *a, int n)
{
    int acc = INT_MIN;

    for (assert(n > 0); n-- > 0; ++a)
        if (*a > acc) acc = *a;

    return acc;
}

int array_sum(const int *a, int n)
{
    int acc = 0;
    for (assert(n >= 0); n-- > 0; ++a) acc += *a;
    return acc;
}

int array_product(const int *a, int n)
{
    int acc = 1;
    for (assert(n >= 0); n-- > 0; ++a) acc *= *a;
    return acc;
}

int array_fold(const int *a, int n, const BinaryOp f, int acc)
{
    for (assert(n >= 0); n-- > 0; ++a) acc = f(acc, *a);
    return acc;
}

int array_reduce(const int *const a, const int n, const BinaryOp f)
{
    assert(n > 0);
    return array_fold(a + 1, n - 1, f, *a);
}

int array_min_byfold(const int *const a, const int n)
{
    return array_fold(a, n, min, INT_MAX);
}

int array_max_byfold(const int *const a, const int n)
{
    return array_fold(a, n, max, INT_MIN);
}

int array_sum_byfold(const int *const a, const int n)
{
    return array_fold(a, n, add, 0);
}

int array_product_byfold(const int *const a, const int n)
{
    return array_fold(a, n, mul, 1);
}

int array_min_byreduce(const int *const a, const int n)
{
    return array_reduce(a, n, min);
}

int array_max_byreduce(const int *const a, const int n)
{
    return array_reduce(a, n, max);
}

int array_sum_byreduce(const int *const a, const int n)
{
    return array_reduce(a, n, add);
}

int array_product_byreduce(const int *const a, const int n)
{
    return array_reduce(a, n, mul);
}
