//將輸入的10個以內數字轉換成2,8,16進位 進位數可輸入自選
#include <stdio.h>

// 將字元陣列進行氣泡排序
void swapArray(char arr[], int n) {
    for(int i = 0; i < n - 1; ++i) {
        int swapped = 0;
        for(int j = 0; j < n - 1 - i; j++) {
            if(arr[j] > arr[j + 1]) {
                char temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if(swapped == 0) {
            break;
        }
    }
}

// 印出所有 1 最少的列（1-based），每個行號分行
void rowMinAll(char arr[10][33], int n) {
    int minCount = 33;
    int ones[10] = {0};
    for(int i = 0; i < n; i++) {
        int count = 0;
        for(int j = 0; j < 32; j++) {
            if(arr[i][j] == '1') count++;
        }
        ones[i] = count;
        if(count < minCount) minCount = count;
    }
    for(int i = 0; i < n; i++) {
        if(ones[i] == minCount) {
            printf("1數量最少為第 %d 行\n", i+1);
        }
    }
}

int main(){
    int num, base;

    printf("請輸入整數的個數(10個以內):");
    scanf("%d", &num);
    if(num > 10 || num <= 0){
        printf("輸入數量超出最大值\n");
        return 1;
    }

    int arr[10];
    printf("請輸入%d個整數:\n", num);
    for(int i = 0; i < num; i++){
        scanf("%d", &arr[i]);
    }

    printf("請輸入要轉換的進位(2,8,16):");
    scanf("%d", &base);
    if(base != 2 && base != 8 && base != 16){
        printf("無效的進位數，請輸入2、8或16。\n");
        return 1;
    }

    //將數字轉換為指定進位並輸出至二維陣列 
    char result[10][33]; //假設最大32位元加上結束符號
    for(int i = 0; i < num; i++){
        if(base == 2){
            //轉換為二進位
            for(int j = 31; j >= 0; j--){
                if (arr[i] % 2 == 1)
                    result[i][j] = '1';
                else
                    result[i][j] = '0';
                arr[i] = arr[i] / 2; //或 arr[i] >>= 1;
            }
            result[i][32] = '\0'; //結束符號

        } else if(base == 8){
            //轉換為八進位
            for(int j = 31; j >= 0; j--){
                result[i][j] = (arr[i] % 8) + '0';
                arr[i] = arr[i] / 8;
            }
            result[i][32] = '\0'; //結束符號

        } else if(base == 16){
            //轉換為十六進位
            for(int j = 31; j >= 0; j--){
                int remainder = arr[i] % 16;
                if(remainder < 10)
                    result[i][j] = remainder + '0';
                else
                    result[i][j] = (remainder - 10) + 'A';
                arr[i] = arr[i] / 16;
            }
            result[i][32] = '\0'; //結束符號
        }
    }

    // 輸出結果（去除前導零）
    int countZero[10] = {0};
    for(int i = 0; i < num; i++){
        // 找到第一個非零位數
        int start = 0;
        while(result[i][start] == '0' && start < 31) {
            start++;
        }
        // 紀錄前導零的數量，方便排序後輸出
        countZero[i] = start;
        printf("數字 %d 轉換為 %d 進位是: %s\n", arr[i], base, &result[i][start]);
    }

    printf("\n運作的結果如下:\n");

    for(int i = 0; i < num; i++){
        swapArray(result[i], 32);
        // 排序後前面的0會一起被跳過，所以直接用countZero來定位
        int start = countZero[i];
        printf("%s\n", &result[i][start]);
    }

    printf("\n");
    rowMinAll(result, num);
}

