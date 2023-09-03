//
// Created by xy on 23-9-9.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace EnclosingClassSample {

    class Foo {
    public:
        string name;

        Foo(string name) : name(name) {}
    };

    /**
     * enclosing class?
     * "如果一个类的成员变量是另一个类的对象,则为封闭类"
     */
    class Bar {
    public:
        Foo foo;
        string name;

        Bar(string foo_name, string bar_name) : name(bar_name), foo(foo_name) {}
    };


    TEST(enclosing_class, enclosing_class_ctor) {
        Bar bar("foo", "bar");
        cout << bar.foo.name << endl;
        cout << bar.name << endl;
        EXPECT_EQ(bar.foo.name, "foo");
        EXPECT_EQ(bar.name, "bar");
    }

}

