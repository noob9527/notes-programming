//
// Created by xy on 23-9-9.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;


/**
 * static_cast 类型转换
 */
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
TEST(static_cast, basic) {
    double raw = 111.1;
    int res1 = static_cast<int>(raw);
    int res2 = (int) raw;   //
    int res3 = int(raw);    //
    int res4 = raw;         // auto conversion
    cout << res1 << endl;
    cout << res2 << endl;
    cout << res3 << endl;
    cout << res4 << endl;
}

#pragma clang diagnostic pop
