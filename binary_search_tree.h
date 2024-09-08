#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <string>
#include <vector>
#include "metric.h"
using namespace std;

struct TreeNode
{
    string key;
    TreeNode *left, *right;

    TreeNode(const string &key);
};

class BinarySearchTree
{
private:
    TreeNode *root;

    // Helper functions
    TreeNode *insert(TreeNode *node, const string &key);
    TreeNode *findMin(TreeNode *node);
    TreeNode *remove(TreeNode *node, const string &key);
    bool search(TreeNode *node, const string &key) const;
    void inorderDisplay(TreeNode *node) const;

public:
    mutable Metric metric;
    BinarySearchTree();

    // Insert key into BST
    void insert(const string &key);

    // Delete a key
    void remove(const string &key);

    // Search for a key
    bool search(const string &key) const;

    // Display the BST (in-order traversal)
    void display() const;
};

#endif
