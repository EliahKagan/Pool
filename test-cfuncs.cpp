/* Test C functions for arrays and linked lists from C++ - implementation. */

#include "test-cfuncs.hpp"
#include "test-cfuncs.h"
#include <iostream>

void run_cfuncs_tests() noexcept
{
    test_list();
    std::cout << '\n';
    test_array();
}
