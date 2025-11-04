#include <stdio.h>

struct Date
{
    int day;
    int month;
    int year;
    char name[100];
};

int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int days_in_month(int month, int year) {
    if (month == 2) {
        return is_leap_year(year) ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 31;
    }
}


// 計算某日期到 0000/1/1 的總天數
int days_from_origin(int year, int month, int day) {
    int days = 0;
    for (int y = 0; y < year; y++) {
        days += is_leap_year(y) ? 366 : 365;
    }
    for (int m = 1; m < month; m++) {
        days += days_in_month(m, year);
    }
    days += day;
    return days;
}

int main() {
    struct Date person1, person2;
    printf("請輸入第一位的資訊(James 2010 5 20):\n");
    scanf("%s %d %d %d", person1.name, &person1.year, &person1.month, &person1.day);
    printf("請輸入第二位的資訊(Doris 2012 4 20):\n");
    scanf("%s %d %d %d", person2.name, &person2.year, &person2.month, &person2.day);

    int days1 = days_from_origin(person1.year, person1.month, person1.day);
    int days2 = days_from_origin(person2.year, person2.month, person2.day);
    int distance = days1 > days2 ? days1 - days2 : days2 - days1;

    printf("%s 和 %s 之間相隔 %d 天\n", person1.name, person2.name, distance);
    return 0;
}
