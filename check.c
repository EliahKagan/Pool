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

static void fill_buffer(int *buffer, int count, va_list *const argsp)
{
    for (assert(count > 0); count > 0; --count)
        *buffer++ = va_arg(*argsp, int);
}

static int find_mismatch(const int *const buffer, const int count,
                         va_list *const argsp)
{
    int mismatch = 0;

    assert(count > 0);
    while (mismatch < count && va_arg(*argsp, int) == buffer[mismatch])
        ++mismatch;

    return mismatch;
}

static void print_label(const char *const label)
{
    assert(label);
    printf("%s:", label);
}

static void print_buffer(const int *buffer, int count)
{
    for (assert(count > 0); count > 0; --count) printf(" %d", *buffer++);
}

void check(const int count, const char *const label, ...)
{
    int *buffer = NULL;
    va_list args;
    int mismatch = 0;

    buffer = xcalloc((size_t)count, sizeof *buffer);

    va_start(args, label);
    fill_buffer(buffer, count, &args);
    mismatch = find_mismatch(buffer, count, &args);
    va_end(args);

    print_label(label);
    print_buffer(buffer, count);
    printf(" (%s)\n", (mismatch == count ? "match" : "mismatch"));

    free(buffer);
    buffer = NULL;

    if (mismatch != count) exit(EXIT_FAILURE);
}
