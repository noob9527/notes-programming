#include <gtest/gtest.h>
#include <iostream>

#include "example1/2018_11_B/ArrayAssign.h"

using namespace std;

TEST(ArrayAssign, basiccase)
{
    int a[] = {3, 4, 5, 6};
    int b[] = {1, 2, 3, 4};
    MulDate(a, b, 4);
    for (int i = 0; i < 4; ++i)
    {
        cout << b[i] << endl;
    }
}
