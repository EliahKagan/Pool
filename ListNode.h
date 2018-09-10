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

#endif // ! HAVE_POOL_LISTNODE_H_
