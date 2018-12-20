#ifndef HAVE_POOL_CHECK_H_
#define HAVE_POOL_CHECK_H_

struct fold_results { int min, max, sum, product; };

void check_folds(const struct fold_results *resp,
                 int min, int max, int sum, int product);

void check(int count, const char *label, ...);

#endif /* ! HAVE_POOL_CHECK_H_ */
