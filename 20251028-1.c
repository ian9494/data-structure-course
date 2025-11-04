#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

static Node *create_node(int value) {
    Node *node = (Node *)malloc(sizeof(Node));

    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static Node *insert_node(Node *root, int value) {
    if (!root) {
        return create_node(value);
    }
    if (value < root->value) {
        root->left = insert_node(root->left, value);
    } else {
        root->right = insert_node(root->right, value);
    }
    return root;
}

static void free_tree(Node *root) {
    if (!root) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

static int check_balance(const Node *root) {
    if (!root) {
        return 0;
    }
    int left_height = check_balance(root->left);
    if (left_height == -1) {
        return -1;
    }
    int right_height = check_balance(root->right);
    if (right_height == -1) {
        return -1;
    }
    if (abs(left_height - right_height) > 1) {
        return -1;
    }
    return (left_height > right_height ? left_height : right_height) + 1;
}

static bool is_balanced(const Node *root) {
    return check_balance(root) != -1;
}

static void append_value(int **array, int *capacity, int *size, int value) {
    if (*size >= *capacity) {
        int new_capacity = (*capacity == 0) ? 16 : (*capacity * 2);
        int *temp = (int *)realloc(*array, sizeof(int) * new_capacity);

        *array = temp;
        *capacity = new_capacity;
    }
    (*array)[(*size)++] = value;
}

static void collect_inorder(const Node *root, int **array, int *capacity, int *size) {
    if (!root) {
        return;
    }
    collect_inorder(root->left, array, capacity, size);
    append_value(array, capacity, size, root->value);
    collect_inorder(root->right, array, capacity, size);
}

static Node *build_balanced_from_sorted(const int *array, int left, int right) {
    if (left > right) {
        return NULL;
    }
    int mid = left + (right - left) / 2;
    Node *root = create_node(array[mid]);
    root->left = build_balanced_from_sorted(array, left, mid - 1);
    root->right = build_balanced_from_sorted(array, mid + 1, right);
    return root;
}

static Node *rebuild_balanced_tree(Node *root) {
    if (!root) {
        return NULL;
    }
    int *values = NULL;
    int capacity = 0;
    int size = 0;
    collect_inorder(root, &values, &capacity, &size);

    Node *new_root = build_balanced_from_sorted(values, 0, size - 1);
    free(values);
    free_tree(root);
    return new_root;
}

static void print_preorder_internal(const Node *root, bool *first) {
    if (!root) {
        return;
    }
    if (!*first) {
        printf(" ");
    }
    printf("%d", root->value);
    *first = false;
    print_preorder_internal(root->left, first);
    print_preorder_internal(root->right, first);
}

static void print_inorder_internal(const Node *root, bool *first) {
    if (!root) {
        return;
    }
    print_inorder_internal(root->left, first);
    if (!*first) {
        printf(" ");
    }
    printf("%d", root->value);
    *first = false;
    print_inorder_internal(root->right, first);
}

static void print_preorder(const Node *root) {
    bool first = true;
    print_preorder_internal(root, &first);
}

static void print_inorder(const Node *root) {
    bool first = true;
    print_inorder_internal(root, &first);
}

static Node *insert_and_balance(Node *root, int value) {
    root = insert_node(root, value);
    if (!is_balanced(root)) {
        root = rebuild_balanced_tree(root);
    }
    return root;
}

int main(void) {
    const char *filename = "data.txt";
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Failed to open file %s.\n", filename);
        return EXIT_FAILURE;
    }

    Node *root = NULL;
    int value = 0;
    int read_count = 0;
    while (fscanf(file, "%d", &value) == 1) {
        root = insert_node(root, value);
        read_count++;
    }
    fclose(file);

    printf("Binary search tree (preorder): ");
    print_preorder(root);
    printf("\n");
    printf("Binary search tree (inorder): ");
    print_inorder(root);
    printf("\n\n");

    if (is_balanced(root)) {
        printf("BST is balanced. No rebuild required.\n\n");
    } else {
        printf("BST is not balanced. Rebuilding.\n");
        root = rebuild_balanced_tree(root);
        printf("Rebuilt balanced BST (preorder): ");
        print_preorder(root);
        printf("\n");
        printf("Rebuilt balanced BST (inorder): ");
        print_inorder(root);
        printf("\n\n");
    }

    // 多個輸入測試插入並保持平衡
    while (true) {
        printf("Enter a value to insert into BST (or '-1' to quit): ");
        if (scanf("%d", &value) != 1 || value == -1) {
            break;
        }
    int new_value = value;
    printf("Insert %d into BST while keeping balance.\n", new_value);
    root = insert_and_balance(root, new_value);
    printf("Balanced BST after insertion (preorder): ");
    print_preorder(root);
    printf("\n");
    printf("Balanced BST after insertion (inorder): ");
    print_inorder(root);
    printf("\n");
    }

    free_tree(root);
    return EXIT_SUCCESS;
}
