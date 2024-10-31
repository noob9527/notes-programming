#include <gtest/gtest.h>
#include "example1/2017_10_A/TwoWaySelectionSort.h"


TEST(TwoWaySelectionSort, empty_arr) {
    int arr[0];

    TwoWaySelectionSort(arr, 0);

    printIntArray(arr, 0);
}

TEST(TwoWaySelectionSort, size1) {
    int arr[1] = {1};

    TwoWaySelectionSort(arr, 0);

    printIntArray(arr, 1);
}

TEST(TwoWaySelectionSort, size2) {
    int arr[] = {0, 1};

    TwoWaySelectionSort(arr, 1);

    printIntArray(arr, 2);
}

TEST(TwoWaySelectionSort, size3) {
    int arr[] = {0, 2, 1};

    TwoWaySelectionSort(arr, 2);

    printIntArray(arr, 3);
}

TEST(TwoWaySelectionSort, sample) {
    int arr[] = {0, 3, 4, 2, 6, 7, 5, 4, 5, 2, 1};


    TwoWaySelectionSort(arr, sizeof(arr) / sizeof(int) - 1);

    printIntArray(arr, sizeof(arr) / sizeof(int));
}
