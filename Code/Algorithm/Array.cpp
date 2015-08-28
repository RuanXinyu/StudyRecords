//
// Created by ruan on 15-7-30.
//

#include "Array.h"

#include "gtest/gtest.h"

// 最大子序列和
int Array_MaxSumOfSubsequence(int *arr, size_t n) {
    assert(arr != nullptr && n > 0);
    int max = arr[0], sum = arr[0];
    for (int i = 1; i < n; ++i) {
        sum = sum < 0 ? arr[i] : arr[i] + sum;
        if (sum > max) {
            max = sum;
        }
    }
    return max;
}

TEST(Array, Array_MaxSumOfSubsequence) {
    int arr01[] = {1, 2, 3, 4, 5};
    EXPECT_EQ(15, Array_MaxSumOfSubsequence(arr01, 5));
    int arr02[] = {1, -2, 3, 4, 5};
    EXPECT_EQ(12, Array_MaxSumOfSubsequence(arr02, 5));
    int arr03[] = {1, -2, 3, -4, 5};
    EXPECT_EQ(5, Array_MaxSumOfSubsequence(arr03, 5));
    int arr04[] = {-1, 2, -7, 4, -5};
    EXPECT_EQ(4, Array_MaxSumOfSubsequence(arr04, 5));
    int arr05[] = {7, -2, -3, 4, 5};
    EXPECT_EQ(11, Array_MaxSumOfSubsequence(arr05, 5));
}


/*********************************************************************************************/
/*********************************************************************************************/
// 最长递增子序列
#define Array_MaxLenOfIncreaseSubsequence_FuncNum 2

#if Array_MaxLenOfIncreaseSubsequence_FuncNum == 1
int Array_MaxLenOfIncreaseSubsequence(int *arr, size_t n) {
    assert(arr != nullptr && n != 0);

    int *dp = (int *)malloc(sizeof(int) * n);
    int max = 0;

    for (int i = 0; i < n; ++i) {
        dp[i] = 1;
        for (int j =0; j < i; ++j) {
            if (arr[i] > arr[j] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
        if (dp[i] > max) {
            max = dp[i];
        }
    }

    free(dp);
    return max;
}

#elif Array_MaxLenOfIncreaseSubsequence_FuncNum == 2

int BinarySearch(int *arr, size_t n, int x) {
    int left = 0, right = n - 1, mid = 0;
    while (left <= right) {
        mid = (left + right) >> 1;
        if (arr[mid] >= x) {
            right = mid - 1;
        } else {
            left = mid +1;
        }
    }
    return left;
}

int Array_MaxLenOfIncreaseSubsequence(int *arr, size_t n) {
    assert(arr != nullptr && n != 0);

    int *dp = (int *)malloc(sizeof(int) * n);
    int max = 1;
    dp[0] = arr[0];

    for (int i = 1; i < n; ++i) {
        if (arr[i] > dp[max - 1]) {
            dp[max++] = arr[i];
        } else {
            dp[BinarySearch(dp, max, arr[i])] = arr[i];
        }
    }

    free(dp);
    return max;
}

#endif

TEST(Array, Array_MaxLenOfIncreaseSubsequence) {
    int arr01[] = {1, 2, 3, 4, 5};
    EXPECT_EQ(5, Array_MaxLenOfIncreaseSubsequence(arr01, 5));
    int arr02[] = {2, 1, 3, 4, 5};
    EXPECT_EQ(4, Array_MaxLenOfIncreaseSubsequence(arr02, 5));
    int arr03[] = {5, 4, 3, 2, 1};
    EXPECT_EQ(1, Array_MaxLenOfIncreaseSubsequence(arr03, 5));
    int arr04[] = {2, 1, 3, 5, 4};
    EXPECT_EQ(3, Array_MaxLenOfIncreaseSubsequence(arr04, 5));
    int arr05[] = {7};
    EXPECT_EQ(1, Array_MaxLenOfIncreaseSubsequence(arr05, 1));
}