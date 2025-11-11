#include <stdio.h>
#include <stdlib.h>

#define MAX_KEYS 2  //B-Tree階度m=3，每個節點最多有的鍵值數(m-1)
#define MIN_KEYS (MAX_KEYS / 2)  //每個節點最少的鍵值數
#define MAX_CHILDREN (MAX_KEYS + 1)  //子節點數為鍵值數+1(m)

//Def B-Tree
typedef struct BTreeNode {
    int keys[MAX_KEYS];                        //存放鍵值
    struct BTreeNode *children[MAX_KEYS + 1];  //子節點指標(m)
    //struct BTreeNode *parent; 
    int num_keys;                              //當前鍵值數
    int is_leaf;                               //是否為葉節點
} BTreeNode;

//Create B-Tree node
BTreeNode *create_node(int is_leaf) {
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->is_leaf = is_leaf;
    node->num_keys = 0;
    for (int i = 0; i <= MAX_KEYS; i++) {
        node->children[i] = NULL;
    }
    return node;
}

//Print B-Tree
void print_tree(BTreeNode *node, int level) {
    if (node != NULL) {
        printf("Level %d: ", level);
        for (int i = 0; i < node->num_keys; i++) {
            printf("%d ", node->keys[i]);
        }
        printf("\n");

        if (!node->is_leaf) {
            for (int i = 0; i <= node->num_keys; i++) {
                print_tree(node->children[i], level + 1);
            }
        }
    }
}

int main() {
    BTreeNode *root = create_node(0);  
    BTreeNode *node1 = create_node(1);
    BTreeNode *node2 = create_node(1);
    
    node1->keys[0] = 10;
    node1->num_keys = 1;

    node2->keys[0] = 30;
    node2->keys[1] = 40;
    node2->num_keys = 2;

    root->keys[0] = 20;
    root->num_keys = 1;
    root->children[0] = node1;
    root->children[1] = node2;
    
    printf("B-Tree structure:\n");
    print_tree(root, 0);

    return 0;
}
