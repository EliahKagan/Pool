#include "ListNode-test.hpp"
#include "TreeNode-test.hpp"
#include <iostream>

namespace {
    void hr()
    {
        std::cout << "\n\n";
        for (auto i = 100; i != 0; --i) std::cout << '=';
        std::cout << "\n\n\n";
    }
}

int main()
{
    std::cout << std::boolalpha;

    //run_c_listnode_tests()
    run_listnode_tests();
    hr();
    run_treenode_tests();

    std::cout << std::flush; // for convenience when debugging
}
