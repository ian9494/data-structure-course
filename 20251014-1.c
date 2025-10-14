#include <stdio.h>
#include <stdlib.h>

// 多項式節點
typedef struct PolyNode {
    int coef;
    int exp;
    struct PolyNode* next;
} PolyNode;

// 佇列結構
typedef struct {
    PolyNode* front;
    PolyNode* rear;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

void enqueue(Queue* q, int coef, int exp) {
    if (coef == 0) return;
    PolyNode* node = (PolyNode*)malloc(sizeof(PolyNode));
    node->coef = coef;
    node->exp = exp;
    node->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = node;
    } else {
        q->rear->next = node;
        q->rear = node;
    }
}

PolyNode* dequeue(Queue* q) {
    if (q->front == NULL) return NULL;
    PolyNode* node = q->front;
    q->front = node->next;
    if (q->front == NULL) q->rear = NULL;
    node->next = NULL;
    return node;
}

// 只用兩個 queue，且只能 dequeue/front 取出、enqueue 尾端加入來排序
void sortQueue(Queue* q) {
    Queue temp;
    initQueue(&temp);
    int n = 0;
    for (PolyNode* p = q->front; p; p = p->next) n++;
    for (int i = 0; i < n; i++) {
        // 找最大次方的節點
        PolyNode* maxNode = NULL;
        PolyNode* prevMax = NULL;
        PolyNode* prev = NULL;
        int maxExp = -1;
        int m = n - i;
        // 先找最大次方
        for (int j = 0; j < m; j++) {
            PolyNode* node = dequeue(q);
            if (!maxNode || node->exp > maxExp) {
                maxNode = node;
                prevMax = prev;
                maxExp = node->exp;
            }
            enqueue(&temp, node->coef, node->exp);
            free(node);
        }
        // 再把最大次方的節點 enqueue 回 q，其餘回 temp 
        int found = 0;
        for (int j = 0; j < m; j++) {
            PolyNode* node = dequeue(&temp);
            if (!found && node->exp == maxExp) {
                enqueue(q, node->coef, node->exp);
                found = 1;
            } else {
                enqueue(&temp, node->coef, node->exp);
            }
            free(node);
        }
    }
    // 合併同次方
    Queue sorted;
    initQueue(&sorted);
    while (q->front) {
        PolyNode* node = dequeue(q);
        if (sorted.rear && sorted.rear->exp == node->exp) {
            sorted.rear->coef += node->coef;
            free(node);
            if (sorted.rear->coef == 0) {
                PolyNode* del = sorted.rear;
                // 找到前一個
                PolyNode* prev = sorted.front;
                if (prev == del) {
                    sorted.front = sorted.rear = NULL;
                } else {
                    while (prev->next != del) prev = prev->next;
                    prev->next = NULL;
                    sorted.rear = prev;
                }
                free(del);
            }
        } else {
            node->next = NULL;
            if (sorted.rear) sorted.rear->next = node;
            else sorted.front = node;
            sorted.rear = node;
        }
    }
    q->front = sorted.front;
    q->rear = sorted.rear;
}

// 列印多項式（由高次到低次）
void print_poly_queue(Queue* q) {
    PolyNode* curr = q->front;
    if (curr == NULL) {
        printf("0\n");
        return;
    }
    while (curr) {
        if (curr != q->front && curr->coef > 0) printf(" + ");
        if (curr->exp == 0) {
            printf("%d", curr->coef);
        } else if (curr->exp == 1) {
            if (curr->coef == 1) printf("X");
            else if (curr->coef == -1) printf("-X");
            else printf("%dX", curr->coef);
        } else {
            if (curr->coef == 1) printf("X^%d", curr->exp);
            else if (curr->coef == -1) printf("-X^%d", curr->exp);
            else printf("%dX^%d", curr->coef, curr->exp);
        }
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    Queue poly1, poly2;
    initQueue(&poly1);
    initQueue(&poly2);
    printf("enter first poly (use 0 0 to end)>\n");
    int coef, exp;
    while (1) {
        scanf("%d %d", &coef, &exp);
        if (coef == 0 && exp == 0) break;
        enqueue(&poly1, coef, exp);
    }
    printf("first poly is: ");
    print_poly_queue(&poly1);

    printf("enter second poly (use 0 0 to end)>\n");
    while (1) {
        scanf("%d %d", &coef, &exp);
        if (coef == 0 && exp == 0) break;
        enqueue(&poly2, coef, exp);
    }
    printf("second poly is: ");
    print_poly_queue(&poly2);

    // 多項式加法
    Queue result;
    initQueue(&result);
    PolyNode* p1 = poly1.front;
    PolyNode* p2 = poly2.front;
    while (p1 && p2) {
        if (p1->exp > p2->exp) {
            enqueue(&result, p1->coef, p1->exp);
            p1 = p1->next;
        } else if (p1->exp < p2->exp) {
            enqueue(&result, p2->coef, p2->exp);
            p2 = p2->next;
        } else {
            int sum_coef = p1->coef + p2->coef;
            if (sum_coef != 0) {
                enqueue(&result, sum_coef, p1->exp);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    printf("result poly is: ");
    print_poly_queue(&result);

    freeQueue(&poly1);
    freeQueue(&poly2);
    freeQueue(&result);
    return 0;
}

/*
7 5
4 4
3 3
2 2
1 1
9 0
0 0

6 4
9 3
4 2
9 0
0 0
*/