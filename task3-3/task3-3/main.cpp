//
//  main.cpp
//  task3-3
//
//  Created by Alexander Rogovsky on 20.05.15.
//  Copyright (c) 2015 Alexander Rogovsky. All rights reserved.
//

#include <iostream>
#include <queue>

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
class TreapNode{
public:
    T key;
    T priority;
    TreapNode* left;
    TreapNode* right;
    
    TreapNode(int key, int priority) : key(key), priority(priority), left(NULL), right(NULL) { }
};

template <class T>
class Treap {
public:
    TreapNode<T> *root;
    
    Treap(): root(NULL) { }
};

template <class T>
TreapNode<T>* merge(TreapNode<T> *left, TreapNode<T> *right) {
    if (left == NULL || right == NULL) {
        return (left == NULL) ? right : left;
    }
    
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

template <class T>
void split(TreapNode<T> *currentNode, T key, TreapNode<T> *&left, TreapNode<T> *&right) {
    if (currentNode == NULL) {
        left = NULL;
        right = NULL;
    } else if (currentNode->key <= key) {
        split(currentNode->right, key, currentNode->right, right);
        left = currentNode;
    } else {
        split(currentNode->left, key, left, currentNode->left);
        right = currentNode;
    }
}

template <class T>
void add(TreapNode<T> *&root, int key, int priority) {
    TreapNode<T> *node = new TreapNode<T>(key, priority);
    TreapNode<T> *splitLeft = NULL;
    TreapNode<T> *splitRight = NULL;
    split(root, key, splitLeft, splitRight);
    root = merge(merge(splitLeft, node), splitRight);
}


template <class T>
int Tree_getMaxWidth(BSTree<T> tree) {
    std::queue<TNode<T>*> Q;
    
    if(tree.root == NULL)
        return 0;
    
    int max = 1;
    int layer = 0;
    Q.push(tree.root);
    Q.push(NULL);
    
    while(!Q.empty()) {
        if(Q.front() != NULL) {
            TNode<T>* child = Q.front();
            
            if(child->left != NULL) {
                Q.push(child->left);
                ++layer;
            }
            
            if(child->right != NULL) {
                Q.push(child->right);
                ++layer;
            }
            
            Q.pop();
            
        }

        else {
            if(layer > max)
                max = layer;
            if(layer!=0)
                Q.push(NULL);
            layer = 0;
            Q.pop();
        }
        
        
    }
    
    return max;
    
}


template <class T>
int Treap_getMaxWidth(Treap<T> tree) {
    std::queue<TreapNode<T>*> Q;
    
    if(tree.root == NULL)
        return 0;
    
    int max = 1;
    int layer = 0;
    Q.push(tree.root);
    Q.push(NULL);
    
    while(!Q.empty()) {
        if(Q.front() != NULL) {
            TreapNode<T>* child = Q.front();
            
            if(child->left != NULL) {
                Q.push(child->left);
                ++layer;
            }
            
            if(child->right != NULL) {
                Q.push(child->right);
                ++layer;
            }
            
            Q.pop();
            
        }
        
        else {
            if(layer > max)
                max = layer;
            if(layer!=0)
                Q.push(NULL);
            layer = 0;
            Q.pop();
            
        }
        
        
    }
    
    return max;
    
}


int main() {
    
    size_t n;
        
    std::cin >> n;
        
    BSTree<int> tree;
    Treap<int> treap;
        
    for (size_t i = 0; i < n; ++i) {
        int key, priority;
        
        std::cin >> key >> priority;
        
        tree.add(key);
        add(treap.root, key, priority);
    }
    
    int a = Tree_getMaxWidth(tree);
    int b = Treap_getMaxWidth(treap);
    
    std::cout<< b - a;
    
    return 0;
}












