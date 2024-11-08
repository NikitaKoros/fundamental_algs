#include "tree.h"

Node* CreateNode(char data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        return NULL;
    }
    node->data = data;
    node->childCount = 0;
    node->childCapacity = CHILDREN_AMOUNT;
    node->children = (Node**)malloc(CHILDREN_AMOUNT * sizeof(Node*));
    if (!node->children) {
        free(node);
        return NULL;
    }
    return node;
}

Error ExpandChildrenArray(Node* node) {
    int newCapacity = node->childCapacity * 2;
    Node** newChildren = (Node**)realloc(node->children, newCapacity * sizeof(Node*));
    if (!newChildren) {
        return MEMORY_ALLOCATION_ERROR;
    }
    node->children = newChildren;
    node->childCapacity = newCapacity;
    return OK;
}

Error MakeTree(char** line_ptr, Node** root) {
    char* line = *line_ptr;

    while (*line == '(' || *line == ' ') {
        line++;
    }

    if (*line == '\0') {
        *root = NULL;
        return OK;
    }

    if (*line == ')') {
        line++;
        *line_ptr = line;
        *root = NULL;
        return OK;
    }

    Node* node = CreateNode(*line);
    if (node == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    do {
        line++;
    } while (*line == ' ');
    

    if (*line == '(') {
        line++;
        while (*line != ')' && *line != '\0') {
            if (*line == ',' || *line == ' ') {
                line++;
            }

            Node *child;
            Error err;

            err = MakeTree(&line, &child);
            if (err != OK) {
                for (int i = 0; i < node->childCount; i++) {
                    FreeTree(node->children[i]);
                }
                free(node->children);
                free(node);
                return err;
            }
            
            if (child == NULL) {
                continue;
            }

            if (node->childCount >= node->childCapacity) {
                err = ExpandChildrenArray(node);
                if (err != OK) {
                        for (int i = 0; i < node->childCount; i++) {
                        FreeTree(node->children[i]);
                    }
                    free(node->children);
                    free(node);
                }
            }

            node->children[node->childCount] = child;
            node->childCount++;
        }

        while (*line == ')') {
            line++;
        }
    }
    
    *root = node;
    *line_ptr = line;
    return OK;
}


void PrintTree(Node* root, int level, FILE* fileOutput) {
    if (root == NULL) {
        return;
    }
    
    for (int i = 0; i < level; i++) {
        fprintf(fileOutput, "\t");
    }
    fprintf(fileOutput, "%c\n", root->data);

    for (int i = 0; i < root->childCount; i++) {
        PrintTree(root->children[i], level + 1, fileOutput);
    }
}

void FreeTree(Node* root) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < root->childCount; i++) {
        FreeTree(root->children[i]);
    }

    free(root->children);
    free(root);
}