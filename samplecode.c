#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct MaxHeap {
    int data[MAX_SIZE]; 
    int size;           
} MaxHeap;

void printHeap(MaxHeap* heap) {
    printf("Heap內容:");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

void printHeapStructure(MaxHeap* heap, int index, int indent) {
    if (index >= heap->size) {
        return;
    }
    printHeapStructure(heap, 2 * index + 2, indent + 4);
    for (int i = 0; i < indent; i++) {
        printf(" ");
    }
    printf("%d\n", heap->data[index]);
    printHeapStructure(heap, 2 * index + 1, indent + 4);
}

int main() {
    MaxHeap heap;
    int preset[] = {90, 75, 80, 60, 65, 70, 50, 20, 30, 55};
    int n = sizeof(preset) / sizeof(preset[0]);

    heap.size = n;
    for (int i = 0; i < n; ++i) {
        heap.data[i] = preset[i];
    }

    printf("=== Max Heap 輸入 ===\n");
    printHeap(&heap);
    printHeapStructure(&heap, 0, 0);

    return 0;
}
