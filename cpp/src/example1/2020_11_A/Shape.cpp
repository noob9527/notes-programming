/**
 * C++程序设计 2020.11月A卷
 * 第一题：
 *
 * Shape类有数据成员r, 虚函数perimeter周长，虚函数Area面积。
 * 派生类Circle实现周长和面积函数。
 * 析构函数输出"De..............";
 * 求半径为10的周长和面积
 */

#include <iostream>
#include <cmath>

using namespace std;

namespace Q_2020_11_A
{
    class Shape
    {
    protected:
        /* data */
        double r;

    public:
        Shape(/* args */): r(0)
        {
        }

        explicit Shape(double r): r(r)
        {
        }

        virtual double perimeter() = 0;
        virtual double area() = 0;
    };

    class Circle : public Shape
    {
    private:
        /* data */
    public:
        Circle(/* args */);

        Circle(double r): Shape(r)
        {
        }

        ~Circle();
        double perimeter();
        double area();
    };

    Circle::Circle(/* args */)
    {
    }

    Circle::~Circle()
    {
        cout << "De.............." << endl;
    }

    double Circle::perimeter()
    {
        return 2 * M_PI * r;
    }

    double Circle::area()
    {
        return M_PI * r * r;
    }
}


int main()
{
    Q_2020_11_A::Circle circle(10);
    cout << circle.perimeter() << endl;
    cout << circle.area() << endl;
    return 0;
}
