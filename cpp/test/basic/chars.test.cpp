//
// Created by xy on 18-3-11.
//

#include <string.h>
#include <math.h>
#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace CharsSample {
    /**
     * char: 以数值形式存储
     */
    TEST(char, compare_str_and_int_1) {
        EXPECT_EQ('A', 65);
    }

    /**
     * 定义字符串的方式与定义字符数组类似，
     * 使用双引号初始化，会自动在字符数组末尾追加 '\0'
     */
    TEST(char, declare) {
        char str1[] = "foo";
        char str2[] = {'f', 'o', 'o', '\0'};
        for (int i = 0; i < sizeof(str1); i++) {
            EXPECT_EQ(str1[i], str2[i]);
        }
    }

    /**
     * 字符串会自动连接
     */
    TEST(char, combination) {
        EXPECT_STREQ("foo" "bar", "foobar");
    }
}

namespace lengthOfString {
    /**
     * strlen函数以字符为单位给出字符串长度，但不会计算末尾的空字符(\0)
     */
    TEST(string, strlen) {
        EXPECT_EQ(sizeof("foo"), 4);
        EXPECT_EQ(strlen("foo"), 3);
    }

    TEST(string, length_of_char_array1) {
        char str1[] = "hello";
        char *str2 = str1;

        cout << "str1: " << str1 << endl;
        cout << "str2: " << str2 << endl;
        cout << "sizeof(str1): " << sizeof(str1) << endl;
        cout << "sizeof(str2): " << sizeof(str2) << endl;
        cout << "strlen(str1): " << strlen(str1) << endl;
        cout << "strlen(str2): " << strlen(str2) << endl;

        EXPECT_EQ(sizeof(str1), 6);  // sizeof(array variable) return the size of the array, not the size of the string
        EXPECT_EQ(sizeof(str2), 8);  // sizeof(pointer) return the size of the pointer, not the size of the string
        EXPECT_EQ(strlen(str1), 5);  // strlen() always return the size of the string
        EXPECT_EQ(strlen(str2), 5);
    }

    TEST(string, length_of_char_array2) {
        char str1[20] = {'f', 'o', 'o', '\0'};
        char *str2 = str1;

        cout << "str1: " << str1 << endl;
        cout << "str2: " << str2 << endl;
        cout << "sizeof(str1): " << sizeof(str1) << endl;
        cout << "sizeof(str2): " << sizeof(str2) << endl;
        cout << "strlen(str1): " << strlen(str1) << endl;
        cout << "strlen(str2): " << strlen(str2) << endl;

        EXPECT_EQ(sizeof(str1), 20);  // sizeof(array variable) return the size of the array, not the size of the string
        EXPECT_EQ(sizeof(str2), 8);  // sizeof(pointer) return the size of the pointer, not the size of the string
        EXPECT_EQ(strlen(str1), 3);  // strlen() always return the size of the string
        EXPECT_EQ(strlen(str2), 3);
    }
}

namespace PointerOfCharArray {
    /**
     * There's an overload of operator<< for char*,
     * that tries to print the nul-terminated string that it thinks your pointer points
     * to the first character of.
     *
     * https://cplusplus.com/forum/beginner/32886/
     * https://stackoverflow.com/questions/9519749/how-do-i-get-the-address-of-elements-in-a-char-array
     */
    TEST(char, pointer_of_char_array) {
        int arr1[] = {1, 2, 3};
        int *arr1_ptr = arr1;
        char arr2[] = "foo";
        char *arr2_ptr = arr2;

        cout << "arr1: " << arr1 << endl;
        cout << "arr1_ptr: " << arr1_ptr << endl;
        cout << "&arr1[0]: " << &arr1[0] << endl;
        cout << "*arr1_ptr: " << *arr1_ptr << endl;
        cout << "*(arr1_ptr + 1): " << *(arr1_ptr + 1) << endl;
        cout << "&arr1_ptr: " << &arr1_ptr << endl;

        cout << "arr2: " << arr2 << endl;
        cout << "arr2_ptr: " << arr2_ptr << endl;
        cout << "&arr2[0]: " << &arr2[0] << endl;  // output "foo", I guess that's because the overload of '<<' operator
        cout << "*arr2_ptr: " << *arr2_ptr << endl;
        cout << "*(arr2_ptr + 1): " << *(arr2_ptr + 1) << endl;
        cout << "&arr2_ptr: " << &arr2_ptr << endl;
    }

    TEST(char, address_of_char_array) {
        char arr1[20] = "foo";
        char *arr1_ptr = arr1;

        cout << "arr1: " << arr1 << endl;   // "foo"
        cout << "&arr1: " << &arr1 << endl;
        cout << "&arr1[0]: " << &arr1[0] << endl;  // "foo"
        cout << "(int *)arr1: " << (int *) arr1 << endl;
        cout << "(void *)arr1: " << (void *) arr1 << endl;
        cout << "(int *)&arr1[0]: " << (int *) &arr1[0] << endl;
        cout << "(void *)&arr1[0]: " << (void *) &arr1[0] << endl;

        cout << "arr1_ptr: " << arr1_ptr << endl;   // "foo"
        cout << "(void *)arr1_ptr: " << (void *) arr1_ptr << endl;
        cout << "*arr1_ptr: " << *arr1_ptr << endl;  // "f"
        cout << "&arr1_ptr: " << &arr1_ptr << endl;  // I think this is the address of the pointer variable

        cout << "*(arr1_ptr + 1): " << *(arr1_ptr + 1) << endl;     // 'o'
        cout << "*(&arr1_ptr + 1): " << *(&arr1_ptr + 1) << endl;  // meaningless

        EXPECT_EQ(arr1_ptr, arr1);
        EXPECT_EQ((void *) arr1_ptr, &arr1);

        // WTF! why these two equals?
        EXPECT_EQ((void *) &arr1, (void *) arr1);
        EXPECT_TRUE((void *) &arr1 == arr1);
    }

    /**
     * I don't understand
     */
    TEST(char, address_of_array) {
        int arr2[] = {1, 2, 3};
        cout << "&arr2: " << &arr2 << endl;
        cout << "(void *)arr2: " << (void *) arr2 << endl;
        EXPECT_EQ((void *) &arr2, (void *) arr2);
    }

}

namespace ImplicitCharToBool {
    /**
     * char: '\0' == 0
     */
    TEST(char, compare_str_and_int_2) {
        bool b = '\0' == 0;
        cout << b << endl;
        EXPECT_TRUE('\0' == 0);
        EXPECT_EQ('\0', 0);
        EXPECT_TRUE(b);
    }

    /**
     * 所有的非零值都被认为是真
     *
     * 由于 '\0' == 0, 所以 '\0' 是假
     */
    TEST(char, implicitConvertToBoolean) {
        int res = 2 && -2 && 'A' && "";
        EXPECT_EQ(res, 1);
    }

    /**
     * '\0' 是 falsy 值
     */
    TEST(char, implicitConvertToBoolean2) {
        int res;
        if ('\0')
            res = 1;
        else
            res = 0;
        EXPECT_EQ(res, 0);
    }
}
