//
// Created by xy on 23-9-9.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace ConstructorExample {

    class Base1 {
    private:
        int arg1;
    public:
        Base1(int arg1) : arg1(arg1) {}
    };

    class Child1 : public Base1 {
    };

    class Child2 : public Base1 {
    public:
        // incorrect: Constructor for 'ConstructorExample::Child2' must explicitly initialize the base class 'ConstructorExample::Base1' which does not have a default constructo
//        Child2(int arg1) {}
        // correct
        Child2(int arg1) : Base1(arg1) {}
    };

    /**
     * 如果父类没有无参构造函数, 则子类构造函数必须显式初始化父类
     */
    TEST(constructor, constructor_sample) {
        // incorrect
//        Child1 child1;
        // correct
        Child2 child2(1);
    }

}
