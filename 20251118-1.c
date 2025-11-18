#include <stdio.h>

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int originalArr[] = {55, 33, 22, 11, 77, 66, 44, 99, 88, 50};
    printf("Original array:\n");
    int n = sizeof(originalArr) / sizeof(originalArr[0]);
    printArray(originalArr, n);
    
    // traditional selection sort
    printf("\nTraditional Selection Sort:\n");
    n = sizeof(originalArr) / sizeof(originalArr[0]);
    int arr[10];
    int compareCount = 0, swapCount = 0;

    memcpy(arr, originalArr, sizeof(originalArr));

    int i;
    for (i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            compareCount++;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        // swap arr[i] and arr[minIdx]
        int temp = arr[i];
        arr[i] = arr[minIdx];
        arr[minIdx] = temp;
        // count swap only if different indices
        if (i != minIdx) swapCount++;
        printf("After pass %d: ", i + 1);
        printArray(arr, n);
    }
    printArray(arr, n);
    printf("Total comparisons: %d\n", compareCount);
    printf("total swaps: %d\n", swapCount);

    // better selection sort (take min to front and max to back)

    printf("\nBetter Selection Sort:\n");
    compareCount = 0, swapCount = 0;
    memcpy(arr, originalArr, sizeof(originalArr));
    n = sizeof(arr) / sizeof(arr[0]);
    int left = 0, right = n - 1;
    int pass = 1;
    while (left < right) {
        int minIdx = left;
        int maxIdx = left;
        for (int j = left; j <= right; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
            if (arr[j] > arr[maxIdx]) {
                maxIdx = j;
            }
            compareCount++;
        }
        // swap min to front
        int temp = arr[left];
        arr[left] = arr[minIdx];
        arr[minIdx] = temp;
        // if max was at left, it is now at minIdx
        if (maxIdx == left) {
            maxIdx = minIdx;
        }
        // swap max to back
        temp = arr[right];
        arr[right] = arr[maxIdx];
        arr[maxIdx] = temp;
        // count swaps only if different indices
        if (left != minIdx) swapCount++;
        if (right != maxIdx) swapCount++;

        printf("After pass %d: ", pass++);
        printArray(arr, n);
        left++;
        right--;
    }
    printArray(arr, n);
    printf("Total comparisons: %d\n", compareCount);
    printf("total swaps: %d\n", swapCount);
    return 0;
}