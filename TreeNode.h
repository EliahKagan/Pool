// A binary tree node and associated helper functions and algorithms.

#ifndef HAVE_POOL_TREENODE_H_
#define HAVE_POOL_TREENODE_H_

#include <functional>
#include <iostream>
#include <iterator>
#include <stack>
#include <string_view>
#include <type_traits>
#include <utility>
#include "Pool.h"
#include "RaiiPrinter.h"

namespace ek {
    template<typename T>
    struct TreeNode {
        T key;
        TreeNode* left;
        TreeNode* right;

        TreeNode(const T& _key, TreeNode* const _left, TreeNode* const _right)
                noexcept(std::is_nothrow_copy_constructible_v<T>)
            : key(_key), left{_left}, right{_right} { }

        explicit TreeNode(const T& _key)
                noexcept(std::is_nothrow_copy_constructible_v<T>)
            : TreeNode{_key, nullptr, nullptr} { }

        TreeNode(T&& _key, TreeNode* const _left, TreeNode* const _right)
                noexcept(std::is_nothrow_move_constructible_v<T>)
            : key(std::move(_key)), left{_left}, right{_right} { }

        explicit TreeNode(T&& _key)
                noexcept(std::is_nothrow_move_constructible_v<T>)
            : TreeNode{std::move(_key), nullptr, nullptr} { }
    };

    namespace detail {
        template<typename P, typename FPre, typename FIn, typename FPost>
        void dfs_node_rec(const P root, FPre f_pre, FIn f_in, FPost f_post)
        {
            static_assert(std::is_convertible_v<decltype(root->left), P>);
            static_assert(std::is_convertible_v<decltype(root->right), P>);

            if (!root) return;

            f_pre(root);
            dfs_node_rec(P{root->left}, f_pre, f_in, f_post);
            f_in(root);
            dfs_node_rec(P{root->right}, f_pre, f_in, f_post);
            f_post(root);
        }

        template<typename P, typename FPre, typename FIn, typename FPost>
        void dfs_node_iter(const P root, FPre f_pre, FIn f_in, FPost f_post)
        {
            std::stack<P> nodes;
            P last_retreated {};

            while (root || !empty(nodes)) {
                // Go all the way left.
                for (; root; root = root->left) {
                    f_pre(root);
                    nodes.push_back(root);
                }

                const auto right = nodes.top()->right;

                // If we cannot go right, retreat.
                if (!right) {
                    last_retreated = nodes.top();
                    nodes.pop();
                    f_post(last_retreated);
                    continue;
                }


            }

            //
        }

        template<typename F>
        class OfKey {
        public:
            explicit constexpr OfKey(const F f)
                noexcept(std::is_nothrow_copy_constructible_v<F>) : f_{f} { }

            template<typename P>
            constexpr decltype(auto) operator()(const P node)
                noexcept(noexcept(std::declval<F&>()(node->key)))
                {
                    return f_(node->key);
                }

        private:
            F f_;
        };

        template<typename P, typename FPre, typename FIn, typename FPost>
        inline void dfs_rec(const P root, const FPre f_pre,
                            const FIn f_in, const FPost f_post)
        {
            dfs_node_rec(root, OfKey{f_pre}, OfKey{f_in}, OfKey{f_post});
        }

        template<typename P, typename FPre, typename FIn, typename FPost>
        inline void dfs_iter(const P root, const FPre f_pre,
                            const FIn f_in, const FPost f_post)
        {
            dfs_node_iter(root, OfKey{f_pre}, OfKey{f_in}, OfKey{f_post});
        }

        inline constexpr auto noop = [](const auto&...) noexcept { };
    }

    template<typename T, typename F>
    inline void preorder_rec(const TreeNode<T>* const root, const F f)
    {
        detail::dfs_rec(root, f, detail::noop, detail::noop);
    }

    template<typename T, typename F>
    inline void preorder_rec(TreeNode<T>* const root, const F f)
    {
        detail::dfs_rec(root, f, detail::noop, detail::noop);
    }

    template<typename T, typename F>
    inline void inorder_rec(const TreeNode<T>* const root, const F f)
    {
        detail::dfs_rec(root, detail::noop, f, detail::noop);
    }

    template<typename T, typename F>
    inline void inorder_rec(TreeNode<T>* const root, const F f)
    {
        detail::dfs_rec(root, detail::noop, f, detail::noop);
    }

    template<typename T, typename F>
    inline void postorder_rec(const TreeNode<T>* const root, const F f)
    {
        detail::dfs_rec(root, detail::noop, detail::noop, f);
    }

    template<typename T, typename F>
    inline void postorder_rec(TreeNode<T>* const root, const F f)
    {
        detail::dfs_rec(root, detail::noop, detail::noop, f);
    }

    template<typename T, typename F>
    inline void preorder_iter(const TreeNode<T>* const root, const F f)
    {
        detail::dfs_iter(root, f, detail::noop, detail::noop);
    }

    template<typename T, typename F>
    inline void preorder_iter(TreeNode<T>* const root, const F f)
    {
        detail::dfs_iter(root, f, detail::noop, detail::noop);
    }

    template<typename T, typename F>
    inline void inorder_iter(const TreeNode<T>* const root, const F f)
    {
        detail::dfs_iter(root, detail::noop, f, detail::noop);
    }

    template<typename T, typename F>
    inline void inorder_iter(TreeNode<T>* const root, const F f)
    {
        detail::dfs_iter(root, detail::noop, f, detail::noop);
    }

    template<typename T, typename F>
    inline void postorder_iter(const TreeNode<T>* const root, const F f)
    {
        detail::dfs_iter(root, detail::noop, detail::noop, f);
    }

    template<typename T, typename F>
    inline void postorder_iter(TreeNode<T>* const root, const F f)
    {
        detail::dfs_iter(root, detail::noop, detail::noop, f);
    }

    // TODO: {pre,in,post}order_rec_iter (like continuation-passing style)

    template<typename T>
    void print_preorder_rec(const TreeNode<T>* const root)
    {
        RaiiPrinter print;
        preorder_rec(root, std::ref(print));
    }

    template<typename T>
    void print_inorder_rec(const TreeNode<T>* const root)
    {
        RaiiPrinter print;
        inorder_rec(root, std::ref(print));
    }

    template<typename T>
    void print_postorder_rec(const TreeNode<T>* const root)
    {
        RaiiPrinter print;
        postorder_rec(root, std::ref(print));
    }
}

#endif // ! HAVE_POOL_TREENODE_H_
