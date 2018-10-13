#ifndef HAVE_POOL_LISTNODE_H_
#define HAVE_POOL_LISTNODE_H_

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <ostream>
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

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const ListNode<T>* const head)
    {
        out << '[';

        auto sep = "";
        for (const auto& x : head) {
            out << sep << x;
            sep = ", ";
        }

        return out << ']';
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
    void concat(ListNode<T>* src_head, ListNode<T>* const dest_node) noexcept
    {
        assert(src_head); // TODO: consider using gsl::not_null

        while (src_head->next) src_head = src_head->next;
        src_head->next = dest_node;
    }

    template<typename T>
    inline void concat(ListNode<T>* const src_head,
                       const typename ListNode<T>::iterator dest_iter) noexcept
    {
        concat(src_head, detail::node<T>(dest_iter));
    }

    namespace detail {
        template<typename I>
        bool has_cycle_helper(I first, const I last,
                              std::forward_iterator_tag) noexcept
        {
            auto leader = first;

            while (leader != last && ++leader != last) {
                if (first == leader) return true;
                ++first;
                ++leader;
            }

            return false;
        }
    }

    template<typename I>
    bool has_cycle(I first, const I last) noexcept
    {
        return detail::has_cycle_helper(first, last,
                typename std::iterator_traits<I>::iterator_category{});
    }

    template<typename T>
    bool has_cycle(const ListNode<T>* head) noexcept
    {
        return has_cycle(cbegin(head), cend(head));
    }

    template<typename T>
    std::vector<T> vec(const ListNode<T>* const head)
    {
        return std::vector<T>(cbegin(head), cend(head));
    }

    template<typename T, typename U>
    inline typename ListNode<T>::const_iterator
    find(const ListNode<T>* const head, const U& key)
    {
        return std::find(cbegin(head), cend(head), key);
    }

    template<typename T, typename U>
    inline typename ListNode<T>::iterator
    find(ListNode<T>* const head, const U& key)
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

    template<typename T, typename U>
    inline ListNode<T>* find_node(ListNode<T>* const head, const U& key)
    {
        return detail::node<T>(find(head, key));
    }

    template<typename T, typename F>
    inline ListNode<T>* find_node_if(ListNode<T>* const head, const F f)
    {
        return detail::node<T>(find_if(head, f));
    }

    template<typename T, typename F>
    inline ListNode<T>* find_node_if_not(ListNode<T>* const head, const F f)
    {
        return detail::node<T>(find_if_not(head, f));
    }

    constexpr bool equal(std::nullptr_t, std::nullptr_t) noexcept
    {
        return true;
    }

    template<typename T>
    constexpr bool equal(const ListNode<T>* const head, std::nullptr_t) noexcept
    {
        return !head;
    }

    template<typename U>
    constexpr bool equal(std::nullptr_t, const ListNode<U>* const head) noexcept
    {
        return !head;
    }

    template<typename T, typename U>
    inline bool equal(const ListNode<T>* const head1,
                      const ListNode<U>* const head2) noexcept
    {
        return std::equal(cbegin(head1), cend(head1),
                          cbegin(head2), cend(head2));
    }

    template<typename T>
    bool equal(const ListNode<T>* head1, const ListNode<T>* head2) noexcept
    {
        // When the key types are the same, the lists could share nodes. In such
        // cases, this algorithm is likely faster than the one using std::equal.
        for (; head1 != head2; head1 = head1->next, head2 = head2->next)
            if (!(head1 && head2 && head1->key == head2->key)) return false;

        return true;
    }

    namespace detail {
        template<typename X>
        constexpr auto be_const(const X* const p) noexcept { return p; }
    }

    template<typename F>
    constexpr bool equal(std::nullptr_t, std::nullptr_t, F) noexcept
    {
        return true;
    }

    template<typename T, typename F>
    constexpr bool
    equal(const ListNode<T>* const head, std::nullptr_t, F) noexcept
    {
        return !head;
    }

    template<typename U, typename F>
    constexpr bool
    equal(std::nullptr_t, const ListNode<U>* const head, F) noexcept
    {
        return !head;
    }

    template<typename T, typename U, typename F>
    inline bool equal(const ListNode<T>* const head1,
                      const ListNode<U>* const head2, const F f)
    {
        return std::equal(cbegin(head1), cend(head1),
                          cbegin(head2), cend(head2), f);
    }

    // Prevents std::equal from being called inadvertently.
    template<typename T, typename U, typename F>
    inline bool equal(ListNode<T>* const head1,
                      ListNode<U>* const head2, const F f)
    {
        return equal(detail::be_const(head1), detail::be_const(head2), f);
    }

    template<typename T, typename F>
    bool equal(const ListNode<T>* head1, const ListNode<T>* head2, F f)
    {
        // When the key types are the same, the lists could share nodes. In such
        // cases, this algorithm is likely faster than the one using std::equal.
        for (; head1 != head2; head1 = head1->next, head2 = head2->next)
            if (!(head1 && head2 && f(head1->key, head2->key))) return false;

        return true;
    }

    template<typename T, typename F>
    inline bool equal(ListNode<T>* const head1,
                      ListNode<T>* const head2, const F f)
    {
        return equal(detail::be_const(head1), detail::be_const(head2), f);
    }

    template<typename T>
    ListNode<T>* reverse(ListNode<T>* head)
    {
        ListNode<T>* acc {};

        while (head) {
            const auto next = head->next;
            head->next = acc;
            acc = head;
            head = next;
        }

        return acc;
    }

    template<typename T, typename F>
    std::pair<ListNode<T>*, ListNode<T>*> split(ListNode<T>* head, F f)
    {
        ListNode<T>* true_head {};
        ListNode<T>* false_head {};
        auto true_destp = &true_head, false_destp = &false_head;

        for (; head; head = head->next) {
            auto& destp = (f(head->key) ? true_destp : false_destp);
            *destp = head;
            destp = &head->next;
        }

        *true_destp = *false_destp = nullptr;
        return {true_head, false_head};
    }

    template<typename T, typename F>
    ListNode<T>* merge(ListNode<T>* head1, ListNode<T>* head2, F f)
    {
        ListNode<T>* ret {};
        auto destp = &ret;

        for (; head1 && head2; destp = &(*destp)->next) {
            auto& src = f(head2->key, head1->key) ? head2 : head1;
            *destp = src;
            src = src->next;
        }

        *destp = (head1 ? head1 : head2);
        return ret;
    }

    template<typename T>
    ListNode<T>* merge(ListNode<T>* head1, ListNode<T>* head2)
    {
        return merge(head1, head2, std::less{});
    }
}

#endif // ! HAVE_POOL_LISTNODE_H_
