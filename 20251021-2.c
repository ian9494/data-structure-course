#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

void preorder(struct Node* node) {
    if (node == NULL) return;
    preorder(node->left);
    printf("%d ", node->data);
    preorder(node->right);
}

int main() {
    int n;
    struct Node* root = NULL;

    printf("Enter integers to insert (end with 0):");
    if (scanf("%d", &n) != 1) return 0;
    if (n == 0) return 0;

    root = malloc(sizeof(struct Node));
    if (root == NULL) return 1;
    root->data = n;
    root->left = NULL;
    root->right = NULL;

    while (1) {
        printf("Enter integers to insert (end with 0):");
        scanf("%d", &n);
        if (n == 0) break;

        struct Node* newNode = malloc(sizeof(struct Node));
        if (newNode == NULL) return 1;
        newNode->data = n;
        newNode->left = NULL;
        newNode->right = NULL;

        // Insert the new node into the BST
        struct Node* current = root;
        struct Node* parent = NULL;
        while (current != NULL) {
            parent = current;
            if (n < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        if (n == parent->data) {
            // Duplicate value, do not insert
            free(newNode);
            continue;
        } else if (n < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }

    preorder(root);
    printf("\n");
    return 0;
}