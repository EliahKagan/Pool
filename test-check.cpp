#include "check.h"

int main()
{
    check(3, "test 1", 11, 22, 33, 11, 22, 33); // should match
    check(3, "test 1", 11, 22, 33, 11, 22, 34); // should not match
}
