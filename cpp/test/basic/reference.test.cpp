//
// Created by xy on 23-9-9.
//
#include <iostream>
#include "gtest/gtest.h"

using namespace std;

/**
 * 引用
 */
TEST(reference, basic) {
    int foo = 10;
    int &foo_ref = foo;

    EXPECT_EQ(foo, 10);
    EXPECT_EQ(foo_ref, 10);

    foo_ref = foo + 1;

    cout << "foo: " << foo << endl;
    cout << "foo_ref: " << foo_ref << endl;

    EXPECT_EQ(foo, 11);
    EXPECT_EQ(foo_ref, 11);
}

/**
 * 引用的指针
 */
TEST(reference, pointer_of_reference) {
    int foo = 10;
    int &foo_ref = foo;
    int *ptr1 = &foo;
    int *ptr2 = &foo_ref;

    cout << "ptr1: " << ptr1 << endl;
    cout << "ptr2: " << ptr2 << endl;
    cout << "*ptr1: " << *ptr1 << endl;
    cout << "*ptr2: " << *ptr2 << endl;

    EXPECT_EQ(ptr1, ptr2);
    EXPECT_EQ(*ptr1, *ptr2);
}

/**
 * 引用变量的常量引用，以及使用 const_const 得到变量引用
 */
TEST(reference, const_reference_variable) {
    int foo = 10;
    const int &foo_const_ref = foo;

    // incorrect
//    foo_const_ref = foo + 1;

    // undo const
    int &foo_ref1 = const_cast<int &>(foo_const_ref);
    int &foo_ref2 = (int &) foo_const_ref;

    foo_ref1++;
    foo_ref2++;

    cout << "foo: " << foo << endl;
    cout << "foo_const_ref: " << foo_const_ref << endl;
    cout << "foo_ref1: " << foo_ref1 << endl;
    cout << "foo_ref2: " << foo_ref2 << endl;

    EXPECT_EQ(foo, 12);
    EXPECT_EQ(foo, foo_const_ref);
    EXPECT_EQ(foo, foo_ref1);
    EXPECT_EQ(foo, foo_ref2);
}

/**
 * 引用常量的常量引用，在使用 const_cast 得到变量引用后，变量本身依然不可变
 * 究极槽点!
 */
TEST(reference, const_reference_const) {
    const int foo = 10;

    // incorrect: Non-const lvalue reference to type 'int' cannot bind to a temporary of type 'const int *'
//    int &foo_ref = &foo;

    const int &foo_const_ref = foo;

    // incorrect: Cannot assign to variable 'foo_const_ref' with const-qualified type 'const int &'
//    foo_const_ref = foo + 1;

    // undo const
    int &foo_ref1 = const_cast<int&>(foo_const_ref);
    int &foo_ref2 = (int&)foo_const_ref;

    foo_ref1++;
    foo_ref2++;

    cout << "&foo: " << &foo << endl;
    cout << "&foo_const_ref: " << &foo_const_ref << endl;
    cout << "&foo_ref1: " << &foo_ref1 << endl;
    cout << "&foo_ref2: " << &foo_ref2 << endl;

    EXPECT_EQ(&foo, &foo_const_ref);
    EXPECT_EQ(&foo, &foo_ref1);
    EXPECT_EQ(&foo, &foo_ref2);

    cout << "foo: " << foo << endl;
    cout << "foo_const_ref: " << foo_const_ref << endl;
    cout << "foo_ref1: " << foo_ref1 << endl;
    cout << "foo_ref2: " << foo_ref2 << endl;

    EXPECT_EQ(foo, foo_const_ref);
    EXPECT_EQ(foo, foo_ref1);
    EXPECT_EQ(foo, foo_ref2);

    EXPECT_FALSE(foo == 12);
    // 不知道为什么, foo == 12 是false, 但这里依然能通过
    EXPECT_EQ(foo, 12);

}
