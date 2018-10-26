// Implementation of tests of TreeNode (and Pool).

#include "TreeNode-test.h"

#include "Pool.h"
#include "TreeNode.h"

#include <iostream>

namespace {
    using ek::Pool, ek::TreeNode;

    void test_int_treenode()
    {
        Pool<TreeNode<int>> p;

        auto root = p(10, p(20, p(40), p(50)),
                          p(30, p(60), p(70)));

        print_preorder_rec(root);
        print_inorder_rec(root);
        print_postorder_rec(root);
    }
}

void run_treenode_tests()
{
    test_int_treenode();
}
