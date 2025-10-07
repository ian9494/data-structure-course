#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct product {
    char prod_id[10]; // 修改為字串以支援 001, 002 等格式
    char prod_name[50];
    int price;
    int quantity;
    int total_value;
    struct product* next;
};

void listProducts(struct product* head) {
    printf("--------------------------------------\n");
    printf("ID\tName\tPrice\tQuantity\tTotal Value\n");
    printf("--------------------------------------\n");
    struct product* current = head;
    while (current != NULL) {
        printf("%s\t%s\t%d\t%d\t%d\n", current->prod_id, current->prod_name, current->price, current->quantity, current->total_value);
        current = current->next;
    }
    printf("--------------------------------------\n");
}

void addProduct(struct product** head) {
    struct product* new_product = (struct product*)malloc(sizeof(struct product));
    printf("Enter product ID: ");
    scanf("%s", new_product->prod_id);
    printf("Enter product name: ");
    scanf("%s", new_product->prod_name);
    printf("Enter price: ");
    scanf("%d", &new_product->price);
    printf("Enter quantity: ");
    scanf("%d", &new_product->quantity);
    new_product->total_value = new_product->price * new_product->quantity;
    new_product->next = *head;
    *head = new_product;
}

void deleteProduct(struct product** head, const char* prod_id) {
    struct product* current = *head;
    struct product* prev = NULL;

    printf("\n\n");
    while (current != NULL) {
        if (strcmp(current->prod_id, prod_id) == 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Product with ID %s deleted.\n", prod_id);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Product with ID %s not found.\n", prod_id);
}

int main() {
    struct product* head = NULL;

    // 預先建立一些產品
    int initial_products[5][4] = {
        {"001", "ProdA", 10, 5},
        {"002", "ProdB", 15.5, 3},
        {"003", "ProdC", 8.2, 7},
        {"004", "ProdD", 12.75, 2},
        {"005", "ProdE", 20, 4}
    };

    for (int i = 4; i >= 0; i--) {
        struct product* new_product = (struct product*)malloc(sizeof(struct product));
        snprintf(new_product->prod_id, sizeof(new_product->prod_id), "%s", initial_products[i][0]);
        snprintf(new_product->prod_name, sizeof(new_product->prod_name), "%s", initial_products[i][1]);
        new_product->price = initial_products[i][2];
        new_product->quantity = initial_products[i][3];
        new_product->total_value = new_product->price * new_product->quantity;
        new_product->next = head;
        head = new_product;
    }

    while (1) {
        printf(
            "\n=====Menu=====\n"
            "1. show all products\n"
            "2. add a product\n"
            "3. delete a product\n"
            "4. exit\n"
            "================\n"
            "Enter your choice> "
        );

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                listProducts(head);
                break;
            case 2:
                addProduct(&head);
                listProducts(head);
                break;
            case 3:
                printf("Enter product ID to delete: ");
                char prod_id[10];
                if (scanf("%s", prod_id) != 1) {
                    printf("Invalid input. Please enter a valid product ID.\n");
                    while (getchar() != '\n'); // 清除輸入緩衝區
                    continue;
                }
                deleteProduct(&head, prod_id);
                listProducts(head);
                break;
            case 4:
                printf("Exiting...\n");
                // 釋放所有節點記憶體
                while (head != NULL) {
                    struct product* temp = head;
                    head = head->next;
                    free(temp);
                }
                printf("All memory freed. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}