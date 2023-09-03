//
// Created by xy on 23-9-9.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace VirtualSample {
    class Base {
    public:
        string getName1();

        virtual string getName2();

        string getName3() {
            return "Base::getName3";
        };

        /**
         * virtual inline function
         * 只有使用基类对象调用该函数时,才能被内联
         * 使用父类指针或引用调用该函数时,不能被内联
         *
         * By default, all the functions defined inside the class are implicitly or automatically
         * considered as inline except virtual functions.
         *
         * Whenever a virtual function is called using base class reference or pointer it cannot be inlined,
         * but whenever called using the object without reference or pointer of that class,
         * can be inlined because the compiler knows the exact class of the object at compile time.
         * @return
         */
        virtual string getName4() {
            return "Base::getName4";
        }

        // incorrect:
        // 'virtual' can only appear on non-static member functions
//        virtual static string getName5() {
//            return "Base::getName5";
//        }
    };

    string Base::getName1() {
        return "Base::getName1";
    }

    string Base::getName2() {
        return "Base::getName2";
    }

    class Child : public Base {
    public:
        virtual string getName1();

        string getName2();

        virtual string getName3();

        string getName4();
    };

    string Child::getName1() {
        return "Child::getName1";
    }

    string Child::getName2() {
        return "Child::getName2";
    }

    string Child::getName3() {
        return "Child::getName3";
    }

    string Child::getName4() {
        return "Child::getName4";
    }

    class GrandChild : public Child {
    public:
        string getName1();

        string getName2();

        string getName3();

        string getName4();
    };

    string GrandChild::getName1() {
        return "GrandChild::getName1";
    }

    string GrandChild::getName2() {
        return "GrandChild::getName2";
    }

    string GrandChild::getName3() {
        return "GrandChild::getName3";
    }

    string GrandChild::getName4() {
        return "GrandChild::getName4";
    }

    /**
     * 使用对象调用时, 没有多态
     */
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-slicing"
    TEST(virtual, use_object_to_call_function) {
        Base base1;
        Child child;
        // 赋值兼容规则, 派生类对象可以赋值给基类对象
        base1 = child;
        Base base2 = Child();
        cout << base1.getName1() << endl;
        cout << base1.getName2() << endl;
        cout << base1.getName3() << endl;
        cout << base1.getName4() << endl;
        cout << base2.getName1() << endl;
        cout << base2.getName2() << endl;
        cout << base2.getName3() << endl;
        cout << base2.getName4() << endl;
        EXPECT_EQ(base1.getName1(), "Base::getName1");
        EXPECT_EQ(base1.getName2(), "Base::getName2");
        EXPECT_EQ(base1.getName3(), "Base::getName3");
        EXPECT_EQ(base1.getName4(), "Base::getName4");

        EXPECT_EQ(base2.getName1(), "Base::getName1");
        EXPECT_EQ(base2.getName2(), "Base::getName2");
        EXPECT_EQ(base2.getName3(), "Base::getName3");
        EXPECT_EQ(base2.getName4(), "Base::getName4");
    }

#pragma clang diagnostic pop

    /**
     * 使用基类指针调用函数, virtual 函数有多态
     */
    TEST(virtual, use_pointer_to_call_function) {
        Child child;
        // 使用基类指针
        Base *base2 = &child;
        cout << base2->getName1() << endl;
        cout << base2->getName2() << endl;
        cout << base2->getName3() << endl;
        cout << base2->getName4() << endl;
        EXPECT_EQ(base2->getName1(), "Base::getName1");
        EXPECT_EQ(base2->getName2(), "Child::getName2");
        EXPECT_EQ(base2->getName3(), "Base::getName3");
        EXPECT_EQ(base2->getName4(), "Child::getName4");
    }

    /**
     * 使用基类引用调用函数, virtual 函数有多态
     */
    TEST(virtual, use_reference_to_call_function) {
        Child child;
        // 使用基类引用
        Base &base3 = child;
        cout << base3.getName1() << endl;
        cout << base3.getName2() << endl;
        cout << base3.getName3() << endl;
        cout << base3.getName4() << endl;
        EXPECT_EQ(base3.getName1(), "Base::getName1");
        EXPECT_EQ(base3.getName2(), "Child::getName2");
        EXPECT_EQ(base3.getName3(), "Base::getName3");
        EXPECT_EQ(base3.getName4(), "Child::getName4");
    }

    /**
     * 多层次继承
     * 如果基类定义为虚函数
     * 子类覆写函数时无论有没有 virtual 关键字, 都是虚函数
     * 如果基类定义不是虚函数
     * 子类覆写函数时无论有没有 virtual 关键字, 都不是虚函数
     */
    TEST(virtual, deep_virtual_function) {
        GrandChild grandChild;
        // 使用基类引用
        Base &base3 = grandChild;
        cout << base3.getName1() << endl;
        cout << base3.getName2() << endl;
        cout << base3.getName3() << endl;
        cout << base3.getName4() << endl;
        EXPECT_EQ(base3.getName1(), "Base::getName1");
        EXPECT_EQ(base3.getName2(), "GrandChild::getName2");
        EXPECT_EQ(base3.getName3(), "Base::getName3");
        EXPECT_EQ(base3.getName4(), "GrandChild::getName4");
    }
}

