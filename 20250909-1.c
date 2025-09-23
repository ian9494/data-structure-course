#include <stdio.h>

int main()
{
    int arr[100], arrLen, i;
    int min, max;
    float avg;

    printf("Enter number of elements in array: ");
    scanf("%d", &arrLen);

    printf("Enter %d elements:\n", arrLen);
    for (i = 0; i < arrLen; i++)
    {
        scanf("%d", &arr[i]);
    }

    calculateNum(arr, arrLen, &avg, &min, &max);

    printf("Average: %.2f\n", avg);
    printf("Minimum: %d\n", min);
    printf("Maximum: %d\n", max);
    return 0;
}

// returns average of array elements, minimum and maximum element
void calculateNum(int arr[100], int arrLen, float *avg, int *min, int *max)
{
    int i, sum = 0;
    *min = arr[0];
    *max = arr[0];

    for (i = 0; i < arrLen; i++)
    {
        sum += arr[i];

        if (arr[i] < *min)
            *min = arr[i];

        if (arr[i] > *max)
            *max = arr[i];
    }

    // 假設 arrLen 是陣列長度，作為參數傳入
    *avg = sum / (float)arrLen;
    return;
}