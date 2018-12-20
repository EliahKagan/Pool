#include "check.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

void check_folds(const struct fold_results *const resp,
                 const int min, const int max,
                 const int sum, const int product)
{
    printf("min=%d max=%d sum=%d product=%d\n", min, max, sum, product);

    if (min != resp->min || max != resp->max) exit(EXIT_FAILURE);
    if (sum != resp->sum || product != resp->product) exit(EXIT_FAILURE);
}

void check(const int count, const char *const label, ...)
{
    int *values = NULL;
    va_list ap;
    int i = 0;

    assert(count > 0);
    assert(label);

    values = xcalloc((size_t)count, sizeof *values);
    printf("%s:", label);
    va_start(ap, label);

    for (i = 0; i < count; ++i) {
        const int x = va_arg(ap, int);
        printf(" %d", x);
        values[i] = x;
    }

    putchar('\n');

    i = 0;
    while (i < count && va_arg(ap, int) == values[i]) ++i;
    printf(" - %s\n", (i == count ? "match" : "mismatch"));

    va_end(ap);
    free(values);
    values = NULL;

    if (i != count) exit(EXIT_FAILURE);
}
