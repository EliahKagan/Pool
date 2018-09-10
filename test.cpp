#include <vector>
#include <iostream>
#include "Pool.h"
#include "ListNode.h"

int main()
{
    Pool<int> pool;

    std::vector<int*> a;
    for (auto i = 5; i != 0; --i)
        a.push_back(pool(i));

    for (const auto x : a)
        std::cout << static_cast<const void*>(x) << ": " << *x << '\n';
}
