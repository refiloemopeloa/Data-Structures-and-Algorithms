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


int main() {
    return 0;
}