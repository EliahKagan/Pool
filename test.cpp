#include <vector>
#include <iostream>
#include "Pool.h"

int main()
{
    Pool<int> pool;

    std::vector<int*> a;
    for (auto i = 5; i != 0; --i)
        a.push_back(pool());
}
