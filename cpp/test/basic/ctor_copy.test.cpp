//
// Created by xy on 23-9-9.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace CopyConstructorExample {
    /**
     * 如果没有定义复制构造函数，系统会自动生成一个复制构造函数
     */
    class DefaultCopyCtorSample {
    private:
        string name;
    public:
        DefaultCopyCtorSample(string name) : name(name) {};

        string getName() {
            return name;
        }
    };


    /**
     * 如果没有定义复制构造函数，系统会自动生成一个复制构造函数
     */
    TEST(ctor, default_copy_ctor_sample) {
        DefaultCopyCtorSample sample1("foo");

        DefaultCopyCtorSample sample2(sample1);

        DefaultCopyCtorSample sample3 = sample1;

        cout << "sample1.getName(): " << sample1.getName() << endl;
        cout << "sample2.getName(): " << sample2.getName() << endl;
        cout << "sample3.getName(): " << sample3.getName() << endl;
        cout << "&sample1" << &sample1 << endl;
        cout << "&sample2" << &sample2 << endl;
        cout << "&sample3" << &sample3 << endl;

        EXPECT_EQ(sample2.getName(), sample1.getName());
        EXPECT_EQ(sample3.getName(), sample1.getName());
        EXPECT_NE(&sample1, &sample2);
        EXPECT_NE(&sample1, &sample3);
    }

    class CopyCtorSample1 {
    private:
    public:
        string name;
        int copy_ctor_called_times = 0;

        CopyCtorSample1(string name) : name(name) {};

        CopyCtorSample1(CopyCtorSample1 &sample) {
            cout << "复制构造函数 is called" << endl;
            name = sample.name;
            copy_ctor_called_times++;
        };
    };

    TEST(ctor, copy_ctor_sample1) {
        CopyCtorSample1 sample1("foo");
        // call 复制构造函数
        CopyCtorSample1 sample2(sample1);
        // call 复制构造函数
        CopyCtorSample1 sample3 = sample2;

        cout << "&sample1" << &sample1 << endl;
        cout << "&sample2" << &sample2 << endl;
        cout << "&sample3" << &sample3 << endl;
        cout << "sample1.name: " << sample1.name << endl;
        cout << "sample2.name: " << sample2.name << endl;
        cout << "sample3.name: " << sample3.name << endl;
        cout << "sample1.copy_ctor_called_times: " << sample1.copy_ctor_called_times << endl;
        cout << "sample2.copy_ctor_called_times: " << sample2.copy_ctor_called_times << endl;
        cout << "sample3.copy_ctor_called_times: " << sample3.copy_ctor_called_times << endl;
        EXPECT_EQ(sample1.copy_ctor_called_times, 0);
        EXPECT_EQ(sample2.copy_ctor_called_times, 1);
        EXPECT_EQ(sample3.copy_ctor_called_times, 1);

        // call 默认的赋值运算符
        sample3 = sample1;

        cout << "sample3.copy_ctor_called_times: " << sample3.copy_ctor_called_times << endl;
        EXPECT_EQ(sample3.copy_ctor_called_times, 0);
    }

    class CopyCtorSample2 {
    private:
    public:
        string name;
        int copy_ctor_called_times = 0;
        int assign_operator_overload_called_times = 0;

        CopyCtorSample2(string name) : name(name) {};

        CopyCtorSample2(CopyCtorSample2 &sample) {
            cout << "复制构造函数 is called" << endl;
            name = sample.name;
            copy_ctor_called_times++;
        };

        CopyCtorSample2 &operator=(const CopyCtorSample2 &sample) {
            cout << "赋值运算符重载 is called" << endl;
            assign_operator_overload_called_times++;
            name = sample.name;
            return *this;
        }
    };

    TEST(ctor, copy_ctor_sample2) {
        CopyCtorSample2 sample1("foo");
        // call 复制构造函数
        CopyCtorSample2 sample2(sample1);
        // call 复制构造函数
        CopyCtorSample2 sample3 = sample2;

        cout << "&sample1" << &sample1 << endl;
        cout << "&sample2" << &sample2 << endl;
        cout << "&sample3" << &sample3 << endl;
        cout << "sample1.name: " << sample1.name << endl;
        cout << "sample2.name: " << sample2.name << endl;
        cout << "sample3.name: " << sample3.name << endl;
        cout << "sample1.copy_ctor_called_times: " << sample1.copy_ctor_called_times << endl;
        cout << "sample2.copy_ctor_called_times: " << sample2.copy_ctor_called_times << endl;
        cout << "sample3.copy_ctor_called_times: " << sample3.copy_ctor_called_times << endl;
        cout << "sample1.assign_operator_overload_called_times: " << sample1.assign_operator_overload_called_times
             << endl;
        cout << "sample2.assign_operator_overload_called_times: " << sample2.assign_operator_overload_called_times
             << endl;
        cout << "sample3.assign_operator_overload_called_times: " << sample3.assign_operator_overload_called_times
             << endl;
        EXPECT_EQ(sample1.copy_ctor_called_times, 0);
        EXPECT_EQ(sample2.copy_ctor_called_times, 1);
        EXPECT_EQ(sample3.copy_ctor_called_times, 1);
        EXPECT_EQ(sample1.assign_operator_overload_called_times, 0);
        EXPECT_EQ(sample2.assign_operator_overload_called_times, 0);
        EXPECT_EQ(sample3.assign_operator_overload_called_times, 0);

        // call 重载的赋值运算符
        sample3.copy_ctor_called_times = 0;
        sample3 = sample1;

        cout << "sample3.copy_ctor_called_times: " << sample3.copy_ctor_called_times << endl;
        cout << "sample3.assign_operator_overload_called_times: " << sample3.assign_operator_overload_called_times
             << endl;

        EXPECT_EQ(sample3.copy_ctor_called_times, 0);
        EXPECT_EQ(sample3.assign_operator_overload_called_times, 1);
    }

    /**
     * 一个类可以写两个复制构造函数
     * 一个参数是 const 引用
     * 另一个是非 const 引用
     */
    class DoubleCopyCtorSample {
    private:
        string name;
    public:
        DoubleCopyCtorSample(DoubleCopyCtorSample &sample) {};

        DoubleCopyCtorSample(const DoubleCopyCtorSample &sample) {};
    };
}
