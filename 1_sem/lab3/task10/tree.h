#ifndef TREE_H
#define TREE_H

#include "util_task10.h"
#define CHILDREN_AMOUNT 8

typedef struct Node Node;

struct Node {
    char data;
    int childCount;
    int childCapacity;
    Node** children;
};

Node* CreateNode(char);
Error MakeTree(char**, Node**);
void PrintTree(Node*, int, FILE*);

void FreeTree(Node*);

#endif