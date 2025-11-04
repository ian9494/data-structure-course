#include <stdio.h>
#include <stdlib.h>

//Huffman tree node 
struct Node {
    char data;
    int freq;
    struct Node *left, *right;
};

//create new node
struct Node* createNode(char data, int freq) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->freq = freq;
    temp->left = temp->right = NULL;
    return temp;
}

//build Huffman tree
struct Node* buildHuffmanTree(char data[], int freq[], int size) {
    struct Node* left, * right, * top;
    while (size > 1) {
        left = createNode(data[0], freq[0]);
        right = createNode(data[1], freq[1]);
        top = createNode('*', freq[0] + freq[1]);
        top->left = left;
        top->right = right;
        size--;
    }
    return top;
}

//Display Huffman tree 
void printTree(struct Node* root, int level) {
    if (root == NULL)
        return;

    printTree(root->right, level + 1);

    for (int i = 0; i < level; i++)
        printf("\t");
    printf("(%c, %d)\n", root->data, root->freq);

    printTree(root->left, level + 1);
}

int main() {
    char data[] = {'A', 'B', 'C', 'D', 'E', 'F'}; 
    int freq[] = {20, 15, 30, 18, 5, 12}; 
    int size = sizeof(data) / sizeof(data[0]);

    struct Node* root = buildHuffmanTree(data, freq, size);

    printf("\nHuffman tree:\n");
    printTree(root, 0);

    return 0;
}
