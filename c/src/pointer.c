//
// Created by xy on 18-3-11.
//
#include <stdio.h>

int test() {
    return 0;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincompatible-pointer-types-discards-qualifiers"

// void test1() {
//     int foo = 10;
//     const int *foo_ptr = &foo;
//     int *ptr1 = foo_ptr;
//     *ptr1 = 11;
//
//     printf("foo: %d\n", foo); // 11
//     printf("*ptr1: %d\n", *ptr1);  // 11
// }
//
// void test2() {
//     const int bar = 20;
//     const int *bar_ptr = &bar;
//
//     int *ptr1 = bar_ptr;
//     *ptr1 = 21;
//
//     printf("bar: %d\n", bar);  // 21
//     printf("*ptr1: %d\n", *ptr1);  // 21
// }
//
// int main(void) {
//     test1();
//     test2();
//     return 0;
// }

#pragma clang diagnostic pop

