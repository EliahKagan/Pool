#include <bitset>
#include <cassert>
#include <vector>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <string>
#include <string_view>
#include <utility>
#include "Pool.h"
#include "ListNode.h"

namespace {
    using ek::Pool, ek::ListNode;

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
        auto a = vec(head0);

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

    void test_bitset_listnode()
    {
        using Bits = std::bitset<10'000'000>;
        Pool<ListNode<Bits>> pool;

        ListNode<Bits>* head1 {};
        for (auto i = 10; i != 0; --i) {
            const auto pre = pool();
            pre->next = head1;
            head1 = pre;
        }

        for (auto p = begin(head1); p != end(head1); ++p) {
            p->flip();
            std::cout << p->count() << '\n';
        }
    }

    void test_string_pair_listnode()
    {
        using namespace std::string_literals;
        using std::pair;

        Pool<ListNode<pair<std::string, std::string>>> pool;

        auto head1 = make_list(pool, pair{"foo"s, "bar"s},
                                     pair{"baz"s, "quux"s},
                                     pair{"foobar"s, "ab"s});

        std::vector a (begin(head1), end(head1));

        for (auto p = begin(head1); p != end(head1); ++p)
            std::cout << p->first << ' ' << p->second << '\n';
    }

    void test_copy()
    {
        using namespace std::string_literals;

        Pool<ListNode<std::string>> pool;

        auto head1 = make_list(pool,
                               {"foo"s, "bar"s, "baz"s, "foobar"s, "quux"s});

        auto head2 = make_list(pool, head1);

        for (auto& s : head1) s.append("zor");

        const auto pp = cend(head1);
        for (auto p = cbegin(head1), q = cbegin(head2); p != pp; ++p, ++q)
            std::cout << '|' << *p << ' ' << *q << '\n';
    }

    void test_find()
    {
        using namespace std::string_view_literals;

        Pool<ListNode<std::string_view>> pool;

        auto head1 = make_list(pool, "foo"sv, "bar"sv, "baz"sv,
                                     "foobar"sv, "quux"sv);
        const auto* head1c = head1;

        auto head2 = find_node_if_not(head1, [](const std::string_view text) {
            return size(text) == 3u;
        });
        auto head2it = find_if_not(head1, [](const std::string_view text) {
            return size(text) == 3u;
        });
        auto head2cit = find_if_not(head1c, [](const std::string_view text) {
            return size(text) == 3u;
        });
        assert(begin(head2) == head2it && head2it == head2cit);

        auto head3 = find_node_if_not(head1, [](const std::string_view text) {
            return size(text) < 1000u;
        });
        auto head3it = find_if_not(head1, [](const std::string_view text) {
            return size(text) < 1000u;
        });
        auto head3cit = find_if_not(head1c, [](const std::string_view text) {
            return size(text) < 1000u;
        });
        assert(begin(head3) == head3it && head3it == head3cit);

        auto head4 = find_node_if(head1, [](const std::string_view text) {
            return text.find("ba") != text.npos;
        });
        auto head4it = find_if(head1, [](const std::string_view text) {
            return text.find("ba") != text.npos;
        });
        auto head4cit = find_if(head1c, [](const std::string_view text) {
            return text.find("ba") != text.npos;
        });
        assert(begin(head4) == head4it && head4it == head4cit);

        auto head5 = find_node_if(head1, [](const std::string_view text) {
            return empty(text);
        });
        auto head5it = find_if(head1, [](const std::string_view text) {
            return empty(text);
        });
        auto head5cit = find_if(head1c, [](const std::string_view text) {
            return empty(text);
        });
        assert(begin(head5) == head5it && head5it == head5cit);

        auto head6 = find_node(head1, "baz");
        auto head6it = find(head1, "baz");
        auto head6cit = find(head1c, "baz");
        assert(begin(head6) == head6it && head6it == head6cit);

        auto head7 = find_node(head1, "quuz");
        auto head7it = find(head1, "quuz");
        auto head7cit = find(head1c, "quuz");
        assert(begin(head7) == head7it && head7it == head7cit);

        // This doesn't (and shouldn't) compile. There are no find_node-family
        // overloads for pointers to const-qualified node types, because users
        // might wrongly expect to get back a pointer that couldn't modify the
        // list. (I'm unsure if this is the right design decision, though.)
        //const auto head4c = find_node(head1c, "baz");
    }

    void test_cycle()
    {
        Pool<ListNode<int>> pool;

        const auto a = []() {
            std::vector<int> v (10);
            std::iota(begin(v), end(v), 0);
            return v;
        }();

        auto head = make_list(pool, a);
        auto p = begin(head);
        std::advance(p, 5);
        concat(head, p);

        std::cout << "Cycle? " << has_cycle(head) << '\n';
    }

    void run_all_tests()
    {
        test_int();
        test_int_listnode();
        test_int_uniqueptr_listnode();
        test_int_nodefault_listnode();
        test_bitset_listnode();
        test_string_pair_listnode();

        test_copy();
        test_find();
        test_cycle();
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cout << std::boolalpha;

    run_all_tests();

    std::cout << std::flush; // for convenience when debugging
}
