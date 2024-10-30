//
// Created by xy on 23-9-9.
//
#include <iostream>
#include "gtest/gtest.h"

using namespace std;

/**
 * 槽点：
 * 1. 数组作为函数参数时，写的是 `int arr[]` 而不是 `int[] arr`
 * 2. 数组作为函数参数等价于指针作为函数参数，
 *  此时 sizeof 计算的是指针的大小，与数组定义时使用 sizeof 的行为不一致，
 *  这也是为什么 c++ 函数参数是数组时，需要传入数组的 size。
 */
namespace ArraySample
{
    /**
     * init an array
     */
    TEST(array, default_initialize_to_0)
    {
        int a[3] = {1};
        EXPECT_EQ(a[0], 1);
        // be initialized to 0
        EXPECT_EQ(a[1], 0);
        EXPECT_EQ(a[2], 0);

        // index out of bound, may print a random value
        cout << a[3] << endl;
    }

    /**
     * size of case 1
     */
    TEST(array, sizeof_case1)
    {
        int a[3] = {1, 2, 3};
        int b[3] = {};
        int a_size = sizeof(a) / sizeof(a[0]);
        int b_size = sizeof(b) / sizeof(b[0]);

        cout << a_size << endl;
        cout << b_size << endl;
        EXPECT_EQ(a_size, 3);
        EXPECT_EQ(b_size, 3);
    }

    /**
     * In C++, when passing arrays to functions,
     * you need to also pass the size of the array
     * because arrays decay to pointers and lose their size information
     *
     * this function will always return 2
     */
    int sizeOf(int arr[])
    {
        return sizeof(arr) / sizeof(arr[0]);
    }

    /**
     * size of case 2
     */
    TEST(array, sizeof_case2)
    {
        int a[10] = {};
        int a_size1 = sizeOf(a);
        int a_size2 = sizeof(a) / sizeof(a[0]);

        cout << a_size1 << endl;
        cout << a_size2 << endl;
        EXPECT_EQ(a_size1, 2);
        EXPECT_EQ(a_size2, 10);
    }

    /**
     * use pointer arithmetic to get index
     */
    TEST(array, pointer_to_index_1)
    {
        int a[3] = {1, 2};
        cout << "a: " << a << endl;
        cout << "*a: " << *a << endl;
        cout << "*(a + 1): " << *(a + 1) << endl;

        EXPECT_EQ(*a, a[0]);
        EXPECT_EQ(*(a + 1), a[1]);
    }
}
