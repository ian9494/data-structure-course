#include <stdio.h>

int main()
{
    int arr[9] = {-4, 2, -5, 4, -3, 2, 1, -1, 5};
    int n = 9;
    int maxSum = maxSubArray(arr, n);
    printf("Maximum subarray sum is %d\n", maxSum);
}

int maxSubArray(int arr[], int n) {
    int maxSum = arr[0]; //初始化最大和為陣列的第一個元素
    int currentSum = arr[0]; //當前子陣列和初始化為第一個元素

    for (int i = 1; i < n; i++) { //從第二個元素開始遍歷陣列
        currentSum = (arr[i] > currentSum + arr[i]) ? arr[i] : currentSum + arr[i]; //決定是否將當前元素加入子陣列或重新開始, 如果當前元素大於當前和加上當前元素，則重新開始子陣列
        maxSum = (currentSum > maxSum) ? currentSum : maxSum;
        //每次迴圈後的最大子陣列
        printf("i=%d, currentSum=%d, maxSum=%d\n", i, currentSum, maxSum);
    }

    return maxSum;
}