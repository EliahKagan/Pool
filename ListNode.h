#ifndef HAVE_POOL_LISTNODE_H_
#define HAVE_POOL_LISTNODE_H_

#include <initializer_list>
#include <utility>
#include "Pool.h"

template<typename T>
struct ListNode {
    ListNode() : key{}, next{} { }

    ListNode(const T& _key, ListNode* const _next) : key{_key}, next{_next} { }

    ListNode(T&& _key, ListNode* const _next) : key{std::forward<T>(_key)},
                                                next{_next} { }

    T key;
    ListNode* next;
};

template<typename T>
ListNode<T>* make_list(Pool<ListNode<T>>& pool,
                       const std::initializer_list<T> ilist)
{
    ListNode<T> sentinel {};

    auto cur = &sentinel;
    for (const auto& x : ilist) {
        cur->next = pool(x, nullptr);
        cur = cur->next;
    }

    return sentinel.next;
}

namespace detail {
    template<typename T, typename... Ts>
    ListNode<T>* build_list(Pool<ListNode<T>>& pool, ListNode<T>* const head,
                            const Ts&... xs, const T& x)
    {
        const auto new_head = pool(x, head);

        if constexpr (sizeof...(xs) == 0)
            return new_head;
        else
            return build_list(pool, new_head, xs...);
    }
}

template<typename T, typename... Ts>
ListNode<T>* make_list(Pool<ListNode<T>>& pool, const Ts&... xs, const T& x)
{
    return detail::build_list(pool, nullptr, xs..., x);
}

#endif // ! HAVE_POOL_LISTNODE_H_
