#include "ListNode-test.h"
#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cout << std::boolalpha;

    run_listnode_tests();

    std::cout << std::flush; // for convenience when debugging
}
