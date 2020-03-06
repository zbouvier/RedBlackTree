class BST {

    struct node {
        int value;
        node* l;
        node* r;
    };

    node* root;

    node* insertNode(int x, node* t)
    {
        if (t == NULL)
        {
            t = new node;
            t->value = x;
            t->l = t->r = NULL;
        }
        else if (x < t->value)
            t->l = insert(x, t->l);
        else if (x > t->value)
            t->r = insert(x, t->r);
        return t;
    }

    node* find(node* t, int x) {
        if (t == NULL)
            return NULL;
        else if (x < t->value)
            return find(t->l, x);
        else if (x > t->value)
            return find(t->r, x);
        else
            return t;
    }

public:
    BST() {
        root = NULL;
    }


    void insert(int x) {
        root = insertNode(x, root);
    }

    void search(int x) {
        root = find(root, x);
    }
};
