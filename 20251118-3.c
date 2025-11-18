#include <stdio.h>

int compareCount = 0;
int moveCount = 0; // count element moves/copies

void printArray(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[8], R[8];
    printf("dealing with indices (%d, %d):\n", left, right);
    printf(" Left part: ");
    printArray(&arr[left], n1);
    printf(" Right part: ");
    printArray(&arr[mid + 1], n2);
    

    for (int i = 0; i < n1; i++) { L[i] = arr[left + i]; moveCount++; }
    for (int j = 0; j < n2; j++) { R[j] = arr[mid + 1 + j]; moveCount++; }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        compareCount++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++]; moveCount++;
        } else {
            arr[k++] = R[j++]; moveCount++;
        }
    }
    while (i < n1) {
        arr[k++] = L[i++];
        moveCount++; // count this copy
    }
    while (j < n2) {
        arr[k++] = R[j++];
        moveCount++; // count this copy
    }
    printf(" Merged: ");
    printArray(&arr[left], n1 + n2);
    printf("\n");
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int originalArr[] = {55, 33, 22, 11, 77, 66, 44, 99};
    printf("Original array:\n");
    int n = sizeof(originalArr) / sizeof(originalArr[0]);
    printArray(originalArr, n);

    // merge sort
    printf("\nMerge Sort:\n");
    int arr[8];
    memcpy(arr, originalArr, sizeof(originalArr));
    compareCount = 0;
    moveCount = 0;


    mergeSort(arr, 0, n - 1);
    printf("Sorted array:\n");
    printArray(arr, n);
    printf("Total comparisons: %d\n", compareCount);
    printf("Total moves: %d\n", moveCount);
}