//
// Created by xy on 18-3-11.
//

#include <string.h>
#include <math.h>
#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace StringSample {

    TEST(string, switchCaseToUpper) {
        cout << "'a'-32: " << 'a' - 32 << endl;
        cout << "std::toupper('a'): " << std::toupper('a') << endl;
    }

    TEST(string, switchCaseToLower) {
        cout << "'A'+32: " << 'A' + 32 << endl;
        cout << "std::tolower('A'): " << std::tolower('A') << endl;
    }

}
