//
// Created by xy on 23-9-9.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace TemplateFunctionSample {

    template<class T>
    void swap(T &x, T &y) {
        T tmp = x;
        x = y;
        y = tmp;
    }

    TEST(template_function, template_function) {
        int a = 1, b = 2;
        swap(a, b);
        cout << a << endl;
        cout << b << endl;
        EXPECT_EQ(a, 2);
        EXPECT_EQ(b, 1);
    }

    /**
     * 显式实例化模板
     */
    TEST(template_function, instantiate_template_explicitly) {
        int a = 1, b = 2;
        swap<int>(a, b);
        cout << a << endl;
        cout << b << endl;
        EXPECT_EQ(a, 2);
        EXPECT_EQ(b, 1);
    }

}

namespace TemplateClassSample {

    /**
     * 模板参数表中的 class 关键词等价于 typename 关键词, 可以混用
     * @tparam T1
     * @tparam T2
     */
    template<class T1, typename T2>
    class Pair {
    public:
        T1 first;
        T2 second;

        Pair(T1 first, T2 second) : first(first), second(second) {

        }
    };

    TEST(template_class, template_class) {
        Pair<string, int> pair("foo", 1);
        cout << pair.first << endl;
        cout << pair.second << endl;
    }

}

namespace TemplateParamSample {

    /**
     * 模板参数除了类型之外, 还可以是变量
     * @tparam T
     * @tparam size
     */
    template<class T, int size = 3>
    class Sum {
    public:
        T array[size];

        Sum(T a, T b, T c) {
            array[0] = a;
            array[1] = b;
            array[2] = c;
        }

        T sum() {
            return array[0] + array[1] + array[2];
        }
    };

    TEST(template_param, template_param) {
        Sum<int> sum1(1, 2, 3);
        Sum<int, 3> sum2(1, 2, 3);
        Sum<int, 4> sum3(1, 2, 3);
        cout << sum1.sum() << endl;
        cout << sum2.sum() << endl;
        cout << sum3.sum() << endl;
        EXPECT_EQ(6, sum1.sum());
        EXPECT_EQ(6, sum2.sum());
        EXPECT_EQ(6, sum3.sum());
    }

}

namespace TemplateSample1 {

    template<class T>
    T sum(T param1, T param2) {
        return param1 + param2;
    }

    TEST(template_class, sum) {
        // correct
        int res1 = sum(1, 2);
        int res2 = sum(1.1, 2.1);

        // incorrect
//        int res3 = sum(1.1, 2);
    }
}
