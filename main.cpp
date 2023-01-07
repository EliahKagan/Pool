// Copyright (c) 2018 Eliah Kagan
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <iostream>

#include "ListNode-test.hpp"
#include "test-cfuncs.hpp"
#include "TreeNode-test.hpp"

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

    run_cfuncs_tests();
    hr();
    run_listnode_tests();
    hr();
    run_treenode_tests();

    std::cout << std::flush; // for convenience when debugging
}
