#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <cassert>

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree {
private:
    Node *root;

    void rotateLeft(Node *&);
    void rotateRight(Node *&);
    void fixInsertion(Node *&);
    void fixDeletion(Node *&);
    void transplant(Node *, Node *);
    Node* minimum(Node *) const;
    Node* maximum(Node *) const;
    int height(Node *) const;
    bool validateProperties(Node *) const;
    void inorderTraversal(Node *) const;

public:
    RBTree();
    void insert(int);
    void remove(int);
    Node* search(int) const;
    void inorder() const;
    bool validate() const;
    int findMin() const;
    int findMax() const;
    int getHeight() const;
};

#endif
