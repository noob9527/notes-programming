/**
 * 1、编写一个选择排序用于排序数组A[n+1]，
 * 从A[1]到A[n]这个区间中选出一个最大的和第一个做交换，
 * 从A[1]到A[n]中选出一个最小的和最后一个做交换，
 * 直到该区间缩小至只剩一个元素。
 */

#ifndef C_TWOWAYSELECTIONSORT_H
#define C_TWOWAYSELECTIONSORT_H

// arr length should be n+1
void TwoWaySelectionSort(int arr[], int n);

void printIntArray(int arr[], int size);

#endif //C_TWOWAYSELECTIONSORT_H
