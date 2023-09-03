//
// Created by xy on 23-9-9.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;


namespace ConstCastSample {

    /**
     * const_cast 用于得到常量指针和引用的可变版本
     *
     * 但如果变量本身使用 const 定义，则其在运行时依然不可变
     * 此时会出现地址相同但值不同的的情况
     */
    TEST(const_cast, basic) {
        int foo = 10;
        const int *foo_ptr = &foo;  // declare pointer
        const int &foo_ref = foo;   // declare ref

        int *ptr1, *ptr2;

        cout << "foo: " << foo << endl;
        cout << "&foo: " << &foo << endl;
        cout << "foo_ptr: " << foo_ptr << endl;
        cout << "*foo_ptr: " << *foo_ptr << endl;
        cout << "foo_ref: " << foo_ref << endl;

        // incorrect: Read-only variable is not assignable
//    *foo_ptr = 11;
        // incorrect: Assigning to 'int *' from 'const int *' discards qualifiers
//    ptr = foo_ptr
        // correct
        ptr1 = const_cast<int *>(foo_ptr);
        ptr2 = (int *) foo_ptr;

        cout << "----------------------- " << endl;
        *ptr1 = foo + 1;
        *ptr2 = foo + 1;
        cout << "foo: " << foo << endl;
        cout << "&foo: " << &foo << endl;
        cout << "foo_ptr: " << foo_ptr << endl;
        cout << "*foo_ptr: " << *foo_ptr << endl;
        cout << "foo_ref: " << foo_ref << endl;

        EXPECT_EQ(ptr1, foo_ptr);
        EXPECT_EQ(ptr2, foo_ptr);
        EXPECT_EQ(*ptr1, foo);
        EXPECT_EQ(*ptr2, foo);
    }

    /**
     * incredible!
     * const_cast 用于得到常量指针和引用的可变版本
     *
     * 但如果变量本身使用 const 定义，则其在运行时依然不可变
     * 此时会出现地址相同但值不同的的情况
     */
    TEST(const_cast, const_cast_with_const_variable) {
        const int bar = 20;
        const int *bar_ptr = &bar;
        const int &bar_ref = bar;

        int *ptr1, *ptr2;

        // incorrect: Read-only variable is not assignable
//    *bar_ptr = 21;
        ptr1 = const_cast<int *>(bar_ptr);
        ptr2 = (int *) bar_ptr;
        // 由于 bar 是 "const int"，下面的赋值实际上不会修改 bar 变量的值
        *ptr1 = bar + 1;
        *ptr2 = bar + 1;
        cout << "bar: " << bar << endl;
        cout << "&bar: " << &bar << endl;
        cout << "bar_ptr: " << bar_ptr << endl;
        cout << "ptr1: " << ptr1 << endl;
        cout << "ptr2: " << ptr2 << endl;
        cout << "*bar_ptr: " << *bar_ptr << endl;
        cout << "*ptr1: " << *ptr1 << endl;
        cout << "*ptr2: " << *ptr2 << endl;
        cout << "bar_ref: " << bar_ref << endl;

        EXPECT_EQ(ptr1, bar_ptr);
        EXPECT_EQ(ptr2, bar_ptr);
        EXPECT_EQ(*ptr1, bar);
        EXPECT_EQ(*ptr2, bar);

        EXPECT_EQ(bar_ptr, &bar);

        // 不知道为什么，*bar_ptr == bar 是 false，但这里依然能通过
        EXPECT_EQ(*bar_ptr, bar);

        // 离谱！！！ bar_ptr == &bar 但是 *bar_ptr != bar
        // 变量 bar 的地址与 bar_ptr, ptr1, ptr2 指向的地址相同，但是值不同
        EXPECT_TRUE(bar_ptr == &bar);
        EXPECT_FALSE(*bar_ptr == bar);
    }

    /**
     * incredible!
     */
    TEST(const_cast, const_cast_with_const_variable_2) {
        const int value = 10;
        int *ptr = (int *) &value;
        *ptr = 20;

        cout << "value: " << value << endl;
        cout << "&value: " << &value << endl;
        cout << "ptr: " << ptr << endl;
        cout << "*ptr: " << *ptr << endl;
        cout << "*ptr == value: " << (*ptr == value) << endl;

        EXPECT_EQ(ptr, &value);         // 地址相同
        EXPECT_EQ(*ptr, value);         // 值虽然不同, 但这里断言成功
        EXPECT_TRUE(ptr == &value);     // 地址相同
        EXPECT_FALSE(*ptr == value);    // 值不同
    }
}

