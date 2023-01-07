/*
  Functions that operate on all elements of an array.

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

#ifndef HAVE_POOL_ARRAY_H_
#define HAVE_POOL_ARRAY_H_

#include "function-types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LENGTH_OF(a) (sizeof (a) / sizeof ((a)[0]))

int array_min(const int *a, int n);
int array_max(const int *a, int n);
int array_sum(const int *a, int n);
int array_product(const int *a, int n);

int array_fold(const int *a, int n, BinaryOp f, int acc);
int array_reduce(const int *a, int n, BinaryOp f);

int array_min_byfold(const int *a, int n);
int array_max_byfold(const int *a, int n);
int array_sum_byfold(const int *a, int n);
int array_product_byfold(const int *a, int n);

int array_min_byreduce(const int *a, int n);
int array_max_byreduce(const int *a, int n);
int array_sum_byreduce(const int *a, int n);
int array_product_byreduce(const int *a, int n);

enum { array_npos = -1 };

int array_index(const int *a, int n, int x);
int array_rindex(const int *a, int n, int x);
int array_count(const int *a, int n, int x);

void array_foreach(const int *a, int n, Consumer f);
void array_foreach_r(const int *a, int n, ConsumerEx f, void *aux);
void array_foreach_mut(int *a, int n, Mutator f);
void array_foreach_mut_r(int *a, int n, MutatorEx f, void *aux);

void array_print(const int *a, int n);
void array_print_alt(const int *a, int n);

#ifdef __cplusplus
} /* ! extern "C" */
#endif

#endif /* ! HAVE_POOL_ARRAY_H_ */
