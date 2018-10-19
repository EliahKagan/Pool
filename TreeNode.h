// A binary tree node and associated helper functions and algorithms.

#ifndef HAVE_POOL_TREENODE_H_
#define HAVE_POOL_TREENODE_H_

namespace ek {
    template<typename T>
    struct TreeNode {
        T key;
        TreeNode* left;
        TreeNode* right;
    };
}

#endif // ! HAVE_POOL_TREENODE_H_
