#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 128

typedef struct {
    int *data;   // 1-based heap array
    int size;    // number of elements
    int cap;     // capacity of allocated array
} MaxHeap;

static void heap_init(MaxHeap *h) {
    h->cap = INITIAL_CAPACITY;
    h->data = (int*)malloc(sizeof(int) * (h->cap + 1));
    h->size = 0;
}

static void heap_free(MaxHeap *h) {
    free(h->data);
    h->data = NULL;
    h->size = 0;
    h->cap = 0;
}

static void ensure_capacity(MaxHeap *h, int needed) {
    if (needed <= h->cap) return;
    while (h->cap < needed) h->cap *= 2;
    h->data = (int*)realloc(h->data, sizeof(int) * (h->cap + 1));
}

static void swap_int(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

// max-heapify at index i (1-based)
static void max_heapify(MaxHeap *h, int i) {
    while (1) {
        int l = 2 * i;
        int r = 2 * i + 1;
        int largest = i;
        if (l <= h->size && h->data[l] > h->data[largest]) largest = l;
        if (r <= h->size && h->data[r] > h->data[largest]) largest = r;
        if (largest != i) {
            swap_int(&h->data[i], &h->data[largest]);
            i = largest;
        } else break;
    }
}

// Build max heap using Method 2: bottom-up, O(n)
static void build_max_heap(MaxHeap *h) {
    for (int i = h->size / 2; i >= 1; i--) {
        max_heapify(h, i);
    }
}

// Insert single value by appending and then sifting up (not used for Method 2 build)
static void heap_insert(MaxHeap *h, int val) {
    ensure_capacity(h, h->size + 1);
    h->size++;
    h->data[h->size] = val;
    int i = h->size;
    while (i > 1 && h->data[i/2] < h->data[i]) {
        swap_int(&h->data[i/2], &h->data[i]);
        i /= 2;
    }
}

// Delete the first occurrence of value 'val' from heap. Return 1 if deleted, 0 if not found.
static int heap_delete_value(MaxHeap *h, int val) {
    if (h->size == 0) return 0;
    int idx = -1;
    for (int i = 1; i <= h->size; i++) {
        if (h->data[i] == val) { idx = i; break; }
    }
    if (idx == -1) return 0;
    // replace with last
    h->data[idx] = h->data[h->size];
    h->size--;
    if (idx <= h->size) {
        // try sift down, if not moved, try sift up
        max_heapify(h, idx);
        int parent = idx / 2;
        while (idx > 1 && h->data[parent] < h->data[idx]) {
            swap_int(&h->data[parent], &h->data[idx]);
            idx = parent;
            parent = idx / 2;
        }
    }
    return 1;
}

// Print heap as array
static void print_heap_array(MaxHeap *h) {
    if (h->size == 0) {
        printf("Heap:\n");
        return;
    }
    // Match samplecode.c exact label and spacing
    printf("Heap: ");
    for (int i = 1; i <= h->size; i++) {
        printf("%d", h->data[i]);
        if (i < h->size) printf(" ");
    }
    printf("\n");
}

// prototype for 0-based structure printer (matches samplecode.c)
static void print_heap_structure_0based(MaxHeap *h, int idx0, int indent);

int main(void) {
    MaxHeap heap;
    heap_init(&heap);

    int choice;
    while (1) {
        printf("Menu:\n");
        printf("1. Insert multiple values\n");
        printf("2. Delete target value\n");
        printf("3. Print Max Heap content\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) break;

        if (choice == 1) {
            printf("Enter number of values to insert: ");
            int n;
            if (scanf("%d", &n) != 1) { printf("Invalid number\n"); continue; }
            if (n <= 0) { printf("Nothing to insert\n"); continue; }
            ensure_capacity(&heap, heap.size + n);
            // read n values and append
            printf("Enter %d values:\n", n);
            for (int i = 0; i < n; i++) {
                int v; if (scanf("%d", &v) != 1) { v = 0; }
                heap.data[++heap.size] = v;
            }
            // build heap bottom-up (Method 2)
            build_max_heap(&heap);
        } else if (choice == 2) {
            printf("Enter value to delete: ");
            int target; if (scanf("%d", &target) != 1) { printf("Invalid input\n"); continue; }
            int ok = heap_delete_value(&heap, target);
            if (ok) {
                printf("Value %d deleted.\n", target);
            } else {
                // message similar to attachment
                printf("Value %d not found in heap\n", target);
            }
        } else if (choice == 3) {
            printf("---- Max Heap content ----\n");
            print_heap_array(&heap);
            printf("---- Tree view ----\n");
            print_heap_structure_0based(&heap, 0, 0);
        } else if (choice == 0) {
            printf("End of program.\n");
            break;
        } else {
            printf("Invalid choice, please try again.\n");
        }
    }

    heap_free(&heap);
    return 0;
}

// Print heap structure similar to samplecode.c (right-root-left, rotated)
// Print heap structure using the same algorithm as samplecode.c (0-based indices)
// This function accepts a 0-based index and maps to our 1-based internal array.
static void print_heap_structure_0based(MaxHeap *h, int idx0, int indent) {
    if (idx0 >= h->size) return; // nothing to print
    int right0 = 2 * idx0 + 2;
    int left0 = 2 * idx0 + 1;
    // print right subtree first
    if (right0 < h->size) print_heap_structure_0based(h, right0, indent + 4);
    // print current node with indent
    for (int i = 0; i < indent; i++) putchar(' ');
    // convert 0-based index to 1-based for access
    printf("%d\n", h->data[idx0 + 1]);
    // print left subtree
    if (left0 < h->size) print_heap_structure_0based(h, left0, indent + 4);
}