#include <vector>
#include <iostream>
#include <iterator>
#include <memory>
#include <utility>
#include "Pool.h"
#include "ListNode.h"

namespace {
    using std::begin, std::end;

    template<typename T>
    class NoDefault {
    public:
        explicit NoDefault(const T& item) : item_{item} { }
        explicit NoDefault(T&& item) noexcept : item_{std::move(item)} { }

        operator const T&() const & noexcept { return item_; }
        operator T&() & noexcept { return item_; }
        operator const T&&() const && noexcept { return std::move(item_); }
        operator T&&() && noexcept { return std::move(item_); }

    private:
        T item_;
    };

    void test_int()
    {
        Pool<int> pool;

        std::vector<int*> a;
        for (auto i = 5; i != 0; --i)
            a.push_back(pool(i));

        for (const auto x : a)
            std::cout << static_cast<const void*>(x) << ": " << *x << '\n';
    }

    void test_int_listnode()
    {
        Pool<ListNode<int>> pool;

        auto i0 = 0, i2 = 2, i4 = 4, i6 = 6, i8 = 8, i10 = 10;
        const auto ineg1 = -1, i12 = 12;

        auto head0 = make_list(pool, ineg1, i0, 1, i2, 3, i4, 5, i6, 7, i8, 9,
                                     i10, 11, i12);
        std::vector a (begin(*head0), end(*head0));

        auto head1 = make_list(pool, {10, 20, 30, 40, 50});
        auto head2 = make_list(pool, {});

        auto head3 = make_list(pool, 1, 2, 3, 4, 5);

        auto h = 11, k = 76;
        auto head4 = make_list(pool, k);
        auto head5 = make_list(pool, 4444);
        auto head6 = make_list(pool, h, k);
        auto head7 = make_list(pool, 3333, 4444);

        std::vector b {2, 3, 5, 7, 11, 13, 17, 19, 23};
        auto head8 = make_list(pool, a);
    }

    void test_int_uniqueptr_listnode()
    {
        Pool<ListNode<std::unique_ptr<int>>> pool;

        constexpr auto m = [](const int i) { return std::make_unique<int>(i); };

        auto head = make_list(pool, m(10), m(20), m(30), m(40), m(50));
    }

    void test_int_nodefault_listnode()
    {
        Pool<ListNode<NoDefault<int>>> pool;

        NoDefault h {3}, i {6}, j {9}, k {12};

        auto head1 = make_list(pool, h, i, j, k);

        std::vector a {h, i, j, k};
        auto head2 = make_list(pool, a);

        auto head3 = make_list(pool, {h, i, j, k});

        auto head4 = make_list(pool, std::vector{k, j, i, h});
    }
}

int main()
{
    test_int();
    test_int_listnode();
    test_int_uniqueptr_listnode();
    test_int_nodefault_listnode();
}
