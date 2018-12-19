// Small general utilities.

#ifndef HAVE_POOL_UTIL_HPP_
#define HAVE_POOL_UTIL_HPP_

// Use this to mark places a compiler might wrongly think are possible to reach.
#if defined(_MSC_VER)
#define NOT_REACHED() __assume(false)
#elif defined(__GNUC__)
#define NOT_REACHED() __builtin_unreachable()
#else
#include <cassert>
#define NOT_REACHED() assert(false)
#endif

#endif // ! HAVE_POOL_UTIL_HPP_
