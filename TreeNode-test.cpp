// Implementation of tests of TreeNode (and Pool).
//
// Copyright (c) 2018 Eliah Kagan
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
// SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
// OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
// CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#include "TreeNode-test.hpp"

#include "Pool.hpp"
#include "TreeNode.hpp"

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

        preorder_rec_iter(r, [](auto& x) { ++x; });
        inorder_rec_iter(r, [](auto& x) { x += 2; });
        postorder_rec_iter(r, [](auto& x) { x += 4; });

        print_preorder_rec_iter(r);
        print_inorder_rec_iter(r);
        print_postorder_rec_iter(r);

        std::cout << '\n';

        auto r2 = p(1, nullptr,
                       p(2, nullptr,
                            p(3, nullptr,
                                 p(4, nullptr,
                                      p(5)))));

        preorder_rec(r2, [](auto& x) { x *= 2; });
        inorder_rec(r2, [](auto& x) { x *= 2; });
        postorder_rec(r2, [](auto& x) { x *= 2; });

        print_preorder_rec(r2);
        print_inorder_rec(r2);
        print_postorder_rec(r2);

        std::cout << '\n';

        preorder_iter(r2, [](auto& x) { x /= 2; });
        inorder_iter(r2, [](auto& x) { x /= 2; });
        postorder_iter(r2, [](auto& x) { x /= 2; });

        print_preorder_iter(r2);
        print_inorder_iter(r2);
        print_postorder_iter(r2);

        std::cout << '\n';

        preorder_rec_iter(r2, [](auto& x) { x *= 2; });
        inorder_rec_iter(r2, [](auto& x) { x *= 2; });
        postorder_rec_iter(r2, [](auto& x) { x *= 2; });

        print_preorder_rec_iter(r2);
        print_inorder_rec_iter(r2);
        print_postorder_rec_iter(r2);

        std::cout << '\n';

        auto r3 = p(1, p(2, p(3, p(4, p(5),
                                      nullptr),
                              nullptr),
                         nullptr),
                    nullptr);

        preorder_rec(r3, [](auto& x) { x *= 2; });
        inorder_rec(r3, [](auto& x) { x *= 2; });
        postorder_rec(r3, [](auto& x) { x *= 2; });

        print_preorder_rec(r3);
        print_inorder_rec(r3);
        print_postorder_rec(r3);

        std::cout << '\n';

        preorder_iter(r3, [](auto& x) { x /= 2; });
        inorder_iter(r3, [](auto& x) { x /= 2; });
        postorder_iter(r3, [](auto& x) { x /= 2; });

        print_preorder_iter(r3);
        print_inorder_iter(r3);
        print_postorder_iter(r3);

        std::cout << '\n';

        preorder_rec_iter(r3, [](auto& x) { x *= 2; });
        inorder_rec_iter(r3, [](auto& x) { x *= 2; });
        postorder_rec_iter(r3, [](auto& x) { x *= 2; });

        print_preorder_rec_iter(r3);
        print_inorder_rec_iter(r3);
        print_postorder_rec_iter(r3);

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

        preorder_rec_iter(s, [](auto& x) { x -= 24; });
        inorder_rec_iter(s, [](auto& x) { x -= 6; });
        postorder_rec_iter(s, [](auto& x) { x -= 2; });

        print_preorder_rec_iter(s);
        print_inorder_rec_iter(s);
        print_postorder_rec_iter(s);

        std::cout << '\n';

        constexpr const TreeNode<char>* s0 {};

        print_preorder_rec(s0);
        print_inorder_rec(s0);
        print_postorder_rec(s0);

        print_preorder_iter(s0);
        print_inorder_iter(s0);
        print_postorder_iter(s0);

        print_preorder_rec_iter(s0);
        print_inorder_rec_iter(s0);
        print_postorder_rec_iter(s0);
    }
}

void run_treenode_tests()
{
    test_dfs_traversals();
}
