#include <stdio.h>

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void printGapContents(int arr[], int n, int gap) {
    for (int k = 0; k < gap; k++) {
        printf("[");
        for (int idx = k; idx < n; idx += gap) {
            printf("%d", arr[idx]);
            // don't print extra space at end
            if (idx + gap < n)  printf(" ");
        }
        printf("] ");
    }
    printf("\n");
}

int main() {
    int originalArr[] = {55, 33, 22, 11, 77, 66, 44, 99, 88, 50};

    printf("Original array:\n");
    int n = sizeof(originalArr) / sizeof(originalArr[0]);
    printArray(originalArr, n);

    // Insertion Sort
    printf("\nInsertion Sort:\n");
    int arr[10];
    int compareCount = 0, shiftCount = 0;
    memcpy(arr, originalArr, sizeof(originalArr));
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        // Move elements of arr[0..i-1], that are greater than key,
        // to one position ahead of their current position
        while (j >= 0) {
            compareCount++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                shiftCount++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
        printf("After inserting element %d: ", i);
        printArray(arr, n);
    }
    printf("Total comparisons: %d\n", compareCount);
    printf("Total shifts: %d\n", shiftCount);

    // Shell Sort
    printf("\nShell Sort:\n");
    compareCount = 0;
    shiftCount = 0;
    memcpy(arr, originalArr, sizeof(originalArr));
    // Using Shell's original gap sequence: n/2, n/4, ...,
    for (int gap = n / 2; gap > 0; gap /= 2) {
        printf("Gap=%d:\n", gap);
        printGapContents(arr, n, gap);
        // do gapped insertion sort for this gap size

        for (int i = gap; i < n; i++) {
            int key = arr[i];
            int j = i - gap;
            while (j >= 0) {
                compareCount++;
                if (arr[j] > key) {
                    arr[j + gap] = arr[j];
                    shiftCount++;
                    j -= gap;
                } else {
                    break;
                }
            }
            // print gap contents after each insertion
            printf("After inserting element %d: ", i);
            printGapContents(arr, n, gap);
            arr[j + gap] = key;
        }
    }
    printf("Total comparisons: %d\n", compareCount);
    printf("Total shifts: %d\n", shiftCount);
}