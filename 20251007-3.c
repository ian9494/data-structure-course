#include <stdio.h>

int arr[5];

int main() {
    // 讓兩個堆疊共用一個陣列
    // stack1 從左邊開始
    // stack2 從右邊開始
    // 不得重疊 指標相遇時表示堆疊已滿
    int top1 = -1; // stack1 指標
    int top2 = 5;  // stack2 指標
    int choice, value;
    
    while (1) {
        printf("\n\n=====Menu=====\n"
        "1. push stack1\n"
        "2. push stack2\n"
        "3. pop stack1\n"
        "4. pop stack2\n"
        "5. display both stacks\n"
        "6. exit\n"
        "================\n"
        "Enter your choice> ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // push stack1
                if (top1 + 1 == top2) {
                    printf("Stack Overflow! Cannot push to stack1.\n");
                } else {
                    printf("Enter value to push to stack1> ");
                    scanf("%d", &value);
                    arr[++top1] = value;
                    printf("Pushed %d to stack1.\n", value);
                }
                break;
            case 2: // push stack2
                if (top2 - 1 == top1) {
                    printf("Stack Overflow! Cannot push to stack2.\n");
                } else {
                    printf("Enter value to push to stack2: ");
                    scanf("%d", &value);
                    arr[--top2] = value;
                    printf("Pushed %d to stack2.\n", value);
                }
                break;
            case 3: // pop stack1
                if (top1 == -1) {
                    printf("Stack Underflow! Cannot pop from stack1.\n");
                } else {
                    value = arr[top1--];
                    printf("Popped %d from stack1.\n", value);
                }
                break;
            case 4: // pop stack2
                if (top2 == 5) {
                    printf("Stack Underflow! Cannot pop from stack2.\n");
                } else {
                    value = arr[top2++];
                    printf("Popped %d from stack2.\n", value);
                }
                break;
            case 5: // display both stacks
                printf("Stack1: ");
                for (int i = 0; i <= top1; i++) {
                    printf("%d ", arr[i]);
                }
                printf("\nStack2: ");
                for (int i = 5 - 1; i >= top2; i--) {
                    printf("%d ", arr[i]);
                }
                printf("\n");
                break;
            case 6: // exit
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}