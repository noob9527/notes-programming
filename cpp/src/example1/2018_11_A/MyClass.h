/**
 * 一、按下列要求，定义类MyClass 中的数据成员和成员函数：
 *
 *    1）具有两个私有的数据成员x,y;
 *
 *    2) 具有无参的构造函数，将数据成员初始化为零，并输出表示信息："Default Constructor!";
 *
 *    3) 具有带两个参数的构造函数，初始化数据成员；
 *
 *    4）为该类定义友元函数Display,该函数计算数据成员x和y的乘积；
 *
 *    5）定义该类的派生类YourClass,新增数据成员z,成员函数显示YourClass类中的所有数据成员的和。
 */
// Method 1: #pragma once (modern, simpler)
// #pragma once

// Method 2: Traditional header guards
#ifndef MYCLASS_H
#define MYCLASS_H

#include <iostream>

namespace Q_2018_11_A
{
    class MyClass
    {
    private:
        int x;
        int y;

    public:
        MyClass(): x(0), y(0)
        {
            std::cout << "Default Constructor!" << std::endl;
        }

        MyClass(int x, int y): x(x), y(y)
        {
        }

        int getX() const
        {
            return x;
        }

        int getY()
        {
            return y;
        }

        friend int display(const MyClass&);
    };

    class YourClass : public MyClass
    {
    private:
        int z;

    public:
        YourClass(int x, int y, int z): MyClass(x, y), z(z)
        {
        }

        int sum()
        {
            return getX() + getY() + z;
        }
    };
}


#endif //MYCLASS_H
