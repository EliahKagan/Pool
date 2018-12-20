#include "check.h"

#include <stdio.h>
#include <stdlib.h>

void check_folds(const struct fold_results *const resp,
                 const int min, const int max,
                 const int sum, const int product)
{
    printf("min=%d max=%d sum=%d product=%d\n", min, max, sum, product);

    if (min != resp->min || max != resp->max) exit(EXIT_FAILURE);
    if (sum != resp->sum || product != resp->product) exit(EXIT_FAILURE);
}
