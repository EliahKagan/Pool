// A binary tree node and associated helper functions and algorithms.

#ifndef HAVE_POOL_TREENODE_H_
#define HAVE_POOL_TREENODE_H_

#include <type_traits>
#include <utility>
#include "Pool.h"

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
        struct Noop {
            template<typename... Args>
            constexpr void operator()(const Args&...) const noexcept { }
        };

        constexpr Noop noop;

        template<typename P, typename FPre, typename FIn, typename FPost>
        void dfs_node_rec(const P root, FPre f_pre, FIn f_in, FPost f_post)
        {

        }

        template<typename P, typename FPre, typename FIn, typename FPost>
        inline void dfs_rec(const P root, const FPre f_pre,
                            const FIn f_in, const FPost f_post)
        {
            dfs_node_rec(root, )
        }
    }
}

#endif // ! HAVE_POOL_TREENODE_H_
