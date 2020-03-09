class Tree {

    struct Node {
        int value;
        Node* l;
        Node* r;
    };

    Node* root;

    Node* insertNode(int x, Node* t)
    {
        if (t == NULL)
        {
            t = new Node;
            t->value = x;
            t->l = t->r = NULL;
        }
        else if (x < t->value)
            t->l = insert(x, t->l);
        else if (x > t->value)
            t->r = insert(x, t->r);
        return t;
    }

public:
    Tree() {
        root = nullptr;
    }


    void insert(int x) {
        root = insertNode(x, root);
    }


};
