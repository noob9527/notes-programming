//
// Created by xy on 23-9-9.
//
#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace ArraySample {

    /**
     * init an array
     */
    TEST(array, default_initialize_to_0) {
        int a[3] = {1};
        EXPECT_EQ(a[0], 1);
        // be initialized to 0
        EXPECT_EQ(a[1], 0);
        EXPECT_EQ(a[2], 0);

        // index out of bound, may print a random value
        cout << a[3] << endl;
    }

    /**
     * use pointer arithmetic to get index
     */
    TEST(array, pointer_to_index_1) {
        int a[3] = {1, 2};
        cout << "a: " << a << endl;
        cout << "*a: " << *a << endl;
        cout << "*(a + 1): " << *(a + 1) << endl;

        EXPECT_EQ(*a, a[0]);
        EXPECT_EQ(*(a + 1), a[1]);
    }

}
