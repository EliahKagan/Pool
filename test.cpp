#include <vector>
#include <iostream>
#include "Pool.h"
#include "ListNode.h"

int main()
{
    Pool<int> pi;

    std::vector<int*> a;
    for (auto i = 5; i != 0; --i)
        a.push_back(pi(i));

    for (const auto x : a)
        std::cout << static_cast<const void*>(x) << ": " << *x << '\n';

    Pool<ListNode<int>> pl;

    auto head = make_list(pl, {10, 20, 30, 40, 50});
}
