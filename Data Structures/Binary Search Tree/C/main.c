#include "stdio.h"
#include "stdlib.h"

typedef struct Node
{
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    int key;
    char visited;
} Node;

#define nullptr ((void *)0);

typedef struct
{
    Node *root;
} BST;

void new_Node(Node *this, Node *left, Node *right, Node *parent, int *key)
{
    this->left = left;
    this->right = right;
    this->parent = parent;
    this->key = key;
    this->visited = 0;
}

void new_BST(BST *this, int *array, int *size)
{
    ;
}
void copy_Node(Node *this, Node *other)
{
    this->left = other->left;
    this->right = other->right;
    this->parent = other->parent;
    this->key = other->key;
}

Node *get_Node(BST *this, int key)
{
    Node *ptr = this->root;

    while (1)
    {
        if (ptr == NULL)
            return NULL;
        if (ptr->key == key)
            return ptr;
        if (ptr->key > key)
        {
            ptr = ptr->left;
            continue;
        }
        ptr = ptr->right;
    }
}

Node *min_Node(Node *this)
{
    Node *ptr = this;

    if (ptr == NULL)
        return NULL;
    while (ptr->left != NULL)
    {
        ptr = ptr->left;
    }

    return ptr;
}

void tree_insert(BST *this, Node *new)
{
    Node *ptr = this->root;
    if (ptr == NULL)
    {
        this->root = (Node *)malloc(sizeof(Node));
        copy_Node(this->root, new);
        return;
    }
    while (1)
    {
        if (ptr->key > new->key)
        {
            if (ptr->left == NULL)
            {
                new->parent = ptr;
                ptr->left = new;
                return;
            }
            ptr = ptr->left;
        }
        else
        {
            if (ptr->right == NULL)
            {
                new->parent = ptr;
                ptr->right = new;
                return;
            }
            ptr = ptr->right;
        }
    }
}

void transplant(BST* this, Node* u, Node* v) {
    if (u->parent == NULL) {
        this->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}

void tree_delete(BST *this, Node* z)
{
    if (z->left == NULL) {
        transplant(this, z, z->right);
    } else if (z->right == NULL) {
        transplant(this, z, z->left);
    } else {
        Node* y = min_Node(z->right);
        if (y != z->right) {
            transplant(this, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(this, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}

void inorder_tree_walk(Node *this)
{
    Node *ptr = this;
    while (1)
    {
        if (ptr == NULL)
        {
            printf("\n");
            return;
        }
        if (ptr->visited == 1)
        {
            ptr = ptr->parent;
            continue;
        }
        if (ptr->left != NULL && ptr->left->visited == 0)
        {
            ptr = ptr->left;
            continue;
        }
        printf("%d ", ptr->key);
        ptr->visited = 1;
        if (ptr->right != NULL && ptr->right->visited == 0)
        {
            ptr = ptr->right;
            continue;
        }
    }
}

void reset_visited(Node *this) {
    if (this != NULL) {
        reset_visited(this->left);
        this->visited = 0;
        reset_visited(this->right);
    }
}


int main() {
    return 0;
}