//
// Created by hpf on 18-6-21.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <algorithm>
#include <iostream>
#include <vector>

template<typename Key, typename Value>
class AVLTree {
private:
    struct Node {
        Key key;
        Value value;
        Node *left;
        Node *right;
        int height;

        Node(Key key, Value value) {
            this->key = key;
            this->value = value;
            this->left = this->right = nullptr;
            height = 1;
        }

        Node(Node *node) {
            this->key = node->key;
            this->value = node->value;
            this->left = node->left;
            this->right = node->right;
            this->height = node->height;
        }
    };

    Node *root;
    int size;

public:

    AVLTree() {
        root = nullptr;
        size = 0;
    }

    ~AVLTree() {
        destroy(root);
    }

    int getSize() {
        return size;
    }

    int isEmpty() {
        return size == 0;
    }

    int getHeight(Node *node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int getBalanceFactor(Node *node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    bool isBST() {
        std::vector<Key> keys;
        inOrder(root, keys);
        for (int i = 1; i < keys.size(); ++i) {
            if (keys.at(i - 1) < keys.at(i)) {
                return false;
            }
        }
        return true;
    }

    bool isBalanced() {
        return isBalanced(root);
    }

    void add(Key key, Value value) {
        root = add(root, key, value);
    }

    bool contains(Key key) {
        return getNode(root, key) != nullptr;
    }

    Value *get(Key key) {
        Node *node = getNode(root, key);
        return node == nullptr ? nullptr : &(node->value);
    }

    void set(Key key, Value newValue) {
        Node *node = getNode(root, key);
        if (node != nullptr) {
            node->value = newValue;
        }
    }

    // 从二叉树中删除键值为key的节点
    Value *remove(Key key) {
        Node *node = getNode(root, key);
        if (node != nullptr) {
            root = remove(root, key);
            return &(node->value);
        }
        return nullptr;
    }

private:

    // 向以node为根的二叉搜索树中,插入节点(key, value)
    // 返回插入新节点后的二叉搜索树的根
    Node *add(Node *node, Key key, Value value) {
        if (node == nullptr) {
            size++;
            return new Node(key, value);
        }
        if (key == node->key) {
            node->value = value;
        } else if (key < node->key) {
            node->left = add(node->left, key, value);
        } else {
            node->right = add(node->right, key, value);
        }
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balanceFactor = getBalanceFactor(node);
        if (std::abs(balanceFactor) > 1) {
            std::cout << "unbalanced : " << balanceFactor;
        }
        return node;
    }

    // 在以node为根的二叉搜索树中查找key所对应的Node
    Node *getNode(Node *node, Key key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (key == node->key) {
            return node;
        } else if (key < node->key) {
            return getNode(node->left, key);
        } else {
            return getNode(node->right, key);
        }
    }

    void destroy(Node *node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
            size--;
        }
    }

    // 在以node为根的二叉搜索树中,返回最小键值的节点
    Node *minimum(Node *node) {
        if (node->left == nullptr)
            return node;
        return minimum(node->left);
    }

    // 在以node为根的二叉搜索树中,返回最大键值的节点
    Node *maximum(Node *node) {
        if (node->right == nullptr)
            return node;
        return maximum(node->right);
    }

    // 删除掉以node为根的二分搜索树中的最小节点
    // 返回删除节点后新的二分搜索树的根
    Node *removeMin(Node *node) {
        if (node->left == nullptr) {
            Node *rightNode = node->right;
            delete node;
            size--;
            return rightNode;
        }

        node->left = removeMin(node->left);
        return node;
    }

    // 删除掉以node为根的二分搜索树中的最大节点
    // 返回删除节点后新的二分搜索树的根
    Node *removeMax(Node *node) {
        if (node->right == nullptr) {
            Node *leftNode = node->left;
            delete node;
            size--;
            return leftNode;
        }

        node->right = removeMax(node->right);
        return node;
    }

    // 删除掉以node为根的二分搜索树中键值为key的节点
    // 返回删除节点后新的二分搜索树的根
    Node *remove(Node *node, Key key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (key < node->key) {
            node->left = remove(node->left, key);
            return node;
        } else if (key > node->key) {
            node->right = remove(node->right, key);
            return node;
        } else {
            if (node->left == nullptr) {
                Node *rightNode = node->right;
                delete node;
                size--;
                return rightNode;
            }

            if (node->right == nullptr) {
                Node *leftNode = node->left;
                delete node;
                size--;
                return leftNode;
            }

            Node *successor = new Node(minimum(node->right));
            //Node *precursor = new Node(maximum(node->right));
            size++;

            successor->right = removeMin(node->right);
            successor->left = node->left;
            //precursor->left = removeMax(node->left);
            //precursor->right = node->right;

            delete node;
            size--;

            return successor;
            //return precursor;
        }
    }

    void inOrder(Node *node, std::vector<Key> keys) {
        if (node == nullptr) {
            return;
        }
        inOrder(node->left, keys);
        keys.push_back(node->key);
        inOrder(node->right, keys);
    }

    bool isBalanced(Node *node) {
        if (node == nullptr) {
            return true;
        }

        int balanceFactor = getBalanceFactor(node);
        if (std::abs(balanceFactor) > 1) {
            return false;
        }

        return isBalanced(node->left) && isBalanced(node->right);
    }
};

#endif //AVLTREE_AVLTREE_H
