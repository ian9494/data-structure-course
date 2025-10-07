#include <stdio.h>

// 單向鏈結構
struct Node {
    int data;
    struct Node* next;
};

void deleteRepeated(struct Node* head){
    struct Node* current = head;
    struct Node* prev = NULL;
    int found;
    while (current != NULL) {
        prev = current;
        struct Node* runner = current->next;
        found = 0;
        while (runner != NULL) {
            if (runner->data == current->data) {
                // 找到重複節點，移除它
                prev->next = runner->next;
                free(runner);
                runner = prev->next;
                found = 1;
            } else {
                prev = runner;
                runner = runner->next;
            }
        }
        current = current->next;
    }
}


int main() {
    // 建立初始資料 10 20 10 30 20 40 10
    int arr[] = {10, 20, 10, 30, 20, 40, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    struct Node* head = NULL;
    struct Node* tail = NULL;
    struct Node* current = NULL;
    struct Node* prev = NULL;
    int i;
    int found;
    // 建立鏈結串列
    for (i = 0; i < n; i++) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = arr[i];
        newNode->next = NULL;
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // 印出原始鏈結串列
    printf("Original List: ");
    current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");

    // 移除重複的節點
    deleteRepeated(head);

    // 印出移除重複後的鏈結串列
    printf("List after removing duplicates: ");
    current = head;
    while (current  -> next != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}