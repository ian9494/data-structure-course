#include <stdio.h>

struct product {
    int ID;
    char name[50];
    float price;
    int stock;
    float total_price;
    struct product *next;
};

int main() {
    int choice;
    struct product *head = NULL;
    struct product *tail = NULL;

    while (1) {

        printf("\n\n主選單:\n"
           "1. 載入 product.txt 檔案\n"
           "2. 顯示所有產品資料\n"
           "3. 新增產品資料到串列頭\n"
           "4. 新增產品資料到串列尾\n"
           "5. 刪除產品資料\n"
           "6. 以反轉串列顯示所有產品資料\n"
           "0. 離開\n"
           "請輸入您的選擇> ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            // 匯入product.txt
            FILE *file = fopen("product.txt", "r");
            if (file == NULL) {
                perror("fopen");
                printf("無法開啟檔案\n");
                return 1;
            }

            // struct product *head = NULL;
            // struct product *tail = NULL;
            int total = 0, skipped = 0;
            while (1) {
                struct product *new_product = malloc(sizeof(struct product));
                // 讀取逗號分隔格式
                if (fscanf(file, "%d, %[^,], %f, %d, %*f", &new_product->ID, new_product->name, &new_product->price, &new_product->stock) != 4) {
                    free(new_product);
                    break;
                }
                // 檢查重複ID
                int duplicate = 0;
                struct product *cur = head;
                while (cur != NULL) {
                    if (cur->ID == new_product->ID) {
                        duplicate = 1;
                        break;
                    }
                    cur = cur->next;
                }
                if (duplicate) {
                    printf("重複的產品編號: %03d（%s），跳過第 %d 筆資料\n", new_product->ID, new_product->name, total + skipped + 1);
                    free(new_product);
                    skipped++;
                    continue;
                }
                new_product->total_price = new_product->price * new_product->stock;
                new_product->next = NULL;
                if (head == NULL) {
                    head = new_product;
                    tail = new_product;
                } else {
                    tail->next = new_product;
                    tail = new_product;
                }
                // tail 更新（確保 tail 指向最後一個節點）
                struct product *tmp = head;
                while (tmp->next != NULL) tmp = tmp->next;
                tail = tmp;

                total++;
            }
            printf("已從檔案載入產品資料，共 %d 筆。\n", total);
            if (skipped > 0) {
                printf("（有 %d 筆重複資料被跳過）\n", skipped);
            }
            break;
        
        case 2:
            // 顯示所有產品資料
            if (head == NULL) {
                printf("目前沒有任何產品資料。\n");
                break;
            } else {
                struct product *current = head;
                printf("編號\t名稱\t價格\t數量\t總金額\n");
                while (current != NULL) {
                    printf("%03d\t%s\t$%.2f\t%d\t$%.2f\n", current->ID, current->name, current->price, current->stock, current->total_price);
                    current = current->next;
                }
            }
            break;
        case 3:
            // 新增產品資料到串列頭
            {
                struct product *new_product = malloc(sizeof(struct product));
                
                printf("請輸入產品編號: ");
                scanf("%d", &new_product->ID);
                printf("請輸入產品名稱: ");
                scanf("%s", new_product->name);
                printf("請輸入產品價格: ");
                scanf("%f", &new_product->price);
                printf("請輸入產品數量: ");
                scanf("%d", &new_product->stock);

                new_product->total_price = new_product->price * new_product->stock;
                new_product->next = head;
                head = new_product;
            }
            break;
        
        case 4:
            // 新增產品資料到串列尾
            {
                struct product *new_product = malloc(sizeof(struct product));
                
                printf("請輸入產品編號: ");
                scanf("%d", &new_product->ID);
                printf("請輸入產品名稱: ");
                scanf("%s", new_product->name);
                printf("請輸入產品價格: ");
                scanf("%f", &new_product->price);
                printf("請輸入產品數量: ");
                scanf("%d", &new_product->stock);

                new_product->total_price = new_product->price * new_product->stock;
                new_product->next = NULL;

                if (head == NULL) {
                    head = new_product;
                    tail = new_product;
                } else {
                    tail->next = new_product;
                    tail = new_product;
                }
                // tail 更新（確保 tail 指向最後一個節點）
                struct product *tmp = head;
                while (tmp->next != NULL) tmp = tmp->next;
                tail = tmp;
            }
            break;
        
        case 5:
            // 刪除產品資料
            {
                int delete_id;
                printf("請輸入要刪除的產品編號: ");
                scanf("%d", &delete_id);

                struct product *current = head;
                struct product *previous = NULL;

                if (head == NULL) {
                    printf("目前沒有任何產品可以刪除。\n");
                    break;
                }

                while (current != NULL && current->ID != delete_id) {
                    previous = current;
                    current = current->next;
                }

                if (current == NULL) {
                    printf("找不到編號為 %03d 的產品。\n", delete_id);
                } else {
                    if (previous == NULL) {
                        head = current->next; // 刪除的是頭節點
                    } else {
                        previous->next = current->next; // 刪除中間或尾節點
                    }
                    free(current);
                    printf("已刪除編號為 %d 的產品。\n", delete_id);
                    break;
                }
            }
            break;
        case 6:
            // 以反轉串列顯示所有產品資料
            {
                if (head == NULL) {
                    printf("目前沒有任何產品資料。\n");
                    break;
                }

                struct product *prev = NULL;
                struct product *current = head;
                struct product *next = NULL;

                while (current != NULL) {
                    next = current->next;
                    current->next = prev;
                    prev = current;
                    current = next;
                }
                head = prev;

                // 顯示反轉後的串列
                current = head;
                printf("編號\t名稱\t價格\t數量\t總金額\n");
                while (current != NULL) {
                    printf("%03d\t%s\t$%.2f\t%d\t$%.2f\n", current->ID, current->name, current->price, current->stock, current->total_price);
                    current = current->next;
                }
            }
            break;
        
        case 0:    
            // 離開
            printf("正在離開...\n");
            // 釋放記憶體
            while (head != NULL) {
                struct product *temp = head;
                head = head->next;
                free(temp);
            }
            printf("程式結束，所有分配記憶體已釋放。\n");
            return 0;

        default:
            printf("無效的選擇，請重新輸入。 \n");
            break;
        }
    }
    return 0;
}