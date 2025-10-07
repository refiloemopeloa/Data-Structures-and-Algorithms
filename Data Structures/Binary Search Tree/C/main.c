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

int main() {

    return 0;
}