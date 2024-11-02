//
// Created by 许炎 on 2024/11/2.
//

#include <gtest/gtest.h>
#include <iostream>
#include "example1/Complex.h"

using namespace std;

TEST(Complex, ctor1)
{
    Complex complex;
    std::cout << complex.imagine << endl;
    std::cout << complex.real << endl;
}

TEST(Complex, ctor2)
{
    Complex complex(1, 2);
    std::cout << complex.real << endl;
    std::cout << complex.imagine << endl;
}

TEST(Complex, calculate1)
{
    Complex complex1(1, 1);
    Complex complex2(2, 2);
    Complex complex3 = complex1 + complex2;
    std::cout << complex3.real << endl;
    std::cout << complex3.imagine << endl;
    EXPECT_EQ(complex3.imagine, 3);
    EXPECT_EQ(complex3.real, 3);
}

TEST(Complex, assign)
{
    Complex complex1(1, 1);
    Complex complex2(2, 2);
    complex2 = complex1;
    std::cout << complex2.real << endl;
    std::cout << complex2.imagine << endl;
    EXPECT_EQ(complex2.imagine, 1);
    EXPECT_EQ(complex2.real, 1);
}
