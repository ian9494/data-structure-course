#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

void enqueue(Queue* q, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = node;
    } else {
        q->rear->next = node;
        q->rear = node;
    }
}

// dequeue 並回傳值
int dequeueAndGet(Queue* q, int* val) {
    if (q->front == NULL) return 0;
    Node* node = q->front;
    *val = node->data;
    q->front = node->next;
    if (q->front == NULL) q->rear = NULL;
    free(node);
    return 1;
}

int removeDuplicatesQueue(Queue* q) {
    Queue temp, check;
    initQueue(&temp);
    int removedCount = 0;
    int val;
    while (dequeueAndGet(q, &val)) {
        // 檢查 temp 是否已存在 val（只能用 dequeue/enqueue）
        int found = 0;
        initQueue(&check);
        int tval;
        while (dequeueAndGet(&temp, &tval)) {
            if (tval == val) found = 1;
            enqueue(&check, tval);
        }
        // 把 check 的內容搬回 temp
        while (dequeueAndGet(&check, &tval)) {
            enqueue(&temp, tval);
        }
        if (!found) {
            enqueue(&temp, val);
        } else {
            removedCount++;
        }
    }
    // 把 temp 的內容搬回原 queue
    int tval;
    while (dequeueAndGet(&temp, &tval)) {
        enqueue(q, tval);
    }
    return removedCount;
}

void freeQueue(Queue* q) {
    Node* curr = q->front;
    while (curr) {
        Node* tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    q->front = q->rear = NULL;
}

void printQueue(Queue* q) {
    Node* curr = q->front;
    printf("Queue: [");
    while (curr) {
        if (curr == q->rear) {
            printf("%d", curr->data);
        } else {
            printf("%d, ", curr->data);
        }
        curr = curr->next;
    }
    printf("]\n");
}

int main() {
    printf("---initialize queue---\n");
    int init_data[7] = {1, 2, 3, 5, 5, 6, 1};

    Queue q;
    initQueue(&q);
    for (int i = 0; i < 7; i++) {
        enqueue(&q, init_data[i]);
    }

    printQueue(&q);
    printf("initial size: %d\n\n\n", 7);

    printf("---After remove duplicates---\n");
    int removedCount = removeDuplicatesQueue(&q);
    printQueue(&q);
    printf("size after remove duplicates: %d\n", 7 - removedCount);

    freeQueue(&q);
    return 0;
}