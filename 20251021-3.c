#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    int ID;
    int score;
    char name[20];
    struct Node* left;
    struct Node* right;
};

void preorder(struct Node* node) {
    if (node == NULL) return;
    
    printf("ID: %d, Name: %s, score: %d\n", node->ID, node->name, node->score);

    preorder(node->left);
    preorder(node->right);
}

// collect nodes into array (DFS)
int collect_nodes(struct Node* node, struct Node** arr, int idx) {
    if (!node) return idx;
    arr[idx++] = node;
    idx = collect_nodes(node->left, arr, idx);
    idx = collect_nodes(node->right, arr, idx);
    return idx;
}

int cmp_node_id(const void* a, const void* b) {
    struct Node* A = *(struct Node**)a;
    struct Node* B = *(struct Node**)b;
    return A->ID - B->ID;
}

// Print all nodes sorted by ID in sample format
void print_sorted_by_id(struct Node* root) {
    if (!root) return;
    struct Node* arr[1024];
    int cnt = collect_nodes(root, arr, 0);
    if (cnt == 0) return;
    qsort(arr, cnt, sizeof(struct Node*), cmp_node_id);
    for (int i = 0; i < cnt; i++) {
        printf("ID: %d, Name: %s , Score: %d\n", arr[i]->ID, arr[i]->name, arr[i]->score);
    }
}

struct Node* searchID(struct Node* node, int ID) {
    if (node == NULL) return NULL;
    if (node->ID == ID) return node;
    struct Node* res = searchID(node->left, ID);
    if (res) return res;
    return searchID(node->right, ID);
}

int main() {
    struct Node* root = NULL;
    struct Node* current = NULL;

    printf("insert initial data from score.txt\n");
    // insert initial data from score.txt
    FILE* file = fopen("score.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    while (1) {
        struct Node* newNode = malloc(sizeof(struct Node));
        if (fscanf(file, "%d %s %d", &newNode->ID, newNode->name, &newNode->score) != 3) {
            free(newNode);
            break;
        }
        newNode->left = NULL;
        newNode->right = NULL;

        // insert into BST
        current = root;
        struct Node* parent = NULL;
        while (current != NULL) {
            parent = current;
            if (newNode->score < current->score) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        if (parent == NULL) {
            root = newNode;
        } else if (newNode->score < parent->score) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }
    printf("Initial data loaded from score.txt.\n");
    fclose(file);

    while (1){
        int choice;
        printf("===Main Menu===\n"
            "1. Show BTS data\n"
            "2. Search for data\n"
            "3. Insert data\n"
            "4. Delete data\n"
            "0. Exit\n"
            "Enter Your Operation:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1: // show data (sorted by ID to match sample)
            print_sorted_by_id(root);
            printf("\n");
            break;
        case 2: { // search for data
            int searchingID;
            printf("Enter ID to search: ");
            scanf("%d", &searchingID);
            struct Node* found = searchID(root, searchingID);
            if (found) printf("Found data - ID: %d, Name: %s, score: %d\n", found->ID, found->name, found->score);
            else printf("Data not found.\n");
            printf("\n");
            break;
        }
        case 3: { // insert data
            struct Node* newNode = malloc(sizeof(struct Node));
            printf("Enter ID: ");
            scanf("%d", &newNode->ID);
            printf("Enter Name: ");
            scanf("%s", newNode->name);
            printf("Enter score: ");
            scanf("%d", &newNode->score);
            newNode->left = NULL;
            newNode->right = NULL;
            // insert into BST
            current = root;
            struct Node* parent = NULL;
            while (current != NULL) {
                parent = current;
                if (newNode->score < current->score) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            if (parent == NULL) {
                root = newNode;
            } else if (newNode->score < parent->score) {
                parent->left = newNode;
            } else {
                parent->right = newNode;
            }
            break;
        }
        case 4: // delete data
            int deletingID;
            printf("Enter ID to delete: ");
            scanf("%d", &deletingID);
            current = root;
            struct Node* parentDel = NULL;
            while (current != NULL && current->ID != deletingID) {
                parentDel = current;
                if (deletingID < current->ID) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            if (current == NULL) {
                printf("Data not found.\n");
                break;
            }
            
            if (current->left == NULL && current->right == NULL) {
                // Case 1: No children
                if (parentDel == NULL) {
                    root = NULL;
                } else if (parentDel->left == current) {
                    parentDel->left = NULL;
                } else {
                    parentDel->right = NULL;
                }
            } else if (current->left == NULL || current->right == NULL) {
                // Case 2: One child
                struct Node* child = (current->left != NULL) ? current->left : current->right;
                if (parentDel == NULL) {

                    root = child;
                } else if (parentDel->left == current) {
                    parentDel->left = child;
                } else {
                    parentDel->right = child;
                }
            } else {
                // Case 3: Two children
                struct Node* successor = current->right;
                struct Node* successorParent = current;
                while (successor->left != NULL) {
                    successorParent = successor;
                    successor = successor->left;
                }
                current->ID = successor->ID;
                strcpy(current->name, successor->name);
                current->score = successor->score;
                if (successorParent->left == successor) {
                    successorParent->left = successor->right;
                } else {
                    successorParent->right = successor->right;
                }
            }
            free(current);
            printf("Data with ID %d deleted.\n", deletingID);
            printf("\n");
            break;
        case 0:
            printf("Exiting program...\n");
            return 0;
        default:
            break;
        }
    }
}