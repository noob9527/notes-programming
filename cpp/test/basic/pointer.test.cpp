//
// Created by xy on 23-9-9.
//
#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace PointerSample {

    /**
     * As you understood pointer is an address which is a numeric value; therefore,
     * you can perform arithmetic operations on a pointer just as you can a numeric value.
     * There are four arithmetic operators that can be used on pointers: ++, --, +, and -.
     */
    TEST(pointer, pointer_arithmetic_1) {
        int a[3] = {1, 2};
        int *ptr = a;

        cout << "ptr: " << ptr << endl;
        cout << "ptr + 1: " << ptr + 1 << endl;
        cout << "ptr + 2: " << ptr + 2 << endl;
        cout << "*ptr: " << *ptr << endl;
        cout << "*(ptr + 1): " << *(ptr + 1) << endl;
        cout << "*(ptr + 2): " << *(ptr + 2) << endl;
    }

    /**
     * let us consider that ptr is an integer pointer which points to the address 1000.
     * Assuming 32-bit integers, let us perform the following arithmetic operation on the pointer
     * `ptr++` the ptr will point to the location 1004 because each time ptr is incremented,
     * it will point to the next integer. This operation will move the pointer to next memory
     * location without impacting actual value at the memory location.
     * If ptr points to a character whose address is 1000, then above operation will point to
     * the location 1001 because next character will be available at 1001.
     */
    TEST(pointer, pointer_arithmetic_2) {
        // 4 bytes
        int int_arr[4] = {1, 2};
        long long_arr[4] = {1, 2};
        char characters[4] = {'a', 'b'};

        cout << "int_arr: " << int_arr << endl;
        cout << "int_arr + 1: " << int_arr + 1 << endl;
        cout << "int_arr + 2: " << int_arr + 2 << endl;
        cout << "int_arr + 3: " << int_arr + 3 << endl;
        cout << "---------------------" << endl;

        cout << "long_arr: " << long_arr << endl;
        cout << "long_arr + 1: " << long_arr + 1 << endl;
        cout << "long_arr + 2: " << long_arr + 2 << endl;
        cout << "long_arr + 3: " << long_arr + 3 << endl;
        cout << "---------------------" << endl;

        cout << "characters: " << characters << endl;
        cout << "characters + 1: " << characters + 1 << endl;
        cout << "*(characters + 1): " << *(characters + 1) << endl;
        cout << "characters + 2: " << characters + 2 << endl;
        cout << "characters + 3: " << characters + 3 << endl;
    }

    TEST(pointer, pointer_arithmetic_3) {
        // 4 bytes
        int int_arr[4] = {1, 2};

        int *ptr1 = int_arr;
        int *ptr2 = int_arr + 1;

        cout << "ptr1: " << ptr1 << endl;
        cout << "ptr2: " << ptr2 << endl;
        cout << "ptr2 - ptr1: " << ptr2 - ptr1 << endl;

        EXPECT_EQ(ptr2 - ptr1, 1);
    }
}

namespace AccessMemberWithPointerSample {

    class Sample {
    public:
        string name;

        Sample(string name) : name(name) {}
    };

    /**
     * "->" operator
     */
    TEST(pointer, basic) {
        Sample sample("foo");
        Sample *ptr = &sample;

        cout << "sample.name: " << sample.name << endl;
        cout << "ptr -> name: " << ptr->name << endl;
        EXPECT_EQ(sample.name, "foo");
        EXPECT_EQ(ptr->name, "foo");

        ptr->name = "bar";
        cout << "sample.name: " << sample.name << endl;
        cout << "ptr -> name: " << ptr->name << endl;
        EXPECT_EQ(sample.name, "bar");
        EXPECT_EQ(ptr->name, "bar");
    }
}
