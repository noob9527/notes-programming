//
// Created by xy on 18-3-11.
//

#include <string.h>
#include <math.h>
#include "gtest/gtest.h"

/**
 * 使用前缀0表示8进制数
 */
TEST(number, octal) {
    EXPECT_EQ(8, 010);
}

/**
 * 使用前缀0x或0X表示16进制数
 */
TEST(number, hexadecimal) {
    EXPECT_EQ(0X10, 0x10);
    EXPECT_EQ(16, 0x10);
}

/**
 * 常见的数字字面量
 */
TEST(number, suffix) {
    // long
    EXPECT_EQ(1l, 1L);
    // float
    EXPECT_EQ(1.0f, 1.0F);
}

/**
 * 比较浮点数的常见方式
 * fabs 取浮点数的绝对值
 */
TEST(double, compare) {
    double res = 3. * 1 / 3;
    EXPECT_TRUE(fabs(res - 1) < 0.0001);
}

/**
 * char: 以数值形式存储
 */
TEST(char, compare_str_and_int_1) {
    EXPECT_EQ('A', 65);
}

/**
 * char: '\0' == 0
 */
TEST(char, compare_str_and_int_2) {
    EXPECT_EQ('\0', 0);
}

/**
 * _Bool 也是整数类型
 */
TEST(_Bool, _Bool) {
    EXPECT_EQ(true, 1);
    EXPECT_EQ(false, 0);
}

/**
 * 所有的非零值都被认为是真
 *
 * 由于 '\0' == 0, 所以 '\0' 是假
 */
TEST(_Bool, implicitConvertToBoolean) {
    int res = 2 && -2 && 'A' && "";
    EXPECT_EQ(res, 1);
}

/**
 * '\0' 是 falsy 值
 */
TEST(_Bool, implicitConvertToBoolean2) {
    int res;
    if('\0')
        res = 1;
    else
        res = 0;
    EXPECT_EQ(res, 0);
}

/**
 * sizeof函数可以运用于类型和其具体量
 */
TEST(primitive, sizeof) {
    EXPECT_EQ(sizeof(char), 1);
    EXPECT_EQ(sizeof("foo"), 4);
}

/**
 * 定义字符串的方式与定义字符数组类似，
 * 使用双引号初始化，会自动在字符数组末尾追加 '\0'
 */
TEST(string, declare) {
    char str1[] = "foo";
    char str2[] = {'f', 'o', 'o', '\0'};
    for (int i = 0; i < sizeof(str1); i++) {
        EXPECT_EQ(str1[i], str2[i]);
    }
}

/**
 * strlen函数以字符为单位给出字符串长度，但不会计算末尾的空字符(\0)
 */
TEST(string, strlen) {
    EXPECT_EQ(sizeof("foo") - 1, strlen("foo"));
}

/**
 * 字符串会自动连接
 */
TEST(string, combination) {
    EXPECT_STREQ("foo" "bar", "foobar");
}

