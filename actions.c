/* Actions useful with both array_foreach* and list_foreach* functions -
     implementation file. */

#include "actions.h"

#include <stdio.h>

void print_element(const int x, void *const sepp)
{
    const char **const my_sepp = (const char **)sepp;
    printf("%s%d", *my_sepp, x);
    *my_sepp = ", ";
}

void print_alt_nonfirst_element(const int x)
{
    printf(", %d", x);
}
