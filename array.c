/*
  Functions that operate on all elements of an array - implementation.

  Copyright (c) 2018 Eliah Kagan

  Permission to use, copy, modify, and/or distribute this software for any
  purpose with or without fee is hereby granted.

  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
  REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
  AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
  INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
  LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
  OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
  PERFORMANCE OF THIS SOFTWARE.
*/

#include "array.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>

#include "actions.h"
#include "binary-ops.h"

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

int array_index(const int *const a, const int n, const int x)
{
    int i = 0;
    for (assert(n >= 0); i < n; ++i)
        if (a[i] == x) return i;

    return array_npos;
}

int array_rindex(const int *const a, int n, const int x)
{
    assert(n >= 0);
    assert(array_npos == -1); /* could be _Static_assert in C99 and later */

    while (--n != array_npos && a[n] != x) { }
    return n;
}

int array_count(const int *a, int n, const int x)
{
    int acc = 0;
    for (assert(n >= 0); n-- > 0; ++a) acc += *a == x;
    return acc;
}

void array_foreach(const int *a, int n, const Consumer f)
{
    for (assert(n >= 0); n-- > 0; ++a) f(*a);
}

void array_foreach_r(const int *a, int n, const ConsumerEx f, void *const aux)
{
    for (assert(n >= 0); n-- > 0; ++a) f(*a, aux);
}

void array_foreach_mut(int *a, int n, const Mutator f)
{
    for (assert(n >= 0); n-- > 0; ++a) f(a);
}

void array_foreach_mut_r(int *a, int n, const MutatorEx f, void *const aux)
{
    for (assert(n >= 0); n-- > 0; ++a) f(a, aux);
}

void array_print(const int *a, int n)
{
    const char *sep = "";
    assert(n >= 0);

    putchar('{');
    array_foreach_r(a, n, print_element, &sep);
    puts("}");
}

static void print_alt_all_elements(const int *const a, const int n)
{
    printf("%d", *a);
    array_foreach(a + 1, n - 1, print_alt_nonfirst_element);
}

void array_print_alt(const int *const a, const int n)
{
    assert(n >= 0);

    putchar('{');
    if (n > 0) print_alt_all_elements(a, n);
    puts("}");
}
