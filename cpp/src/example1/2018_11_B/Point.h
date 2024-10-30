/**
* 一、按要求编写程序，程序要求如下：。
* 1）定义类 Point，具有两个整型的私有数据成员a、b：•
* 2）定义带两个参数的构造函数，将数据成员a、b分别初始化
* 为10、20：•
* 3） 定义析构函效，当释放对象时，输出提示信息：“Destructor！”）
* 4） 为Point类定义友元函数show，该函数输出数据成员a和b
* 的值：例如：设a=10、b=20，输出格式为：
* "The value of a is 10，the value of b is 20；*
* 5）定义 Point 类的派生类 Circle，派生类新增数据成员；
* 6） Circle 类包含成员函数 Area 用于显示圆的面积。：
* 7） 编写主程序，定义类 Circle 的对象 c1，对象 c1 通过构造函
* 效设置圆心为（8.5），半径为10：计算对象c1 的面积，并将结果
* 输出。。
*/

#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <math.h>

using namespace std;

namespace Q_2018_11_B
{
    class Point
    {
        int a;
        int b;

    public:
        Point(int a = 10, int b = 20): a(a), b(b)
        {
        }

        ~Point()
        {
            cout << "Destructor!" << endl;
        }

        friend void show(Point&);
    };

    class Circle : public Point
    {
    private:
        int r;

    public:
        Circle(int a, int b, int r): Point(a, b), r(r)
        {
        }

        double Area()
        {
            double res =  M_PI * r * r;
            cout << "Area: " << res << endl;
            return res;
        }
    };
}

#endif //POINT_H
