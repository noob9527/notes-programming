//
// Created by xy on 23-9-9.
//
#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace FunctionSample {
    /**
     * 函数参数默认是传值，而不是传引用
     * 如果参数类型是对象，会先调用复制构造函数，然后使用复制的对象调用函数
     */
    namespace FunctionInvokeSample {
        class Sample {
        public:
            string name;
            int copy_ctor_called_times = 0;

            Sample(string name) : name(name) {};

            Sample(Sample &sample) {
                cout << "复制构造函数 is called" << endl;
                name = sample.name;
                copy_ctor_called_times++;
            };
        };

        void set_sample_name_by_value(Sample sample, string name) {
            cout << "set_sample_name_by_value &sample" << &sample << endl;
            sample.name = name;
        }

        void set_sample_name_by_ref(Sample &sample, string name) {
            cout << "set_sample_name_by_ref &sample" << &sample << endl;
            sample.name = name;
        }

        TEST(function, by_value) {
            Sample sample("foo");
            set_sample_name_by_value(sample, "bar");
            cout << "&sample" << &sample << endl;
            cout << "sample.name: " << sample.name << endl;
            EXPECT_EQ(sample.name, "foo");
        }

        TEST(function, by_ref) {
            Sample sample("foo");
            set_sample_name_by_ref(sample, "bar");
            cout << "&sample" << &sample << endl;
            cout << "sample.name: " << sample.name << endl;
            EXPECT_EQ(sample.name, "bar");
        }
    }
}
