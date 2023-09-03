//
// Created by xy on 23-9-9.
//

#include <cmath>
#include "gtest/gtest.h"

using namespace std;


/**
 * computes 2 raised to the power 10
 */
TEST(math, pow) {
    double res = pow(2, 10);
    EXPECT_EQ(res, 1024);
}
