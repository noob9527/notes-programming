#include <gtest/gtest.h>

#include "example1/2018_11_A/MyClass.h"

using namespace std;
using namespace Q_2018_11_A;


TEST(MyClass, defaultCtor)
{
    MyClass myClass;
}

TEST(MyClass, display)
{
    MyClass myClass(2, 5);
    display(myClass);
}

TEST(YourClass, sum)
{
    YourClass yourClass(1, 2, 3);
    display(yourClass);
    cout << yourClass.sum() << endl;
}
