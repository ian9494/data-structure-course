#include <stdio.h>
#include <stdlib.h>

// B-Tree Order = 3 (max children = 3, max keys = 2)
#define MAX_KEYS 2
#define MAX_CHILDREN (MAX_KEYS + 1)

typedef struct BTreeNode {
    int keys[MAX_KEYS + 1]; // allow one extra temporarily during inserts
    struct BTreeNode *children[MAX_CHILDREN + 1]; // allow one extra
    int num_keys;
    int is_leaf;
} BTreeNode;

BTreeNode *create_node(int is_leaf) {
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->is_leaf = is_leaf;
    node->num_keys = 0;
    for (int i = 0; i <= MAX_CHILDREN; i++) node->children[i] = NULL;
    return node;
}

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

// Split node 'node' which currently has num_keys == MAX_KEYS+1
// After split: node keeps left part, *new_node is created for right part
// promoted key value returned via *promoted
void split_node(BTreeNode *node, int *promoted, BTreeNode **new_node) {
    int total = node->num_keys; // should be MAX_KEYS+1
    int mid = total / 2; // middle index to promote

    *new_node = create_node(node->is_leaf);

    // promoted key
    *promoted = node->keys[mid];

    // right node gets keys after mid
    int j = 0;
    for (int i = mid + 1; i < total; i++) {
        (*new_node)->keys[j++] = node->keys[i];
    }
    (*new_node)->num_keys = j;

    // if not leaf, move corresponding children
    if (!node->is_leaf) {
        int k = 0;
        for (int i = mid + 1; i <= total; i++) {
            (*new_node)->children[k++] = node->children[i];
        }
    }

    // left node keeps keys before mid
    node->num_keys = mid;
    // null out moved children in left node
    if (!node->is_leaf) {
        for (int i = node->num_keys + 1; i <= MAX_CHILDREN; i++) node->children[i] = NULL;
    }
}

// 此function將key插入以node為根的子樹中。如果發生分裂，返回1並提供提升的鍵和值的新子指針。
int insert_recursive(BTreeNode *node, int key, int *promoted, BTreeNode **new_child) {
    // 尋找插入位置
    int i = node->num_keys - 1;
    if (node->is_leaf) {
        // 以排序順序（升序）將鍵插入鍵陣列中
        // 移動元素以騰出空間
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = key;
        node->num_keys++;
        if (node->num_keys <= MAX_KEYS) { // 如果num_keys未超過最大值 不需要分裂
            return 0;
        } else {
            // split node
            split_node(node, promoted, new_child);
            return 1;
        }
    } else {
        // non-leaf: find child
        while (i >= 0 && node->keys[i] > key) i--;
        int child_idx = i + 1;
        int child_promoted;
        BTreeNode *child_new = NULL;
        if (insert_recursive(node->children[child_idx], key, &child_promoted, &child_new)) {
            // need to insert child_promoted into this node at position child_idx
            // shift keys and children to make room
            for (int j = node->num_keys - 1; j >= child_idx; j--) node->keys[j+1] = node->keys[j];
            for (int j = node->num_keys; j >= child_idx + 1; j--) node->children[j+1] = node->children[j];
            node->keys[child_idx] = child_promoted;
            node->children[child_idx + 1] = child_new;
            node->num_keys++;
            if (node->num_keys <= MAX_KEYS) return 0;
            else {
                split_node(node, promoted, new_child);
                return 1;
            }
        } else {
            return 0;
        }
    }
}

void btree_insert(BTreeNode **root_ptr, int key) {
    BTreeNode *root = *root_ptr;
    int promoted;
    BTreeNode *new_child = NULL;
    if (insert_recursive(root, key, &promoted, &new_child)) {
        // 如果根節點分裂，建立新根節點
        BTreeNode *new_root = create_node(0);
        new_root->keys[0] = promoted;
        new_root->children[0] = root;
        new_root->children[1] = new_child;
        new_root->num_keys = 1;
        *root_ptr = new_root;
    }
}

int main() {
    BTreeNode *root = create_node(1); // start as leaf
    int keys[] = {10,20,30,40,50,60,70,80,90,100};
    int n = sizeof(keys)/sizeof(keys[0]);
    for (int i = 0; i < n; i++) {
        btree_insert(&root, keys[i]);
    }

    printf("B-Tree structure:\n");
    print_tree(root, 0);

    return 0;
}
