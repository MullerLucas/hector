#pragma once

#include "linked_list.hpp"
#include <functional>
#include <ostream>

namespace hell
{

// ----------------------------------------------

template<typename T>
struct BSTreeNode
{
    T value;
    BSTreeNode<T>* left;
    BSTreeNode<T>* right;
};

// ----------------------------------------------

template<typename T>
using FnTraverseValues = const std::function<void(const T&)>&;

template<typename T>
using FnTraverseNodesMut = const std::function<void(BSTreeNode<T>*)>&;

// ----------------------------------------------

template<typename T>
class BSTree
{
private:
    BSTreeNode<T>* root;

public:
    BSTree();
    BSTree(const BSTree& rhs);
    BSTree(BSTree&& rhs);
    ~BSTree();

    void push(T value);

    void traverse_level_order(FnTraverseValues<T> func) const;
    void traverse_pre_order  (FnTraverseValues<T> func) const;
    void traverse_in_order   (FnTraverseValues<T> func) const;
    void traverse_post_order (FnTraverseValues<T> func) const;

private:
    BSTreeNode<T>* find_parent_node(T& value) const;

    static void traverse_values_pre_order_recursive (BSTreeNode<T>* node, FnTraverseValues<T> func);
    static void traverse_values_in_order_recursive  (BSTreeNode<T>* node, FnTraverseValues<T> func);
    static void traverse_values_post_order_recursive(BSTreeNode<T>* node, FnTraverseValues<T> func);

    static void traverse_nodes_post_order_recursive(BSTreeNode<T>* node, FnTraverseNodesMut<T> func);
};

// -----

template<typename T>
BSTree<T>::BSTree()
    : root(nullptr)
{}

template<typename T>
BSTree<T>::~BSTree()
{
    if (this->root == nullptr)
        return;

    BSTree<T>::traverse_nodes_post_order_recursive(this->root, [](BSTreeNode<T>* node) {
        delete node;
    });

    this->root = nullptr;
}

// -----

template<typename T>
void BSTree<T>::push(T value)
{
    auto new_node = new BSTreeNode<T> {};
    new_node->value = value;

    auto parent_node = this->find_parent_node(value);

    if (parent_node == nullptr)
    {
        this->root = new_node;
        return;
    }

    if (new_node->value <= parent_node->value)
    {
        new_node->left    = parent_node->left;
        parent_node->left = new_node;
    }
    else
    {
        new_node->right    = parent_node->right;
        parent_node->right = new_node;
    }
}

// -----

template<typename T>
void BSTree<T>::traverse_pre_order(FnTraverseValues<T> func) const
{
    if (this->root == nullptr)
        return;

    BSTree<T>::traverse_values_pre_order_recursive(this->root, func);
}

template<typename T>
void BSTree<T>::traverse_in_order(FnTraverseValues<T> func) const
{
    if (this->root == nullptr)
        return;

    BSTree<T>::traverse_values_in_order_recursive(this->root, func);
}

template<typename T>
void BSTree<T>::traverse_post_order(FnTraverseValues<T> func) const
{
    if (this->root == nullptr)
        return;

    BSTree<T>::traverse_values_post_order_recursive(this->root, func);
}

// -----

template<typename T>
BSTreeNode<T>* BSTree<T>::find_parent_node(T& value) const
{
    auto node = this->root;
    while (node != nullptr)
    {
        if (value <= node->value)
        {
            if (node->left == nullptr)
                return node;

            node = node->left;
        }
        else
        {
            if (node->right == nullptr)
                return node;

            node = node->right;
        }
    }

    return nullptr;
}

template<typename T>
void BSTree<T>::traverse_values_pre_order_recursive(BSTreeNode<T>* node, FnTraverseValues<T> func)
{
    func(node->value);

    if (node->left != nullptr)
        BSTree<T>::traverse_values_pre_order_recursive(node->left, func);
    if (node->right != nullptr)
        BSTree<T>::traverse_values_pre_order_recursive(node->right, func);
}

template<typename T>
void BSTree<T>::traverse_values_in_order_recursive(BSTreeNode<T>* node, FnTraverseValues<T> func)
{
    if (node->left != nullptr)
        BSTree<T>::traverse_values_in_order_recursive(node->left, func);

    func(node->value);

    if (node->right != nullptr)
        BSTree<T>::traverse_values_in_order_recursive(node->right, func);
}

template<typename T>
void BSTree<T>::traverse_values_post_order_recursive(BSTreeNode<T>* node, FnTraverseValues<T> func)
{
    if (node->left != nullptr)
        BSTree<T>::traverse_values_post_order_recursive(node->left, func);
    if (node->right != nullptr)
        BSTree<T>::traverse_values_post_order_recursive(node->right, func);

    func(node->value);
}

// -----

template<typename T>
void BSTree<T>::traverse_nodes_post_order_recursive(BSTreeNode<T>* node, FnTraverseNodesMut<T> func)
{
    if (node->left != nullptr)
        BSTree<T>::traverse_nodes_post_order_recursive(node->left, func);
    if (node->right != nullptr)
        BSTree<T>::traverse_nodes_post_order_recursive(node->right, func);

    func(node);
}

// ----------------------------------------------

}
