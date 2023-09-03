//
// Created by xy on 23-9-9.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace FriendFunctionSample {
    // 前向引用声明
    class Sample1;

    class Sample1NamePrinter {
    public:
        // 这里不能 inline
        // Incorrect: Error: Variable has incomplete type 'FriendFunctionSample1'
//        string getName(FriendFunctionSample1 sample) {
//            return sample.name;
//        }

        string getName(Sample1 sample);
        static string static_get_name(Sample1 sample);
    };

    class Sample1 {
    private:
        string name;
    public:
        Sample1(string);

        string getName() {
            return name;
        }

        // 将全局函数定义为本类的友元函数
        friend void global_set_name(Sample1& sample, string n);

        friend string global_get_name(Sample1 sample);

        // 将其他类的成员函数作为本类的友元函数
        friend string Sample1NamePrinter::getName(Sample1 sample);

        // 将其他类的静态函数作为本类的友元函数
        friend string Sample1NamePrinter::static_get_name(Sample1 sample);
    };

    string Sample1NamePrinter::getName(Sample1 sample) {
        return sample.name;
    }

    string Sample1NamePrinter::static_get_name(Sample1 sample) {
        return sample.name;
    }

    Sample1::Sample1(string name) : name(name) {}

    void global_set_name(Sample1& sample, string n) {
        sample.name = n;
    }

    string global_get_name(Sample1 sample) {
        return sample.name;
    }

    TEST(friend_function, global_function_as_friend_function) {
        Sample1 sample1("foo");
        cout << "global_get_name(sample1): " << global_get_name(sample1) << endl;
        EXPECT_EQ(global_get_name(sample1), "foo");
    }

    TEST(friend_function, class_member_function_as_friend_function) {
        Sample1 sample1("foo");
        Sample1NamePrinter sample1NamePrinter;
        cout << "sample1NamePrinter.getName(sample1): " << sample1NamePrinter.getName(sample1) << endl;
        EXPECT_EQ(sample1NamePrinter.getName(sample1), "foo");
    }

    TEST(friend_function, class_static_function_as_friend_function) {
        Sample1 sample1("foo");
        cout << "Sample1NamePrinter::static_get_name(sample1): " << Sample1NamePrinter::static_get_name(sample1) << endl;
        EXPECT_EQ(Sample1NamePrinter::static_get_name(sample1), "foo");
    }

    TEST(friend_function, friend_function_mutate_object) {
        Sample1 sample1("foo");

        cout << "sample1.getName(): " << sample1.getName() << endl;
        cout << "sample1.getName(): " << global_get_name(sample1) << endl;

        global_set_name(sample1, "bar");

        cout << "sample1.getName(): " << sample1.getName() << endl;
        cout << "sample1.getName(): " << global_get_name(sample1) << endl;

        EXPECT_EQ(sample1.getName(), "bar");
    }
}
