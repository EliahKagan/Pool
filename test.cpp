#include <vector>
#include <iostream>
#include <memory>
#include "Pool.h"
#include "ListNode.h"

namespace {
    void test_int_pool()
    {
        Pool<int> pi;

        std::vector<int*> a;
        for (auto i = 5; i != 0; --i)
            a.push_back(pi(i));

        for (const auto x : a)
            std::cout << static_cast<const void*>(x) << ": " << *x << '\n';
    }

    void test_int_listnode_pool()
    {
        Pool<ListNode<int>> pl;

        auto i0 = 0, i2 = 2, i4 = 4, i6 = 6, i8 = 8, i10 = 10;
        const auto ineg1 = -1, i12 = 12;

        auto head0 = make_list(pl, ineg1, i0, 1, i2, 3, i4, 5, i6, 7, i8, 9,
                                   i10, 11, i12);

        auto head1 = make_list(pl, {10, 20, 30, 40, 50});
        auto head2 = make_list(pl, {});

        auto head3 = make_list(pl, 1, 2, 3, 4, 5);

        auto k = 76;
        auto head4 = make_list(pl, k);
        auto head5 = make_list(pl, 4444);
    }

    void test_int_uniqueptr_listnode_pool()
    {

    }
}

int main()
{
    test_int_pool();
    test_int_listnode_pool();
    test_int_uniqueptr_listnode_pool();
}
