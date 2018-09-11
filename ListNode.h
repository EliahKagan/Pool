#ifndef HAVE_POOL_LISTNODE_H_
#define HAVE_POOL_LISTNODE_H_

#include <initializer_list>
#include <iterator>
#include <type_traits>
#include <utility>
#include "Pool.h"

template<typename T>
struct ListNode {
    ListNode() : key{}, next{} { }

    ListNode(const T& _key, ListNode* const _next) : key{_key}, next{_next} { }

    ListNode(T&& _key, ListNode* const _next)
            noexcept(std::is_nothrow_move_constructible_v<T>)
        : key{std::move(_key)}, next{_next} { }

    T key;
    ListNode* next;
};

template<typename T, typename I>
std::enable_if_t<
    std::is_same_v<typename std::iterator_traits<I>::value_type, T>,
    ListNode<T>*>
make_list(Pool<ListNode<T>>& pool, I first, const I last)
{
    if (first == last) return nullptr;

    const auto head = pool(*first, nullptr);

    for (auto cur = head; ++first != last; cur = cur->next)
        cur->next = pool(*first, nullptr);

    return head;
}

namespace detail { // TODO: maybe put this in a different header
    using std::begin, std::end;

    template<typename C, typename T>
    constexpr std::enable_if_t<
        std::is_same_v<decltype(begin(std::declval<C>())),
                       decltype(end(std::declval<C>()))>
            && std::is_same_v<typename std::iterator_traits<
                                decltype(begin(std::declval<C>()))>::value_type,
                              T>,
        std::true_type>
    collects_helper(int) noexcept { return {}; }

    template<typename C, typename T>
    constexpr std::false_type collects_helper(...) noexcept { return {}; }

    template<typename C, typename T>
    inline constexpr bool collects = collects_helper<C, T>(0).value;
}

template<typename T, typename C>
std::enable_if_t<detail::collects<C, T>, ListNode<T>*>
make_list(Pool<ListNode<T>>& pool, C&& c)
{
    using std::begin, std::end;
    return make_list(pool, begin(c), end(c));
}

template<typename T>
ListNode<T>* make_list(Pool<ListNode<T>>& pool,
                       const std::initializer_list<T> ilist)
{
    return make_list(pool, cbegin(ilist), cend(ilist));
}

template<typename T>
constexpr ListNode<T>* make_list(Pool<ListNode<T>>&) noexcept
{
    return nullptr;
}

template<typename T, typename... Ts>
ListNode<T>* make_list(Pool<ListNode<T>>& pool, const T& x, Ts&&... xs)
{
    return pool(x, make_list(pool, std::forward<Ts>(xs)...));
}

template<typename T, typename... Ts>
ListNode<T>* make_list(Pool<ListNode<T>>& pool, T&& x, Ts&&... xs)
{
    return pool(std::move(x), make_list(pool, std::forward<Ts>(xs)...));
}

#endif // ! HAVE_POOL_LISTNODE_H_
