//
// Created by xy on 18-3-11.
//

#include <string.h>
#include <math.h>
#include <iostream>
#include "gtest/gtest.h"

using namespace std;

/**
 * 槽点：
 * 1. string 类型的变量不等同于 string 字面量
 *   e.g. string a = "a";   // 但 a 变量与 "a" 行为不同
 * 2. string + int 不会报错，但是输出 random 字符串
 */
namespace StringSample
{
    TEST(string, switchCaseToUpper)
    {
        cout << "'a'-32: " << 'a' - 32 << endl;
        cout << "std::toupper('a'): " << std::toupper('a') << endl;
    }

    TEST(string, switchCaseToLower)
    {
        cout << "'A'+32: " << 'A' + 32 << endl;
        cout << "std::tolower('A'): " << std::tolower('A') << endl;
    }

    TEST(string, concat_1)
    {
        string foo = "foo";
        string bar = "bar";

        cout << foo + bar << endl;
        cout << "foo" + bar << endl;
        cout << foo + "bar" << endl;
        EXPECT_EQ(foo + bar, "foobar");
        EXPECT_EQ("foo" + bar, "foobar");
        EXPECT_EQ(foo + "bar", "foobar");
    }

    /**
     * string 类型的变量不等同于 string 字面量
     * string + int 不会报错，但是输出 random 字符串
     */
    TEST(string, concat_2)
    {
        string foo = "foo";
        string bar = "bar";
        bar += 40;

        // output arbitrary string, in this case, output "ar""
        cout << "foo" + 40 << endl;
        // incorrect
        // cout << bar + 40 << endl;
        // output arbitrary string, in this case, output "bar("
        cout << bar << endl;
        EXPECT_NE("foo" + 40, "foo40");
        EXPECT_NE(bar, "bar40");
    }

    TEST(string, concat_3)
    {
        cout << "ab" "cd" << endl;
    }
}
