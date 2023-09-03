//
// Created by xy on 23-9-9.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

/**
 * 使用 new 动态分配内存
 *
 * 使用 `new Type;` 动态分配大小为 sizeof(T) 的内存空间
 * 返回该内存空间的起始指针
 */
TEST(new, basic) {
    int *ptr;
    ptr = new int;
    *ptr = 1;

    EXPECT_EQ(*ptr, 1);
}

/**
 * 使用 new 分配任意大小的数组
 *
 * 使用 `pointer = new Type[ｎ];` 动态分配大小为 n * sizeof(T) 的内存空间
 * 返回该内存空间的起始指针
 */
TEST(new, array) {
    int i = 2;
    int *ptr;
    ptr = new int[i * 5];  // 分配 10 个元素的 int 数组
    cout << "ptr: ";
    for (int j = 0; j < 10; ++j) {
        cout << ptr[j] << ", ";
    }
    cout << endl;
}

/**
 * 使用 delete 释放动态分配的内存
 */
#pragma clang diagnostic push
#pragma ide diagnostic ignored "DanglingPointer"
TEST(delete, basic) {
    int *ptr;
    ptr = new int;
    *ptr = 1;
    cout << ptr << endl;
    delete ptr;
    cout << ptr << endl;
}

#pragma clang diagnostic pop

/**
 * 使用 delete 释放数组
 */
#pragma clang diagnostic push
#pragma ide diagnostic ignored "DanglingPointer"
TEST(delete, delete_array) {
    int *ptr;
    ptr = new int[10];
    cout << ptr << endl;
    delete[]ptr;
    cout << ptr << endl;
}

#pragma clang diagnostic pop

/**
 * 使用 delete 释放非动态分配的内存
 * 会导致 RunTime Error
 */
TEST(delete, delete_runtime_error) {
    int foo = 1;
    int *ptr = &foo;

    cout << ptr << endl;

    // incorrect Signal: SIGSEGV (Segmentation fault)
//    delete ptr;
}
