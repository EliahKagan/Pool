#include "list_node.h"

#include <assert.h>
#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>

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

}

int list_fold(const struct list_node *head, BinaryOp f, int acc)
{

}

int list_reduce(const struct list_node *head, BinaryOp f)
{

}

int list_length_byfold(const struct list_node *head)
{

}


int list_min_byfold(const struct list_node *head)
{

}

int list_max_byfold(const struct list_node *head)
{

}

int list_sum_byfold(const struct list_node *head)
{

}

int list_product_byfold(const struct list_node *head)
{

}

int list_min_byreduce(const struct list_node *head)
{

}

int list_max_byreduce(const struct list_node *head)
{

}

int list_sum_byreduce(const struct list_node *head)
{

}

int list_product_byreduce(const struct list_node *head)
{

}

int list_find(const struct list_node *head, int x)
{

}

int list_count(const struct list_node *head, int x)
{

}

void list_foreach(const struct list_node *head, Consumer f)
{

}

void list_foreach_r(const struct list_node *head, ConsumerEx f, void *aux)
{

}

void list_foreach_mut(struct list_node *head, Mutator f)
{

}

void list_foreach_mut_r(struct list_node *head, MutatorEx f, void *aux)
{

}

void list_print(const struct list_node *head)
{

}

void list_print_alt(const struct list_node *head)
{

}
