/*
  Small general utilities.

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

#ifndef HAVE_POOL_UTIL_H_
#define HAVE_POOL_UTIL_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Use this to mark places a compiler might wrongly think could be reached. */
#if defined(_MSC_VER)
#define NOT_REACHED() __assume(false)
#elif defined(__GNUC__)
#define NOT_REACHED() __builtin_unreachable()
#else
#include <cassert>
#define NOT_REACHED() assert(false)
#endif

void xatexit(void (*handler)(void));
void *xcalloc(size_t count, size_t size);

#ifdef __cplusplus
} /* ! extern "C" */
#endif

#endif /* ! HAVE_POOL_UTIL_H_ */