namespace VirtualDestructorSample {
    class Base1 {
    public:
        ~Base1() {
            cout << "Base1 destructor" << endl;
        }
    };

    class Base2 {
    public:
        virtual ~Base2() {
            cout << "Base2 destructor" << endl;
        }
    };

    class Child1 : public Base1 {
        ~Child1() {
            cout << "Child1 destructor" << endl;
        }
    };

    class Child2 : public Base2 {
        /**
         * 如果一个类的析构函数是虚函数, 则其子类的析构函数也是虚函数
         */
        ~Child2() {
            cout << "Child2 destructor" << endl;
        }
    };

    TEST(virtual, virtual_destructor) {
        Base1 *base1 = new Child1();
        Base2 *base2 = new Child2();
        delete base1;  // only call Base destructor
        delete base2;  // call Child2 destructor, then Base2 destructor
    }
}

namespace PureVirtualFunctionSample {
    class AbstractBase {
        virtual string virtualFun() {
            return "AbstractBase::virtualFun";
        }

        virtual string pureVirtualFun1() = 0;

        virtual string pureVirtualFun2() = 0;
    };

    class AbstractChild : public AbstractBase {
        string pureVirtualFun1() {
            return "AbstractChild::pureVirtualFun1";
        }
    };

    /**
     * all pure virtual functions are implemented
     */
    class GrandChild : public AbstractChild {
        string pureVirtualFun2() {
            return "AbstractGrandChild::pureVirtualFun2";
        }
    };

    TEST(virtual, pure_virtual_function) {
        // incorrect: Variable type 'PureVirtualFunctionSample::AbstractBase' is an abstract class
//        AbstractBase abstractBase;
//        AbstractChild abstractChild;
        // correct
        GrandChild abstractGrandChild;
    }
}

namespace VirtualBaseClassSample {
    class Base {
    public:
        string getBaseName() {
            return "Base";
        }
    };

    class Child1 : public Base {
    public:
        string getChild1Name() {
            return "Child1";
        }
    };

    class Child2 : public Base {
    public:
        string getChild2Name() {
            return "Child2";
        }
    };

    class Child3 : virtual public Base {
    };

    class Child4 : virtual public Base {
    };

    class GrandChild1 : public Child1, public Child2 {
    public:
        string getGrandChild1Name() {
            return "GrandChild1";
        }
    };

    class GrandChild2 : public Child3, public Child4 {
    };

    TEST(virtual, virtal_base_class) {
        GrandChild1 grandChild1;
        GrandChild2 grandChild2;
        // incorrect: Non-static member 'getBaseName' found in multiple base-class subobjects of type 'VirtualBaseClassSample::Base':
//        cout << grandChild1.getBaseName() << endl;
        // incorrect: Ambiguous conversion from derived class 'VirtualBaseClassSample::GrandChild' to base class 'VirtualBaseClassSample::Base':
//        cout << grandChild1.Base::getBaseName() << endl;

        // correct
        cout << grandChild1.getChild1Name() << endl;
        cout << grandChild1.getChild2Name() << endl;
        cout << grandChild1.getGrandChild1Name() << endl;

        cout << grandChild2.getBaseName() << endl;
        cout << grandChild2.Base::getBaseName() << endl;
    }
}
