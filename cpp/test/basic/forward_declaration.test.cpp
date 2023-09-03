//
// Created by xy on 23-9-9.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

/**
 * 前向引用声明
 * 1. 可以定义指针或引用
 * 2. 不能用作成员变量
 * 3. 可以作为函数的参数或返回值, 但不能内联. 函数的实现需要写在补全声明后
 */
namespace ForwardDeclaration {

    class Foo;

    class Bar {
    public:
        // incorrect: Field has incomplete type 'ForwardDeclaration::Foo'
//        Foo foo1;
        // correct
        Foo *foo2;
        Foo &foo3;

        Bar(Foo *foo2, Foo &foo3) : foo2(foo2), foo3(foo3) {}

        // incorrect: Field has incomplete type 'ForwardDeclaration::Foo'
//        void foo_function1(Foo foo) {};
//        Foo foo_function2() {}

        // correct
        void foo_function1(Foo foo);

        Foo foo_function2();

    };

    // incorrect, 写在Foo类之前
//    void Bar::foo_function1(Foo foo) {}
//    Foo Bar::foo_function2() {}

    class Foo {
    public:
        void bar_function(Bar bar) {
        }
    };

    // correct, 写在Foo类之后
    void Bar::foo_function1(Foo foo) {}

    Foo Bar::foo_function2() {}


    TEST(forward_declaration, forward_declaration) {
        Foo foo;
        Foo *foo_ptr = &foo;
        Foo &foo_ref = foo;
        Bar bar(foo_ptr, foo_ref);

        foo.bar_function(bar);
        bar.foo_function1(foo);
        bar.foo_function2();
    }

}

