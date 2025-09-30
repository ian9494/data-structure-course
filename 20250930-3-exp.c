#include <stdio.h>
#include <stdlib.h> 

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct Stack {
    Node* data[100];
    int top;
} Stack;

void init(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, Node* node) {
    s->data[++(s->top)] = node;
}

Node* pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return NULL;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void Display(Node* root) {
    Stack stack;
    init(&stack);
    Node* current = root;

    while (current != NULL || !isEmpty(&stack)) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }
        current = pop(&stack);
        printf("%d ", current->data);
        current = current->right;
    }
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

    // Free memory (not shown here for brevity)

    return 0;
}