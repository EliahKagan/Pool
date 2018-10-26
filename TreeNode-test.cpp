// Implementation of tests of TreeNode (and Pool).

#include "TreeNode-test.h"

#include "Pool.h"
#include "TreeNode.h"

#include <iostream>

namespace {
    using ek::Pool, ek::TreeNode;

    void test_dfs_traversals()
    {
        Pool<TreeNode<int>> p;

        auto r = p(10, p(20, p(40), p(50)),
                       p(30, p(60), p(70)));

        preorder_rec(r, [](auto& x) { ++x; });
        inorder_rec(r, [](auto& x) { x += 2; });
        postorder_rec(r, [](auto& x) { x += 4; });

        print_preorder_rec(r);
        print_inorder_rec(r);
        print_postorder_rec(r);

        std::cout << '\n';

        preorder_iter(r, [](auto& x) { --x; });
        inorder_iter(r, [](auto& x) { x -= 2; });
        postorder_iter(r, [](auto& x) { x -= 4; });

        print_preorder_iter(r);
        print_inorder_iter(r);
        print_postorder_iter(r);

        std::cout << '\n';

        Pool<TreeNode<char>> q;

        auto s = q('a', q('b', q('d'), // first tree example from TAOCPv1 s2.3.1
                               nullptr),
                        q('c', q('e', nullptr,
                                      q('g')),
                               q('f', q('h'),
                                      q('j'))));

        preorder_rec(s, [](auto& x) { x -= 24; });
        inorder_rec(s, [](auto& x) { x -= 6; });
        postorder_rec(s, [](auto& x) { x -= 2; });

        print_preorder_rec(s);
        print_inorder_rec(s);
        print_postorder_rec(s);

        std::cout << '\n';

        preorder_iter(s, [](auto& x) { x += 24; });
        inorder_iter(s, [](auto& x) { x += 6; });
        postorder_iter(s, [](auto& x) { x += 2; });

        print_preorder_iter(s);
        print_inorder_iter(s);
        print_postorder_iter(s);

        std::cout << '\n';


    }
}

void run_treenode_tests()
{
    test_dfs_traversals();
}
