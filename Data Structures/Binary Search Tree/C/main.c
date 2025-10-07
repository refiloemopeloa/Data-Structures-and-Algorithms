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

int main() {
    return 0;
}