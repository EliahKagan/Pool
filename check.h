#ifndef HAVE_POOL_CHECK_H_
#define HAVE_POOL_CHECK_H_

#ifdef __cplusplus
extern "C" {
#endif

struct fold_results { int min, max, sum, product; };

void check_folds(const struct fold_results *resp,
                 int min, int max, int sum, int product);

void check(int count, const char *label, ...);

#ifdef __cplusplus
} /* ! extern "C" */
#endif

#endif /* ! HAVE_POOL_CHECK_H_ */
