//
// Created by xy on 23-9-9.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace LocalStaticVariableSample {
    int get_and_inc() {
        // 如果未显式给出初始值,则相当于初始化为0
        static int counter;
        return counter++;
    }

    /**
     * 静态局部变量具有局部作用域,但却有全局生存期
     */
    TEST(static, local_static_var) {
        // incorrect, counter 是局部作用域
//        int res = counter
        int res1 = get_and_inc();
        int res2 = get_and_inc();
        cout << res1 << endl;
        cout << res2 << endl;

        EXPECT_EQ(res1, 0);
        EXPECT_EQ(res2, 1);
    }
}

namespace ClassStaticSample {
    class Sample {
    public:
        // incorrect: Non-const static data member must be initialized out of line
        // 不能在类体内给静态变量赋初值
//        static int static_number1 = 0;
        // 可以在类体内给静态常量赋初值
        static const int static_number2 = 2;

        static int static_number3;
        static const int static_number4;
    };

    // incorrect: 应该使用 "::" 而不是 "." 来引用类的静态变量
//    Base.static_number3 = 0;
    // incorrect: 赋值的前面需要加类型
//    Base::static_number3 = 0;
    // incorrect: 赋初值的时候前面不能加 static 关键字
//    static int Base::static_number3 = 0;
    // correct
    int Sample::static_number3 = 3;

    // incorrect: 如果定义时前面有 const, 赋值的时候也要有
//    int Base::static_number4 = 0;
    // correct
    const int Sample::static_number4 = 4;

    TEST(static, class_static_sample) {
        Sample sample;

        // incorrect: 应该使用 "::" 而不是 "." 来引用类的静态变量
//        cout << Sample.static_number2 << endl;
        // correct
        cout << Sample::static_number2 << endl;
        // incorrect: 应该使用 "." 而不是 "::" 来引用实例的静态变量
//        cout << sample::static_number2 << endl;
        // correct
        cout << sample.static_number2 << endl;
    }
}

namespace ClassDeriveStaticSample {

    class Base {
    public:
        static int static_number4;
    };

    int Base::static_number4 = 0;

    class Child : public Base {
    };

    // 派生静态成员变量时, 父类,子类,父对象,子对象共享同一变量
    TEST(static, class_derive_static_sample) {
        Base base;
        Child child;

        cout << Base::static_number4 << endl;
        cout << base.static_number4 << endl;
        cout << Child::static_number4 << endl;
        cout << child.static_number4 << endl;

        EXPECT_EQ(Base::static_number4, 0);
        EXPECT_EQ(base.static_number4, 0);
        EXPECT_EQ(Child::static_number4, 0);
        EXPECT_EQ(child.static_number4, 0);

        Base::static_number4++;

        cout << Base::static_number4 << endl;
        cout << base.static_number4 << endl;
        cout << Child::static_number4 << endl;
        cout << child.static_number4 << endl;
        cout << &Base::static_number4 << endl;
        cout << &base.static_number4 << endl;
        cout << &Child::static_number4 << endl;
        cout << &child.static_number4 << endl;

        EXPECT_EQ(Base::static_number4, 1);
        EXPECT_EQ(base.static_number4, 1);
        EXPECT_EQ(Child::static_number4, 1);
        EXPECT_EQ(child.static_number4, 1);
    }


}
