#include "closed_hashing_linear_probing.h"
#include "open_hashing_sorted_list.h"
#include "open_hashing_unsorted_list.h"
#include "binary_search_tree.h"
#include "utility_functions.h"
#include "metric.h"
#include <iostream>
#include <string>
using namespace std;

TreeNode::TreeNode(const string &key) : key(key), left(nullptr), right(nullptr) {}

TreeNode *BinarySearchTree::insert(TreeNode *node, const string &key)
{
    metric.incrementProbeCount();
    if (node == nullptr)
    {
        return new TreeNode(key); // Insert a new node if the current position is empty
    }
    if (key < node->key)
    {
        node->left = insert(node->left, key); // Insert into the left subtree
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key); // Insert into the right subtree
    }
    return node;
}
bool BinarySearchTree::search(TreeNode *node, const string &key) const
{
    metric.incrementProbeCount();
    if (node == nullptr)
    {
        // cout << key << " not found in the BST" << endl;
        return false; // Key not found
    }
    if (key == node->key)
    {
        // cout << key << " found in the BST" << endl;
        return true; // Key found
    }
    else if (key < node->key)
    {
        return search(node->left, key); // Search in the left subtree
    }
    else
    {
        return search(node->right, key); // Search in the right subtree
    }
}
TreeNode *BinarySearchTree::findMin(TreeNode *node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

TreeNode *BinarySearchTree::remove(TreeNode *node, const string &key)
{
    metric.incrementProbeCount();
    if (node == nullptr)
    {
        // cout << key << " not found in the BST" << endl;
        return nullptr; // Key not found
    }
    if (key < node->key)
    {
        node->left = remove(node->left, key); // Remove from left subtree
    }
    else if (key > node->key)
    {
        node->right = remove(node->right, key); // Remove from right subtree
    }
    else
    {

        // Node to be deleted is found
        if (node->left == nullptr && node->right == nullptr)
        {
            // Case 1: No children (leaf node)
            delete node;
            return nullptr;
        }
        else if (node->left == nullptr)
        {
            // Case 2: One child (right)
            TreeNode *temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr)
        {
            // Case 2: One child (left)
            TreeNode *temp = node->left;
            delete node;
            return temp;
        }
        else
        {
            // Case 3: Two children
            TreeNode *temp = findMin(node->right);        // Find the minimum in the right subtree
            node->key = temp->key;                        // Replace the node's key with the minimum key
            node->right = remove(node->right, temp->key); // Remove the minimum node
        }
        // cout << key << " deleted from BST" << endl;
    }
    return node;
}

void BinarySearchTree::inorderDisplay(TreeNode *node) const
{
    if (node == nullptr)
    {
        return;
    }
    inorderDisplay(node->left);
    cout << node->key << " ";
    inorderDisplay(node->right);
}

BinarySearchTree::BinarySearchTree() : root(nullptr) {}
void BinarySearchTree::insert(const string &key)
{
    metric.startProbeCounting();
    root = insert(root, key);
    metric.recordProbeCount("insert", true);
}
bool BinarySearchTree::search(const string &key) const
{
    metric.startProbeCounting();
    bool b;
    b = search(root, key);
    if (b)
    {
        metric.recordProbeCount("search", true);
    }
    else
    {
        metric.recordProbeCount("search", false);
    }
    return b;
}
void BinarySearchTree::remove(const string &key)
{
    metric.startProbeCounting();
    root = remove(root, key);
    if (root != nullptr)
    {
        metric.recordProbeCount("delete", true);
    }
    else
    {
        metric.recordProbeCount("delete", false);
    }
}
void BinarySearchTree::display() const
{
    inorderDisplay(root);
    cout << endl;
}