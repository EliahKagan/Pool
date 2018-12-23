/* Small general utilities - implementation file. */

#include "util.h"

#include <stdlib.h>

void xatexit(void (*handler)(void))
{
    if (atexit(handler) != 0) abort();
}

void *xcalloc(const size_t count, const size_t size)
{
    void *const p = calloc(count, size);
    if (!p) abort();
    return p;
}
