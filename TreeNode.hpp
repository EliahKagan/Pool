// A binary tree node and associated helper functions and algorithms.
//
// Copyright (c) 2018 Eliah Kagan
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
// SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
// OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
// CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#ifndef HAVE_POOL_TREENODE_HPP_
#define HAVE_POOL_TREENODE_HPP_

#include <functional>
#include <iostream>
#include <iterator>
#include <stack>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>
#include "Pool.hpp"
#include "RaiiPrinter.hpp"
#include "util.h"

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
        void dfs_node_iter(P root, FPre f_pre, FIn f_in, FPost f_post)
        {
            P post {};

            for (std::stack<P> nodes; root || !empty(nodes); ) {
                // Go left all the way. Run the preorder handler on each node.
                for (; root; root = root->left) {
                    f_pre(root);
                    nodes.push(root);
                }

                const auto cur = nodes.top();

                if (!cur->right || cur->right != post) {
                    // We have not been right of here. Run the inorder handler.
                    f_in(cur);
                }

                if (cur->right && cur->right != post) {
                    // We haven't gone right of here and we can, so do it.
                    root = cur->right;
                } else {
                    // There is nothing more to explore from this position.
                    // Run the postorder handler here, and retreat.
                    post = cur;
                    f_post(post);
                    nodes.pop();
                }
            }
        }

        template<typename P, typename FPre, typename FIn, typename FPost>
        void dfs_node_rec_iter(P root, FPre f_pre, FIn f_in, FPost f_post)
        {
            enum class Action {go_left, go_right, retreat};

            std::stack<std::tuple<P, Action>> frames;
            if (root) frames.emplace(root, Action::go_left);

            while (!empty(frames)) {
                auto& [node, action] = frames.top();

                switch (action) {
                case Action::go_left:
                    f_pre(node);
                    action = Action::go_right;
                    if (node->left)
                        frames.emplace(node->left, Action::go_left);
                    continue;

                case Action::go_right:
                    f_in(node);
                    action = Action::retreat;
                    if (node->right)
                        frames.emplace(node->right, Action::go_right);
                    continue;

                case Action::retreat:
                    f_post(node);
                    frames.pop();
                    continue;
                }

                NOT_REACHED();
            }
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

        template<typename P, typename FPre, typename FIn, typename FPost>
        inline void dfs_rec_iter(const P root, const FPre f_pre,
                                 const FIn f_in, const FPost f_post)
        {
            dfs_node_rec_iter(root, OfKey{f_pre}, OfKey{f_in}, OfKey{f_post});
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

    template<typename T, typename F>
    inline void preorder_rec_iter(const TreeNode<T>* const root, const F f)
    {
        detail::dfs_rec_iter(root, f, detail::noop, detail::noop);
    }

    template<typename T, typename F>
    inline void preorder_rec_iter(TreeNode<T>* const root, const F f)
    {
        detail::dfs_rec_iter(root, f, detail::noop, detail::noop);
    }

    template<typename T, typename F>
    inline void inorder_rec_iter(const TreeNode<T>* const root, const F f)
    {
        detail::dfs_rec_iter(root, detail::noop, f, detail::noop);
    }

    template<typename T, typename F>
    inline void inorder_rec_iter(TreeNode<T>* const root, const F f)
    {
        detail::dfs_rec_iter(root, detail::noop, f, detail::noop);
    }

    template<typename T, typename F>
    inline void postorder_rec_iter(const TreeNode<T>* const root, const F f)
    {
        detail::dfs_rec_iter(root, detail::noop, detail::noop, f);
    }

    template<typename T, typename F>
    inline void postorder_rec_iter(TreeNode<T>* const root, const F f)
    {
        detail::dfs_rec_iter(root, detail::noop, detail::noop, f);
    }

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

    template<typename T>
    void print_preorder_iter(const TreeNode<T>* const root)
    {
        RaiiPrinter print;
        preorder_iter(root, std::ref(print));
    }

    template<typename T>
    void print_inorder_iter(const TreeNode<T>* const root)
    {
        RaiiPrinter print;
        inorder_iter(root, std::ref(print));
    }

    template<typename T>
    void print_postorder_iter(const TreeNode<T>* const root)
    {
        RaiiPrinter print;
        postorder_iter(root, std::ref(print));
    }

    template<typename T>
    void print_preorder_rec_iter(const TreeNode<T>* const root)
    {
        RaiiPrinter print;
        preorder_rec_iter(root, std::ref(print));
    }

    template<typename T>
    void print_inorder_rec_iter(const TreeNode<T>* const root)
    {
        RaiiPrinter print;
        inorder_rec_iter(root, std::ref(print));
    }

    template<typename T>
    void print_postorder_rec_iter(const TreeNode<T>* const root)
    {
        RaiiPrinter print;
        postorder_rec_iter(root, std::ref(print));
    }

    // TODO: provide preorder, inorder, postorder, and levelorder iterators
}

#endif // ! HAVE_POOL_TREENODE_HPP_
