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

        preorder_rec(root, [](auto& x) { ++x; });
        inorder_rec(root, [](auto& x) { x += 2; });
        postorder_rec(root, [](auto& x) { x += 4; });

        print_preorder_rec(root);
        print_inorder_rec(root);
        print_postorder_rec(root);
        std::cout << '\n';
        print_preorder_iter(root);
        print_inorder_iter(root);
        print_postorder_iter(root);
    }
}

void run_treenode_tests()
{
    test_int_treenode();
}
