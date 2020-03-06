// RedBlackTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>

using namespace std;
/* Your generic Binary Search Tree */
class Node {
public:
    int data;
    Node* left, * right, * parent;
    struct t_red_black_Node {
        enum { red, black } colour;
        void* item;
        struct t_red_black_Node* left, * right, * parent;
    }
};
class Tree {

    public:
        Node* root;

        Node* insertNode(int x, Node* t)
        {
            if (x == NULL) return getNode(x);
            if (x < t->data) { //to the left subtree
                Node* leftChild = insertNode(x,t->left);
                t->left = leftChild;
                leftChild->parent = t;
            }
            else if (x > t->data) { // to the right subtree
                Node* rightChild = insertNode(x,t->right);
                t->right = rightChild;
                rightChild->parent = t;
            }
            return t;
        }

        Node* getNode(int item) {
            Node* temp = new Node;
            temp->data = item;
            temp->left = temp->right = temp->parent = NULL;
            return temp;
        }

};
/* End of Binary Search Tree */

/* a red-black tree's Node structure. you may write a class instead of a struct */


leftRotate(Tree* T, Node* x) {
    Node* y;
    y = x->right;
    /* Turn y's left sub-tree into x's right sub-tree */
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    /* y's new parent was x's parent */
    y->parent = x->parent;
    /* Set the parent to point to y instead of x */
    /* First see whether we're at the root */
    if (x->parent == NULL) T->root = y;
    else
        if (x == (x->parent)->left)
            /* x was on the left of its parent */
            x->parent->left = y;
        else
            /* x must have been on the right */
            x->parent->right = y;
    /* Finally, put x on y's left */
    y->left = x;
    x->parent = y;
}

void rbInsert(Tree* T, Node* x) {
    /* Insert in the tree in the usual way */
    T->insertNode(T, x);
    /* Now restore the red-black property */
    x->colour = red;
    while ((x != T->root) && (x->parent->colour == red)) {
        if (x->parent == x->parent->parent->left) {
            /* If x's parent is a left, y is x's right 'uncle' */
            y = x->parent->parent->right;
            if (y->colour == red) {
                /* case 1 - change the colours */
                x->parent->colour = black;
                y->colour = black;
                x->parent->parent->colour = red;
                /* Move x up the tree */
                x = x->parent->parent;
            }
            else {
                /* y is a black Node */
                if (x == x->parent->right) {
                    /* and x is to the right */
                    /* case 2 - move x up and rotate */
                    x = x->parent;
                    leftRotate(T, x);
                }
                /* case 3 */
                x->parent->colour = black;
                x->parent->parent->colour = red;
                right_rotate(T, x->parent->parent);
            }
        }
        else {
            /* repeat the "if" part with right and left
             exchanged */
        }
    }
    /* Colour the root black */
    T->root->colour = black;
}

int main() {
    return 0;
}