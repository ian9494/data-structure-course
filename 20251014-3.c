#include <stdio.h>
#include <stdlib.h>

//queue based on linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} LinkListQueue;

void initQueue(LinkListQueue* q) {
    q->front = q->rear = NULL;
}

void enqueue(LinkListQueue* q, int data) {
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

void freeQueue(LinkListQueue* q) {
    Node* curr = q->front;
    while (curr) {
        Node* tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    q->front = q->rear = NULL;
}

void printQueue(LinkListQueue* q) {
    Node* curr = q->front;
    printf("LinkListQueue: [");
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

// queue base on array
#define MAX_QUEUE_SIZE 100

typedef struct {
    int data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} ArrayQueue;

void initArrayQueue(ArrayQueue* q) {
    q->front = 0;
    q->rear = 0;
}

int enqueueArray(ArrayQueue* q, int value) {
    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    return 1;
}

void printArrayQueue(ArrayQueue* q) {
    printf("ArrayQueue: [");
    int i = q->front;
    while (i != q->rear) {
        printf("%d", q->data[i]);
        i = (i + 1) % MAX_QUEUE_SIZE;
        if (i != q->rear) printf(", ");
    }
    printf("]\n");
}

// dequeue 並回傳值（linked list queue）
int dequeueAndGet(LinkListQueue* q, int* val) {
    if (q->front == NULL) return 0;
    Node* node = q->front;
    *val = node->data;
    q->front = node->next;
    if (q->front == NULL) q->rear = NULL;
    free(node);
    return 1;
}
// dequeue 並回傳值（array queue）
int dequeueAndGetArray(ArrayQueue* q, int* val) {
    if (q->front == q->rear) return 0;
    *val = q->data[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return 1;
}

void findIntersection(LinkListQueue* q1, ArrayQueue* q2) {
    LinkListQueue temp1;
    ArrayQueue temp2;
    initQueue(&temp1);
    initArrayQueue(&temp2);
    int found = 0;
    printf("Intersection: [");
    int val1;
    while (dequeueAndGet(q1, &val1)) {
        int match = 0;
        int val2;
        // 檢查 q2 是否有 val1
        int size2 = 0;
        while (dequeueAndGetArray(q2, &val2)) {
            if (val2 == val1) match = 1;
            enqueueArray(&temp2, val2);
            size2++;
        }
        // 把 temp2 的內容搬回 q2
        for (int i = 0; i < size2; i++) {
            dequeueAndGetArray(&temp2, &val2);
            enqueueArray(q2, val2);
        }
        if (match) {
            if (found) printf(", ");
            printf("%d", val1);
            found = 1;
        }
        enqueue(&temp1, val1);
    }
    if (!found) printf("No intersection");
    printf("]\n");
    // 把 temp1 的內容搬回 q1
    int tval;
    while (dequeueAndGet(&temp1, &tval)) {
        enqueue(q1, tval);
    }
}

int main() {
    printf("---initialize queue---\n");
    int init_array_queue[4] = {1, 2, 3, 5};
    int init_linklist_queue[4] = {2, 4, 5, 6};

    LinkListQueue q2;
    initQueue(&q2);
    for (int i = 0; i < 4; i++) {
        enqueue(&q2, init_linklist_queue[i]);
    }

    ArrayQueue q1;
    initArrayQueue(&q1);
    for (int i = 0; i < 4; i++) {
        enqueueArray(&q1, init_array_queue[i]);
    }

    printArrayQueue(&q1);
    printQueue(&q2);

    printf("\n\n---find intersection---\n");
    findIntersection(&q2, &q1);

    printf("\n\n");
    printArrayQueue(&q1);
    printQueue(&q2);

    freeQueue(&q2);
    return 0;
}