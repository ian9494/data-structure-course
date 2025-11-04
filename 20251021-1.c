#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// 前序遍歷（preorder）：根、左、右
void preorder_print(struct Node* node) {
    if (node == NULL) return;
    printf("%d ", node->data);
    preorder_print(node->left);
    preorder_print(node->right);
}

// 檢查是否為完整二元樹
// 對於一維陣列表示的樹，從 index=1..size
// 找到第一個為 0 的位置 pos，若之後還有非 0 節點 => 非完整
int is_complete(struct Node* root) {
    if (root == NULL) return 1;
    struct Node* queue[1024];
    int head = 0, tail = 0;
    queue[tail++] = root;
    int found_null = 0;
    while (head < tail) {
        struct Node* n = queue[head++];
        if (n == NULL) {
            found_null = 1;
        } else {
            if (found_null) return 0; // found non-null after null
            queue[tail++] = n->left;
            queue[tail++] = n->right;
        }
    }
    return 1;
}

int main() {
    // 範例資料：對應題目圖示（index 從 1 開始，index 7,8,9 為空）
    // 1:99 2:55 3:66 4:11 5:33 6:44 7:0 8:0 9:0 10:22 11:77 12:88
    int n = 12;
    int *arr = (int*)calloc(n+1, sizeof(int));
    arr[1]=99; arr[2]=55; arr[3]=66; arr[4]=11; arr[5]=33; arr[6]=44;
    arr[7]=0; arr[8]=0; arr[9]=0; arr[10]=22; arr[11]=77; arr[12]=88;

    // 轉換為二元樹結構
    struct Node** nodes = (struct Node**)calloc(n+1, sizeof(struct Node*));
    for (int i = 1; i <= n; i++) {
        if (arr[i] != 0) {
            nodes[i] = (struct Node*)malloc(sizeof(struct Node));
            nodes[i]->data = arr[i];
            nodes[i]->left = NULL;
            nodes[i]->right = NULL;
        }
    }

    // 根據陣列索引建立 left/right 連結
    for (int i = 1; i <= n; i++) {
        if (nodes[i] == NULL) continue;
        int li = i * 2;
        int ri = i * 2 + 1;
        nodes[i]->left = (li <= n) ? nodes[li] : NULL;
        nodes[i]->right = (ri <= n) ? nodes[ri] : NULL;
    }

    printf("Binary tree (preorder): ");
    preorder_print(nodes[1]);
    printf("\n\n");

    if (is_complete(nodes[1])) printf("The binary tree is complete.\n");
    else printf("The binary tree is NOT complete.\n");
    // 釋放節點記憶體
    for (int i = 1; i <= n; i++) {
        if (nodes[i]) free(nodes[i]);
    }
    free(nodes);
    free(arr);
    return 0;
}
