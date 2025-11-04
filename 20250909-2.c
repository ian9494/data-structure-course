#include <stdio.h>

void main()
{
    //印出10層的巴斯卡三角形
    int i, j, coef = 1, space;
    
    for (i = 0; i < 10; i++)
    {
        //每層10-i個空白
        for (space = 1; space <= 10 - i; space++)
            printf("  ");

        //每層i+1個數字
        for (j = 0; j <= i; j++)
        {
            if (j == 0 || i == 0)
                coef = 1;
            else
                // 計算組合數 C(i, j) 公式: C(i, j) = coef * (i - j + 1) / j
                coef = coef * (i - j + 1) / j;

            printf("%4d", coef);
        }
        printf("\n");
    }
    return;
}