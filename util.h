/* Small general utilities. */

#ifndef HAVE_POOL_UTIL_H_
#define HAVE_POOL_UTIL_H_

#include <stddef.h>

/* Use this to mark places a compiler might wrongly think could be reached. */
#if defined(_MSC_VER)
#define NOT_REACHED() __assume(false)
#elif defined(__GNUC__)
#define NOT_REACHED() __builtin_unreachable()
#else
#include <cassert>
#define NOT_REACHED() assert(false)
#endif

#ifdef __cplusplus
extern "C" {
#endif

void *xcalloc(size_t count, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* ! HAVE_POOL_UTIL_H_ */
