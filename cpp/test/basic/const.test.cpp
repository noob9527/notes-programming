//
// Created by xy on 23-9-9.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace ConstSample {

    /**
     * case 1:
     *
     * - int const *ptr1 = &foo;
     * - const int *ptr2 = &foo;
     *
     * 指针指向的数据不能使用该指针来修改，但指针可以修改为指向其他变量
     */
    TEST(const, case1) {
        int foo = 1;
        int bar = 2;

        int const *ptr1 = &foo;
        const int *ptr2 = &foo;

        // incorrect
//    *ptr1 = 2;
//    *ptr2 = 2;
        // correct
        ptr1 = &bar;
        ptr2 = &bar;

        EXPECT_EQ(*ptr1, 2);
        EXPECT_EQ(*ptr2, 2);
    }

    /**
     * case 2:
     * 指针指向的数据可以使用该指针来修改，但指针不能修改为指向其他变量
     */
    TEST(const, case2) {
        int foo = 1;
        int bar = 2;

        int *const ptr2 = &foo;

        // incorrect
//    ptr2 = &bar;
        // correct
        *ptr2 = 2;

        EXPECT_EQ(*ptr2, 2);
    }

    /**
     * case 3:
     * 指针指向的数据不能使用该指针来修改，且指针不能修改为指向其他变量
     */
    TEST(const, case3) {
        int foo = 1;
        int bar = 2;

        int const *const ptr3 = &foo;

        // incorrect
//    ptr3 = &bar;
//    *ptr3 = 2;
    }
}

namespace ConstMemberFunctionSample {
    // incorrect: Non-member function cannot have 'const' qualifier
//    void func1() const { }

    class Sample {
    public:
        void func() {
            cout << "func is called" << endl;
        }
        void func() const {
            cout << "func(const) is called" << endl;
        }
    };


    TEST(const_function, basic) {
        Sample sample1;
        const Sample sample2;
        sample1.func();
        sample2.func();

        cout << "-----------------------------------------" << endl;

        Sample const *sample1_ptr1 = &sample1;
        Sample *const sample1_ptr2 = &sample1;
        Sample const *const sample1_ptr3 = &sample1;

        sample1_ptr1->func();
        sample1_ptr2->func();
        sample1_ptr3->func();

        cout << "-----------------------------------------" << endl;

        Sample const *sample2_ptr1 = &sample2;
        // incorrect: Cannot initialize a variable of type 'ConstFunctionSample::Sample *const' with an rvalue of type 'const ConstFunctionSample::Sample *'
        // why?
//        Sample *const sample2_ptr2 = &sample2;
        Sample const *const sample2_ptr3 = &sample2;

        sample2_ptr1->func();
//        sample2_ptr2->func();
        sample2_ptr3->func();

    }

}

