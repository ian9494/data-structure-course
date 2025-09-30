#include <stdio.h>  

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// 用遞迴方式印出中序走訪結果
void Display(struct Node* root) {
    if (root == NULL) return;
    Display(root->left);
    printf("%d ", root->data);
    Display(root->right);
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int main() {
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    printf("In-order Traversal: ");
    Display(root);
    printf("\n");

    return 0;
}
