#include "list_node.h"

#include <assert.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "actions.h"
#include "predicates.h"
#include "util.h"

struct list_node *list_create(int n, ...)
{
    struct list_node sentinel = {NULL, 0}, *cur = &sentinel;
    va_list ap;

    assert(n >= 0);
    va_start(ap, n);

    while (n-- > 0) {
        cur->next = xcalloc(1, sizeof *cur->next);
        cur = cur->next;
        cur->key = va_arg(ap, int);
    }

    va_end(ap);
    assert(cur->next == NULL);
    return sentinel.next;
}

void list_destroy(struct list_node *head)
{
    while (head) {
        struct list_node *const next = head->next;
        free(head);
        head = next;
    }
}

int list_length(const struct list_node *head)
{
    int acc = 0;
    for (; head; head = head->next) ++acc;
    return acc;
}

int list_min(const struct list_node *head)
{
    int acc = INT_MAX;

    for (; head; head = head->next)
        if (head->key < acc) acc = head->key;

    return acc;
}

int list_max(const struct list_node *head)
{
    int acc = INT_MIN;

    for (; head; head = head->next)
        if (head->key > acc) acc = head->key;

    return acc;
}

int list_sum(const struct list_node *head)
{
    int acc = 0;
    for (; head; head = head->next) acc += head->key;
    return acc;
}

int list_product(const struct list_node *head)
{
    int acc = 1;
    for (; head; head = head->next) acc *= head->key;
    return acc;
}

int list_fold(const struct list_node *head, const BinaryOp f, int acc)
{
    for (; head; head = head->next) acc = f(acc, head->key);
    return acc;
}

int list_reduce(const struct list_node *const head, const BinaryOp f)
{
    assert(head);
    return list_fold(head->next, f, head->key);
}

static int count_any(const int acc, const int elem)
{
    (void)elem;
    return acc + 1;
}

int list_length_byfold(const struct list_node *const head)
{
    return list_fold(head, count_any, 0);
}

int list_min_byfold(const struct list_node *const head)
{
    assert(head);
    return list_fold(head, min, INT_MAX);
}

int list_max_byfold(const struct list_node *const head)
{
    assert(head);
    return list_fold(head, max, INT_MIN);
}

int list_sum_byfold(const struct list_node *const head)
{
    return list_fold(head, add, 0);
}

int list_product_byfold(const struct list_node *const head)
{
    return list_fold(head, mul, 1);
}

int list_min_byreduce(const struct list_node *const head)
{
    return list_reduce(head, min);
}

int list_max_byreduce(const struct list_node *const head)
{
    return list_reduce(head, max);
}

int list_sum_byreduce(const struct list_node *const head)
{
    return list_reduce(head, add);
}

int list_product_byreduce(const struct list_node *const head)
{
    return list_reduce(head, mul);
}

int list_index(const struct list_node *head, const int x)
{
    int i = 0;
    for (; head && head->key != x; head = head->next) ++i;
    return head ? i : list_npos;
}

int list_count(const struct list_node *head, const int x)
{
    int acc = 0;
    for (; head; head = head->next) acc += head->key == x;
    return acc;
}

void list_foreach(const struct list_node *head, Consumer f)
{
    for (; head; head = head->next) f(head->key);
}

void list_foreach_r(const struct list_node *head, ConsumerEx f, void *aux)
{
    for (; head; head = head->next) f(head->key, aux);
}

void list_foreach_mut(struct list_node *head, Mutator f)
{
    for (; head; head = head->next) f(&head->key);
}

void list_foreach_mut_r(struct list_node *head, MutatorEx f, void *aux)
{
    for (; head; head = head->next) f(&head->key, aux);
}

void list_print(const struct list_node *head)
{
    const char *sep = "";

    putchar('[');
    list_foreach_r(head, print_element, &sep);
    puts("]");
}

static void print_alt_all_elements(const struct list_node *const head)
{
    printf("%d", head->key);
    list_foreach(head->next, print_alt_nonfirst_element);
}

void list_print_alt(const struct list_node *head)
{
    putchar('[');
    if (head) print_alt_all_elements(head);
    puts("]");
}
