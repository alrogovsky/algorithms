//
//  main.cpp
//  task3-2
//
//  Created by Alexander Rogovsky on 20.05.15.
//  Copyright (c) 2015 Alexander Rogovsky. All rights reserved.
//

#include <iostream>

template <class T>
class TNode{
public:
    T data;
    TNode* left;
    TNode* right;
    
    TNode<T>(T d) : data(d), left(NULL), right(NULL) {}
    
    TNode* find(T data) {
        TNode *current = this;
        
        while (current != NULL) {
            if (current->data > data) {
                if (current->left != NULL) {
                    current = current->left;
                } else {
                    return current;
                }
            } else if (current->data < data) {
                if (current->right != NULL) {
                    current = current->right;
                } else {
                    return current;
                }
            } else {
                return current;
            }
        }
        
        return NULL;
    }
};

template <class T>
class BSTree{
public:
    TNode<T> *root;
    
    BSTree(T* root) : root(root) {}
    BSTree(): root(NULL) {}
    
    void add(T data) {
        TNode<T> *node = root->find(data);
        
        if (node == NULL) {
            root = new TNode<T>(data);
        } else if (node->data >= data) {
            node->left = new TNode<T>(data);
        } else {
            node->right = new TNode<T>(data);
        }
    }
};


template <class T>
void Traverse(TNode<T> *node) {
    if(node == NULL)
        return;
    
    std::cout << node->data << " ";
    
    Traverse(node->left);
    Traverse(node->right);
    
}

int main() {
    
    size_t n;
    
    std::cin >> n;
    
    BSTree<int> tree;
    
    for (size_t i = 0; i < n; ++i) {
        int data;
        
        std::cin >> data;
        tree.add(data);
    }
    
    Traverse(tree.root);
    
    return 0;
}
