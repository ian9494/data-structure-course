#include <stdio.h>

struct student {
    int ID;
    char name[50];
    struct grade grades;
};

struct grade {
    float chinese;
    float english;
    float math;
    float sum;
    float average;
    int rank;
};

int main() {
    //從data.txt中讀取
    struct student students[100];
    int count = 0;
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("無法開啟檔案\n");
        return 1;
    }
    
    // 讀取數據並計算總分與平均（同一行多筆資料）
    char buffer[4096];
    fgets(buffer, sizeof(buffer), file);
    char *p = buffer;
    while (1) {
        int n = sscanf(p, "%d %s %f %f %f", &students[count].ID, students[count].name, &students[count].grades.chinese, &students[count].grades.english, &students[count].grades.math);
        if (n != 5) break;
        students[count].grades.sum = students[count].grades.chinese + students[count].grades.english + students[count].grades.math;
        students[count].grades.average = students[count].grades.sum / 3.0;
        count++;
        // 跳到下一組
        int skip = 0;
        while (*p && skip < 5) {
            // 跳過一個欄位
            while (*p && *p != ' ' && *p != '\n') p++;
            while (*p == ' ' || *p == '\n') p++;
            skip++;
        }
    }
    fclose(file);

    // 計算排名
    for (int i = 0; i < count; i++) {
        students[i].grades.rank = 1;
        for (int j = 0; j < count; j++) {
            if (students[j].grades.average > students[i].grades.average) {
                students[i].grades.rank++;
            }
        }
    }

    // 根據排名排序
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (students[j].grades.rank > students[j + 1].grades.rank) {
                struct student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    // 輸出結果
    printf("ID\tName\tChinese\tEnglish\tMath\tSum\tAvg\tRank\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%d\n",
               students[i].ID, students[i].name,
               students[i].grades.chinese, students[i].grades.english, students[i].grades.math,
               students[i].grades.sum, students[i].grades.average, students[i].grades.rank);
    }

    return 0;
}