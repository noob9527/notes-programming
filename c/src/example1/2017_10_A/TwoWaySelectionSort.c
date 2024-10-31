/**
 * 1、编写一个选择排序用于排序数组A[n+1]，
 * 从A[1]到A[n]这个区间中选出一个最大的和第一个做交换，
 * 从A[1]到A[n]中选出一个最小的和最后一个做交换，
 * 直到该区间缩小至只剩一个元素。
 */

#include <stdio.h>
#include "TwoWaySelectionSort.h"


// arr length should be n+1
void TwoWaySelectionSort(int arr[], int n) {
    if (n <= 0) return;
    int lo = 1;
    int hi = n;

    while (lo < hi) {
        int max = lo;
        // find index with maximum value
        for (int i = lo; i <= hi; i++) {
            if (arr[i] > arr[max]) {
                max = i;
            }
        }
        // exchange index with maximum and hi
        int tmp = arr[hi];
        arr[hi] = arr[max];
        arr[max] = tmp;
        hi--;

        int min = hi;
        for (int i = hi; i >= lo; i--) {
            if (arr[i] < arr[min]) {
                min = i;
            }
        }

        // exchange index with minimum and lo
        tmp = arr[lo];
        arr[lo] = arr[min];
        arr[min] = tmp;
        lo++;
    }
}

void printIntArray(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; ++i) {
        printf("%d,", arr[i]);
    }
    printf("]");
}
