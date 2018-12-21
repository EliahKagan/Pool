#ifndef HAVE_POOL_LIST_NODE_H_
#define HAVE_POOL_LIST_NODE_H_

#include "function-types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct list_node {
    struct list_node *next;
    int key;
};

struct list_node *list_create(int n, ...);
void list_destroy(struct list_node *head);

int list_length(const struct list_node *head);

int list_min(const struct list_node *head);
int list_max(const struct list_node *head);
int list_sum(const struct list_node *head);
int list_product(const struct list_node *head);

int list_fold(const struct list_node *head, BinaryOp f, int acc);
int list_reduce(const struct list_node *head, BinaryOp f);

int list_length_byfold(const struct list_node *head);

int list_min_byfold(const struct list_node *head);
int list_max_byfold(const struct list_node *head);
int list_sum_byfold(const struct list_node *head);
int list_product_byfold(const struct list_node *head);

int list_min_byreduce(const struct list_node *head);
int list_max_byreduce(const struct list_node *head);
int list_sum_byreduce(const struct list_node *head);
int list_product_byreduce(const struct list_node *head);

enum { list_npos = -1 };

int list_index(const struct list_node *head, int x);
int list_rindex(const struct list_node *head, int x);
int list_count(const struct list_node *head, int x);

void list_foreach(const struct list_node *head, Consumer f);
void list_foreach_r(const struct list_node *head, ConsumerEx f, void *aux);
void list_foreach_mut(struct list_node *head, Mutator f);
void list_foreach_mut_r(struct list_node *head, MutatorEx f, void *aux);

void list_print(const struct list_node *head);
void list_print_alt(const struct list_node *head);

#ifdef __cplusplus
}
#endif

#endif /* ! HAVE_POOL_LIST_NODE_H_ */
