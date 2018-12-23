/* Test C functions for arrays and linked lists, from C - entry point. */

#include "test-cfuncs.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    test_array();
    putchar('\n');
    test_list();
    putchar('\n');
    test_list_equality();
    return EXIT_SUCCESS;
}
