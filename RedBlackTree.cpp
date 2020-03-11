#include<iostream>
using namespace std;
class Node {
    public:
    Node(int item)
    {
        this->item = item;
    }
    enum class colour { red, black };
    int item = NULL;
    Node* left = NULL;
    Node* right = NULL;
    Node* parent = NULL;
    colour c = Node::colour::black;
    
};
class Tree {
    
public:
    Node* root;
    Node* insertNode(Node* x, Node* t)
    {
        if (t == NULL)
        {

            t = x;
        }
        else if (x->item < t->item)
        {
            x->parent = t;
            t->left = insertNode(x, t->left);
            
        }
            

        else if (x->item > t->item)
        {
            x->parent = t;
            t->right = insertNode(x, t->right);
            
        }

        return t;
    }

    void inorder(Node* t) {
        if (t == NULL)
            return;
        inorder(t->left);
        string colorOfNode = "";
        if (t->c == Node::colour::black)
        {
            colorOfNode = "Black";
        }
        else
        {
            colorOfNode = "Red";
        }
        int leftItem = 0;
        int rightItem = 0;
        if (t->left != nullptr)
            leftItem = t->left->item;
        else
            leftItem = -1;
        if (t->right != nullptr)
            rightItem = t->right->item;
        else
            rightItem = -1;
        cout << t->item << "(" << colorOfNode <<")" << "L("<< leftItem <<")"<<"R("<< rightItem <<")" << endl;
        inorder(t->right);
    }
    void postOrder(Node* t) {
        if (t == NULL)
            return;
        string colorOfNode = "";
        if (t->c == Node::colour::black)
        {
            colorOfNode = "Black";
        }
        else
        {
            colorOfNode = "Red";
        }
        int leftItem = 0;
        int rightItem = 0;
        if (t->left != nullptr)
            leftItem = t->left->item;
        else
            leftItem = -1;
        if (t->right != nullptr)
            rightItem = t->right->item;
        else
            rightItem = -1;
        cout << t->item << "(" << colorOfNode << ")" << "L(" << leftItem << ")" << "R(" << rightItem << ")" << endl;
        postOrder(t->left);
        postOrder(t->right);
    }



    Tree() {
        root = NULL;
    }
    void insert(Node* x) {
        root = insertNode(x, root);
    }

    void displayInorder() {
        inorder(root);
        cout << endl;
        cout << "----------------" << endl;
    }
    void displayPostOrder() {
        postOrder(root);
        cout << endl;
        cout << "----------------" << endl;
    }

};
/* a red-black tree's node structure. you may write a class instead of a struct */

void left_rotate(Tree* T, Node* x) {
    cout << "Left rotation triggered!" << endl;
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
void right_rotate(Tree* T, Node* x) {
    cout << "Right rotation triggered!" << endl;
    Node* y;
    y = x->left;
    /* Turn y's left sub-tree into x's right sub-tree */
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;
    /* y's new parent was x's parent */
    y->parent = x->parent;
    /* Set the parent to point to y instead of x */
    /* First see whether we're at the root */
    if (x->parent == NULL) T->root = y;
    else
        if (x == (x->parent)->right)
            /* x was on the left of its parent */
            x->parent->right = y;
        else
            /* x must have been on the right */
            x->parent->left = y;
    /* Finally, put x on y's left */
    y->right = x;
    x->parent = y;
}
void rb_insert(Tree* T, Node* x) {
    /* Insert in the tree in the usual way */
    T->insert(x);
    /* Now restore the red-black property */
    x->c = Node::colour::red;
    while ((x != T->root) && (x->parent->c == Node::colour::red)) {
        if (x->parent == x->parent->parent->left) {
            /* If x's parent is a left, y is x's right 'uncle' */
            Node* y = x->parent->parent->right;
            if (y != nullptr && y->c == Node::colour::red) {
                /* case 1 - change the colours */
                x->parent->c = Node::colour::black;
                y->c = Node::colour::black;
                x->parent->parent->c = Node::colour::red;
                /* Move x up the tree */
                x = x->parent->parent;
            }
            else {
                /* y is a black node */
                if (x == x->parent->right) {
                    /* and x is to the right */
                    /* case 2 - move x up and rotate */
                    x = x->parent;
                    left_rotate(T, x);
                }
                /* case 3 */
                x->parent->c = Node::colour::black;
                x->parent->parent->c = Node::colour::red;
                right_rotate(T, x->parent->parent);
            }
        }
        else {
            /* If x's parent is a right, y is x's left 'uncle' */
            Node* y = x->parent->parent->left;
            if (y != nullptr && y->c == Node::colour::red) {
                /* case 1 - change the colours */
                x->parent->c = Node::colour::black;
                y->c = Node::colour::black;
                x->parent->parent->c = Node::colour::red;
                /* Move x up the tree */
                x = x->parent->parent;
            }
            else {
                /* y is a black node */
                if (x == x->parent->left) {
                    /* and x is to the left */
                    /* case 2 - move x up and rotate */
                    x = x->parent;
                    right_rotate(T, x);
                }
                /* case 3 */
                x->parent->c = Node::colour::black;
                x->parent->parent->c = Node::colour::red;
                left_rotate(T, x->parent->parent);
            }
        }
    }
    /* Colour the root black */
    T->root->c = Node::colour::black;
}



int main() {
    Tree* t = new Tree;
    cout << "Test Case 0: Insert Root 100" << endl;
    Node* test01 = new Node(100);
    rb_insert(t, test01);
    t->displayInorder();
    
    cout << "Test Case 1: Insert 200,300 and get a left rotation" << endl;
    Node* test11 = new Node(200);
    rb_insert(t, test11);
    Node* test12 = new Node(300);
    rb_insert(t, test12);
    t->displayInorder();
    cout << "Test Case 2: Insert 99,98 and get a right rotation" << endl;
    Node* test21 = new Node(99);
    rb_insert(t, test21);
    Node* test22 = new Node(98);
    rb_insert(t, test22);
    t->displayInorder();
    cout << "Test Case 3: Insert 301,302 and get a right rotation, then a left rotation" << endl;
    Node* test31 = new Node(302);
    rb_insert(t, test31);
    Node* test32 = new Node(301);
    rb_insert(t, test32);
    t->displayInorder();
    cout << "Finally, printing out the tree in inorder, and post order:" << endl;
    cout << endl << "--------In Order--------" << endl;
    t->displayInorder();
    cout << "--------Post Order--------" << endl;
    t->displayPostOrder();
    return 0;
}