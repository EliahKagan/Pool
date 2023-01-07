/*
  Test C functions for arrays and linked lists, from C or C++.

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

#ifndef HAVE_POOL_TEST_CFUNCS_H_
#define HAVE_POOL_TEST_CFUNCS_H_

#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "check.h"
#include "consumers.h"
#include "list_node.h"
#include "mutators.h"

/* Note: Compiling as extern "C" in C++ is intentionally not done. */

static void test_array_foreach(int *const a, const int n)
{
    enum { acc_start = 100 };
    int acc = acc_start, delta = 2;
    reset_s_acc();

    array_foreach(a, n, increase_s_acc);
    array_print(a, n);
    array_print_alt(a, n);
    array_foreach_mut(a, n, increment);
    array_print(a, n);
    array_print_alt(a, n);
    array_foreach(a, n, decrease_s_acc);
    printf("%d\n", read_s_acc());
    if (read_s_acc() != -n) exit(EXIT_FAILURE);
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

    check(6, "indices", array_index(a1, n1, -2), array_rindex(a1, n1, -2),
                        array_index(a1, n1, 12), array_rindex(a1, n1, 12),
                        array_index(a1, n1, 7), array_rindex(a1, n1, 7),
            2, 10, 8, 8, -1, -1);

    putchar('\n');

    test_array_foreach(a1, n1);
}

static void detail_test_list_foreach(struct list_node *const head)
{
    enum { acc_start = 100 };
    int acc = acc_start, delta = 2;
    const int n = list_length(head);
    if (n != list_length_byfold(head)) exit(EXIT_FAILURE);
    reset_s_acc();

    list_foreach(head, increase_s_acc);
    list_print(head);
    list_print_alt(head);
    list_foreach_mut(head, increment);
    list_print(head);
    list_print_alt(head);
    list_foreach(head, decrease_s_acc);
    printf("%d\n", read_s_acc());
    if (read_s_acc() != -n) exit(EXIT_FAILURE);
    putchar('\n');

    list_foreach_r(head, increase_acc, &acc);
    list_print(head);
    list_print_alt(head);
    list_foreach_mut_r(head, increase_by, &delta);
    list_print(head);
    list_print_alt(head);
    list_foreach_r(head, decrease_acc, &acc);
    printf("%d\n", acc);
    if (acc != acc_start - n * delta) exit(EXIT_FAILURE);
    putchar('\n');
}

static void test_list(void)
{
    struct fold_results r1 = {-9, 44, 66, -164229120};

    struct list_node *h1 = list_create(11,
                            4, 3, -2, 8, -9, 15, 44, -6, 12, -1, -2);

    check_folds(&r1, list_min(h1), list_max(h1),
                     list_sum(h1), list_product(h1));

    check_folds(&r1, list_min_byfold(h1), list_max_byfold(h1),
                     list_sum_byfold(h1), list_product_byfold(h1));

    check_folds(&r1, list_min_byreduce(h1), list_max_byreduce(h1),
                     list_sum_byreduce(h1), list_product_byreduce(h1));

    check(3, "counts", list_count(h1, 10), list_count(h1, 3),
                       list_count(h1, -2),
            0, 1, 2);

    check(6, "indices", list_index(h1, -2), list_rindex(h1, -2),
                        list_index(h1, 12), list_rindex(h1, 12),
                        list_index(h1, 7), list_rindex(h1, 7),
            2, 10, 8, 8, -1, -1);

    putchar('\n');

    detail_test_list_foreach(h1);
}

static void test_list_equality(void)
{
    struct list_node *h1 = list_create(5, 100, 200, 300, 400, 500);
    struct list_node *h2 = list_create(5, 100, 200, 300, 400, 500);

    check(1, "equal", list_equal(h1, h2), 1);
    h1 = list_prepend(h1, 3, 10, 20, 30);
    list_print(h1);
    check(1, "unequal", list_equal(h1, h2), 0);

    list_destroy(h2);
    list_destroy(h1);
}

/* Note: Compiling as extern "C" in C++ is intentionally not done. */

#endif /* ! HAVE_POOL_TEST_CFUNCS_H_ */
