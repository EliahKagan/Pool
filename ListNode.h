#ifndef HAVE_POOL_LISTNODE_H_
#define HAVE_POOL_LISTNODE_H_

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <type_traits>
#include <utility>
#include <vector>
#include "Pool.h"

namespace ek {
    template<typename T>
    struct ListNode {
        class const_iterator;
        class iterator;

        constexpr ListNode() : key{}, next{} { }

        constexpr ListNode(const T& _key, ListNode* const _next)
            : key{_key}, next{_next} { }

        constexpr ListNode(T&& _key, ListNode* const _next)
                noexcept(std::is_nothrow_move_constructible_v<T>)
            : key{std::move(_key)}, next{_next} { }

        constexpr iterator begin() noexcept;
        constexpr iterator end() noexcept;
        constexpr const_iterator begin() const noexcept;
        constexpr const_iterator end() const noexcept;
        constexpr const_iterator cbegin() const noexcept;
        constexpr const_iterator cend() const noexcept;

        T key;
        ListNode* next;
    };

    template<typename T>
    class ListNode<T>::const_iterator {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::forward_iterator_tag;

        friend constexpr bool operator==(const const_iterator& lhs,
                                         const const_iterator& rhs) noexcept
        {
            return lhs.pos_ == rhs.pos_;
        }

        friend constexpr bool operator!=(const const_iterator& lhs,
                                         const const_iterator& rhs) noexcept
        {
            return lhs.pos_ != rhs.pos_;
        }

        explicit constexpr
        const_iterator(const ListNode<T>* const pos = nullptr) noexcept
            : pos_{pos} { }

        constexpr const_iterator& operator++() noexcept
        {
            pos_ = pos_->next;
            return *this;
        }

        constexpr const_iterator operator++(int) noexcept
        {
            const auto ret = *this;
            ++*this;
            return ret;
        }

        constexpr reference operator*() const noexcept { return pos_->key; }

        constexpr pointer operator->() const noexcept { return &pos_->key; }

    private:
        const ListNode<T>* pos_;
    };

    namespace detail {
        template<typename T>
        constexpr ListNode<T>*
        node(const typename ListNode<T>::iterator&) noexcept;
    }

    template<typename T>
    class ListNode<T>::iterator {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::forward_iterator_tag;

        friend constexpr bool
        operator==(const iterator& lhs, const iterator& rhs) noexcept
        {
            return lhs.pos_ == rhs.pos_;
        }

        friend constexpr bool
        operator!=(const iterator& lhs, const iterator& rhs) noexcept
        {
            return lhs.pos_ != rhs.pos_;
        }

        explicit constexpr iterator(ListNode<T>* const pos = nullptr) noexcept
            : pos_{pos} { }

        constexpr iterator& operator++() noexcept
        {
            pos_ = pos_->next;
            return *this;
        }

        constexpr iterator operator++(int) noexcept
        {
            const auto ret = *this;
            ++*this;
            return ret;
        }

        constexpr reference operator*() const noexcept { return pos_->key; }

        constexpr pointer operator->() const noexcept { return &pos_->key; }

        constexpr operator const_iterator() const noexcept
        {
            return const_iterator{pos_};
        }

    private:
        friend constexpr ListNode<T>* detail::node<T>(const iterator&) noexcept;

        ListNode<T>* pos_;
    };

    namespace detail {
        template<typename T>
        constexpr ListNode<T>*
        node(const typename ListNode<T>::iterator& p) noexcept
        {
            return p.pos_;
        }
    }

    template<typename T>
    constexpr auto ListNode<T>::begin() noexcept -> iterator
    {
        return iterator{this};
    }

    template<typename T>
    constexpr auto ListNode<T>::end() noexcept -> iterator
    {
        return iterator{};
    }

    template<typename T>
    constexpr auto ListNode<T>::begin() const noexcept -> const_iterator
    {
        return const_iterator{this};
    }

    template<typename T>
    constexpr auto ListNode<T>::end() const noexcept -> const_iterator
    {
        return const_iterator{};
    }

    template<typename T>
    constexpr auto ListNode<T>::cbegin() const noexcept -> const_iterator
    {
        return begin();
    }

    template<typename T>
    constexpr auto ListNode<T>::cend() const noexcept -> const_iterator
    {
        return end();
    }

    template<typename T>
    constexpr typename ListNode<T>::iterator
    begin(ListNode<T>* const head) noexcept
    {
        return std::begin(*head);
    }

    template<typename T>
    constexpr typename ListNode<T>::iterator
    end(ListNode<T>* const head) noexcept
    {
        return std::end(*head);
    }

    template<typename T>
    constexpr typename ListNode<T>::const_iterator
    begin(const ListNode<T>* const head) noexcept
    {
        return std::begin(*head);
    }

    template<typename T>
    constexpr typename ListNode<T>::const_iterator
    end(const ListNode<T>* const head) noexcept
    {
        return std::end(*head);
    }

    template<typename T>
    constexpr typename ListNode<T>::const_iterator
    cbegin(const ListNode<T>* const head) noexcept
    {
        return std::cbegin(*head);
    }

    template<typename T>
    constexpr typename ListNode<T>::const_iterator
    cend(const ListNode<T>* const head) noexcept
    {
        return std::cend(*head);
    }

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

    namespace detail {
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
    inline std::enable_if_t<detail::collects<C, T>, ListNode<T>*>
    make_list(Pool<ListNode<T>>& pool, C&& c)
    {
        using std::begin, std::end;
        return make_list(pool, begin(c), end(c));
    }

    template<typename T>
    inline ListNode<T>* make_list(Pool<ListNode<T>>& pool,
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

    template<typename T>
    std::vector<T> vec(const ListNode<T>* const head)
    {
        return std::vector<T>(cbegin(head), cend(head));
    }

    template<typename T>
    inline typename ListNode<T>::const_iterator
    find(const ListNode<T>* const head, const T& key)
    {
        return std::find(cbegin(head), cend(head), key);
    }

    template<typename T>
    inline typename ListNode<T>::iterator
    find(ListNode<T>* const head, const T& key)
    {
        return std::find(begin(head), end(head), key);
    }

    template<typename T, typename F>
    inline typename ListNode<T>::const_iterator
    find_if(const ListNode<T>* const head, const F f)
    {
        return std::find_if(cbegin(head), cend(head), f);
    }

    template<typename T, typename F>
    inline typename ListNode<T>::iterator
    find_if(ListNode<T>* const head, const F f)
    {
        return std::find_if(begin(head), end(head), f);
    }

    template<typename T, typename F>
    inline typename ListNode<T>::const_iterator
    find_if_not(const ListNode<T>* const head, const F f)
    {
        return std::find_if_not(cbegin(head), cend(head), f);
    }

    template<typename T, typename F>
    inline typename ListNode<T>::iterator
    find_if_not(ListNode<T>* const head, const F f)
    {
        return std::find_if_not(begin(head), end(head), f);
    }

    template<typename T>
    inline ListNode<T>* find_node(ListNode<T>* const head, const T& key)
    {
        return detail::node(find(head, key));
    }

    template<typename T, typename F>
    inline ListNode<T>* find_node_if(ListNode<T>* const head, const F f)
    {
        return detail::node(find_if(head, f));
    }

    template<typename T, typename F>
    inline ListNode<T>* find_node_if_not(ListNode<T>* const head, const F f)
    {
        return detail::node(find_if_not(head, f));
    }
}

#endif // ! HAVE_POOL_LISTNODE_H_
