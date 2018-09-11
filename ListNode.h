#ifndef HAVE_POOL_LISTNODE_H_
#define HAVE_POOL_LISTNODE_H_

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
        class const_iterator {
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
            const_iterator(const ListNode* const pos = nullptr) noexcept
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
            const ListNode* pos_;
        };

        class iterator {
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

            explicit constexpr iterator(ListNode* const pos = nullptr) noexcept
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
            ListNode* pos_;
        };

        constexpr ListNode() : key{}, next{} { }

        constexpr ListNode(const T& _key, ListNode* const _next)
            : key{_key}, next{_next} { }

        constexpr ListNode(T&& _key, ListNode* const _next)
                noexcept(std::is_nothrow_move_constructible_v<T>)
            : key{std::move(_key)}, next{_next} { }

        constexpr iterator begin() noexcept { return iterator{this}; }

        constexpr iterator end() noexcept { return iterator{}; }

        constexpr const_iterator begin() const noexcept
        {
            return const_iterator{this};
        }

        constexpr const_iterator end() const noexcept
        {
            return const_iterator{};
        }

        constexpr const_iterator cbegin() const noexcept { return begin(); }

        constexpr const_iterator cend() const noexcept { return end(); }

        T key;
        ListNode* next;
    };

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
}

#endif // ! HAVE_POOL_LISTNODE_H_
