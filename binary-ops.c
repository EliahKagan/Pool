#include "binary-ops.h"

int min(const int x, const int y)
{
    return y < x ? y : x;
}

int max(const int x, const int y)
{
    return y > x ? y : x;
}

int add(const int x, const int y)
{
    return x + y;
}

int mul(const int x, const int y)
{
    return x * y;
}
