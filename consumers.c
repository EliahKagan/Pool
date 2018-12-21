#include "consumers.h"

void increase_acc(const int x, void *const accp)
{
    *(int *)accp += x;
}

void decrease_acc(const int x, void *const accp)
{
    *(int *)accp -= x;
}

static int s_acc = 0;

void increase_s_acc(const int x)
{
    s_acc += x;
}

void decrease_s_acc(const int x)
{
    s_acc -= x;
}

void reset_s_acc(void)
{
    s_acc = 0;
}

int read_s_acc(void)
{
    return s_acc;
}
