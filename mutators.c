#include "mutators.h"

void increment(int *const elemp)
{
    ++*elemp;
}

void increase_by(int *const elemp, void *const deltap)
{
    *elemp += *(int *)deltap;
}
