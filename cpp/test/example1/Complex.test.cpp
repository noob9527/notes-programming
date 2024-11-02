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
