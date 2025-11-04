#include <stdio.h>

struct struct1 {
    struct struct1 *prev; 
    int coef; // 項的係數
    int exp;  // 項的指數
    struct struct1 *next;
};

// 建立多項式節點
struct struct1* createNode(int coef, int exp) {
    struct struct1* node = (struct struct1*)malloc(sizeof(struct struct1));
    node->coef = coef;
    node->exp = exp;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// 插入節點到多項式鏈結串列（按降冪排列）
void insertNode(struct struct1** head, int coef, int exp) {
    struct struct1* newNode = createNode(coef, exp);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct struct1* curr = *head;
    struct struct1* prev = NULL;

    // 找到插入位置 若 現在的節點指數小於等於插入的指數，則插入在前面
    while (curr && curr->exp > exp) {
        prev = curr;
        curr = curr->next;
    }

    // 若指數相同，則係數相加
    if (curr && curr->exp == exp) {
        curr->coef += coef;
        free(newNode);
        return;
    }

    // 插入節點
    if (prev == NULL) {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    // 插入在中間或尾部
    } else {
        newNode->next = curr;
        newNode->prev = prev;
        prev->next = newNode;
        if (curr) curr->prev = newNode;
    }
}

// 多項式加法：C = A + B
struct struct1* addPoly(struct struct1* A, struct struct1* B) {
    struct struct1* C = NULL;
    struct struct1* pa = A;
    struct struct1* pb = B;
    while (pa) {
        insertNode(&C, pa->coef, pa->exp);
        pa = pa->next;
    }
    while (pb) {
        insertNode(&C, pb->coef, pb->exp);
        pb = pb->next;
    }
    return C;
}

// 轉換成環狀（資料結構2）
struct struct1* convertToCircular(struct struct1* head) {
    if (!head) return NULL;

    struct struct1* tail = head;
    while (tail->next) {
        tail = tail->next;
    }
    tail->next = head;
    head->prev = tail;
    return head;
}

// 輸出多項式
void printPoly(struct struct1* head, char name) {
    struct struct1* curr = head;
    printf("%c = ", name);
    while (curr) {
        if (curr->exp > 1)
        printf("%dX^%d", curr->coef, curr->exp);
        else if (curr->exp == 1)
            printf("%dX", curr->coef);
        else if (curr->exp == 0) 
            printf("%d", curr->coef);
        curr = curr->next;
        if (curr) printf(" + ");
    }
    printf("\n");
}


// 輸出陣列
void printArray(int arr[][2], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d %d\n", arr[i][0], arr[i][1]);
    }
}

int main() {
    // 範例：A(x) = 3x^4 + 2x^2 + 1
    //      B(x) = 5x^3 + 2x^2 + 4
    struct struct1* A = NULL;
    struct struct1* B = NULL;
    insertNode(&A, 4, 3);
    insertNode(&A, 3, 1);
    insertNode(&A, 2, 0);
    insertNode(&B, 3, 3);
    insertNode(&B, 6, 2);
    insertNode(&B, 9, 1);
    insertNode(&B, 1, 0);

    // 輸出多項式 A 和 B
    printPoly(A, 'A');
    printPoly(B, 'B');
    struct struct1* C = addPoly(A, B);
    printPoly(C, 'C');

    int arr[20][2];
    int size = 0;
    convertToCircular(C);
    struct struct1* curr = C;

    // 輸出陣列
    printArray(arr, size);

    // 釋放記憶體
    struct struct1* curr;
    while (A) { curr = A; A = A->next; free(curr); }
    while (B) { curr = B; B = B->next; free(curr); }
    while (C) { curr = C; C = C->next; free(curr); }
    return 0;
}