#ifndef HAVE_POOL_ARRAY_H_
#define HAVE_POOL_ARRAY_H_

#define LENGTH_OF(a) (sizeof (a) / sizeof ((a)[0]))

int array_min(const int *a, int n);
int array_max(const int *a, int n);
int array_sum(const int *a, int n);
int array_product(const int *a, int n);

typedef int (*BinaryOp)(int, int);

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

#endif /* ! HAVE_POOL_ARRAY_H_ */
