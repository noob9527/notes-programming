//
// Created by xy on 23-9-9.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

/**
 * 一般来说，public继承是最常用的，因为它符合直观的“is-a”关系，
 * 并且允许派生类对象被用作基类对象。
 * protected和private继承则用于更特殊的场景，
 * 通常涉及到实现细节的封装和访问控制。
 * -- claude AI
 */
namespace DeriveAccessSpecifierSample {
    class Base {
    private:
        string private_name;
    protected:
        string protected_name;
    public:
        string public_name;

        static int static_number;

        Base(
                string private_name = "base.private_name",
                string protected_name = "base.protected_name",
                string public_name = "base.public_name")
                : private_name(private_name),
                  protected_name(protected_name),
                  public_name(public_name) {}
    };

    int Base::static_number = 0;

    /**
     * 不加说明时,默认的继承方式是私有继承
     */
    class PrivateChild : private Base {
    public:
        int number;

        void print_name() {
            cout << "protected_name: " << protected_name << endl;
            cout << "public_name: " << public_name << endl;
            cout << "Base::protected_name: " << Base::protected_name << endl;
            cout << "Base::public_name: " << Base::public_name << endl;
        }
    };

    class PrivateGrandChild : public PrivateChild {
        void print_name() {
            // incorrect, 由于父类通过 private 继承, Base 类中的 public, protected 成员都成了 private
//            cout << "protected_name: " << protected_name << endl;
//            cout << "public_name: " << public_name << endl;
//            cout << "Base::protected_name: " << Base::protected_name << endl;
//            cout << "Base::public_name: " << Base::public_name << endl;
//            cout << "Base::protected_name: " << PrivateChild::protected_name << endl;
//            cout << "Base::public_name: " << PrivateChild::public_name << endl;
        }
    };

    class ProtectedChild : protected Base {
    public:
        int number;

        void print_name() {
            cout << "protected_name: " << protected_name << endl;
            cout << "public_name: " << public_name << endl;
            cout << "Base::protected_name: " << Base::protected_name << endl;
            cout << "Base::public_name: " << Base::public_name << endl;
        }
    };

    class ProtectedGrandChild : public ProtectedChild {
        void print_name() {
            // 由于父类通过 protected 继承, Base 类中的 public, protected 成员都成了 protected
            cout << "protected_name: " << protected_name << endl;
            cout << "public_name: " << public_name << endl;
            cout << "Base::protected_name: " << Base::protected_name << endl;
            cout << "Base::public_name: " << Base::public_name << endl;
            cout << "Base::protected_name: " << ProtectedChild::protected_name << endl;
            cout << "Base::public_name: " << ProtectedChild::public_name << endl;
        }
    };

    class PublicChild : public Base {
    public:
        int number;

        void print_name() {
            // incorrect:
//            cout << "Base::private_name: " << Base::private_name << endl;
            cout << "Base::protected_name: " << Base::protected_name << endl;
            cout << "Base::public_name: " << Base::public_name << endl;
        }
    };

    class PublicGrandChild : public PublicChild {
        void print_name() {
            // 由于父类通过 public 继承, Base 类中的 public, protected 成员的访问属性不变
            cout << "protected_name: " << protected_name << endl;
            cout << "public_name: " << public_name << endl;
            cout << "Base::protected_name: " << Base::protected_name << endl;
            cout << "Base::public_name: " << Base::public_name << endl;
            cout << "Base::protected_name: " << PublicChild::protected_name << endl;
            cout << "Base::public_name: " << PublicChild::public_name << endl;
        }
    };

    TEST(derive, sizeof_sample) {
        cout << "sizeof(Base)" << sizeof(Base) << endl;
        cout << "sizeof(PrivateDeriveChild)" << sizeof(PrivateChild) << endl;
        cout << "sizeof(ProtectedDeriveChild)" << sizeof(ProtectedChild) << endl;
        cout << "sizeof(PublicDeriveChild)" << sizeof(PublicChild) << endl;
    }

    /**
     * 通过public继承：派生类中基类部分成员的访问说明符在基类中为public或protected的，在派生类中类型保持不变，private的成员不可访问。
     * 通过protected继承：派生类中基类部分成员的访问说明符在基类中为public或protected的，在派生类中类型为protected，private的成员不可访问。
     * 通过private继承：派生类中基类部分成员的访问说明符在基类中为public或protected的，在派生类中类型为private，private的成员不可访问。
     * 不加说明时,默认的继承方式是私有继承
     */
    TEST(derive, access_specifier) {
        Base base;
        PrivateChild privateChild;
        PrivateGrandChild privateGrandChild;
        ProtectedChild protectedChild;
        ProtectedGrandChild protectedGrandChild;
        PublicChild publicChild;
        PublicGrandChild publicGrandChild;

        // incorrect
//        privateChild.public_name;
//        privateGrandChild.public_name;
//        protectedChild.public_name;
//        protectedGrandChild.public_name;
//        publicChild.protected_name;
//        publicGrandChild.protected_name;
        // correct
        cout << publicChild.public_name << endl;
        cout << publicGrandChild.public_name << endl;

        // incorrect
//        privateDeriveChild.Base::public_name;
//        protectedDeriveChild.Base::public_name;
        // correct
        cout << publicChild.Base::public_name << endl;
        cout << publicGrandChild.Base::public_name << endl;
        cout << publicGrandChild.PublicChild::public_name << endl;
    }
}

namespace MultipleInheritanceSample {
    class Base1 {
    public:
        string name = "base1.name";
        int age = 1;
    };

    class Base2 {
    public:
        string name = "base2.name";
        int age = 2;
    };

    class Child : public Base1, public Base2 {
    public:
        string name = "child.name";
    };

    TEST(multiple_inheritance, basic_sample) {
        Child child;

        // incorrect: Member 'age' found in multiple base classes of different types
//        child.age
        // correct
        cout << child.Base1::age << endl;
        cout << child.Base2::age << endl;
        EXPECT_EQ(child.Base1::age, 1);
        EXPECT_EQ(child.Base2::age, 2);

        // correct
        cout << child.name << endl;
        cout << child.Base1::name << endl;
        cout << child.Base2::name << endl;
        EXPECT_EQ(child.name, "child.name");
        EXPECT_EQ(child.Base1::name, "base1.name");
        EXPECT_EQ(child.Base2::name, "base2.name");
    }
}
