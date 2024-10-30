#include "MyClass.h"

#include <iostream>

using namespace std;

namespace Q_2018_11_A
{
    int display(const MyClass& myClass)
    {
        const int res = myClass.x * myClass.y;
        cout << "display: " << res << endl;
        return res;
    }
}
