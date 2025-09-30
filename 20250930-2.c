#include <stdio.h>

// 優先順序
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0;
}

// 計算
int calc(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '%': return a % b;
    }
    return 0;
}

int main() {
    char filename[100];
    int nums[100];
    char operators[100];

    printf("Enter filename> ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int num_count = 0, operator_count = 0, bracket = 0;
    char ch;
    
    while ((ch = fgetc(file)) != EOF) {
        if (ch >= '0' && ch <= '9') {
            num_count++;
            // 跳過連續的數字（只消耗數字，不再讀下一個非數字字元）
            while ((ch = fgetc(file)) != EOF && (ch >= '0' && ch <= '9')) {
                // 只消耗數字
            }
            // 跳出後 ch 不是數字，需處理 ch
            if (ch == EOF) break;
            // 這裡不 return，繼續判斷 ch
        }
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') {
            operator_count++;
            // printf("Operator: %c\n", ch);
        } else if (ch == '(') {
            bracket++;
        }
    }

    fclose(file);

    printf("Numbers: %d\n", num_count);
    printf("Operators: %d\n", operator_count);
    printf("Brackets: %d\n", bracket);

    // 計算算式
    // --- 堆疊結構 ---
    #define MAX_STACK 100
    int numStack[MAX_STACK], numTop = -1;
    char opStack[MAX_STACK], opTop = -1;

    // 重新打開檔案，逐字元計算
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    int num = 0, readingNum = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch >= '0' && ch <= '9') {
            num = num * 10 + (ch - '0');
            readingNum = 1;
        } else {
            if (readingNum) {
                numStack[++numTop] = num;
                num = 0;
                readingNum = 0;
            }
            // 遇到括號要處理
            if (ch == '(') {
                opStack[++opTop] = ch;
            } else if (ch == ')') {
                while (opTop >= 0 && opStack[opTop] != '(') {
                    int b = numStack[numTop--];
                    int a = numStack[numTop--];
                    char op = opStack[opTop--];
                    numStack[++numTop] = calc(a, b, op);
                }
                if (opTop >= 0 && opStack[opTop] == '(') opTop--;
            } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') {
                while (opTop >= 0 && precedence(opStack[opTop]) >= precedence(ch)) {
                    int b = numStack[numTop--];
                    int a = numStack[numTop--];
                    char op = opStack[opTop--];
                    numStack[++numTop] = calc(a, b, op);
                }
                opStack[++opTop] = ch;
            }
        }
    }
    if (readingNum) {
        numStack[++numTop] = num;
    }
    while (opTop >= 0) {
        int b = numStack[numTop--];
        int a = numStack[numTop--];
        char op = opStack[opTop--];
        numStack[++numTop] = calc(a, b, op);
    }
    fclose(file);
    printf("Result: %d\n", numStack[numTop]);
    return 0;
}