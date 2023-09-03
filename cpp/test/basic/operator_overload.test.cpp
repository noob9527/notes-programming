//
// Created by xy on 23-9-9.
//

#include <iostream>
#include "gtest/gtest.h"
#include <string>

using namespace std;

namespace OperatorOverloadSample {
    class Complex {
    private:
        int real, imagine;
    public:
        Complex(int, int);

        // 使用成员函数重载
        Complex operator+(Complex &point);

        // 可以使用成员函数重载
        Complex operator+(int r);

        // 使用友元函数重载
        friend Complex operator-(const Complex &point1, const Complex &point2);

        // 只能使用友元函数重载
        friend Complex operator+(int r, const Complex &point);

        string to_string() {
            return "(" + std::to_string(real) + ", " + std::to_string(imagine) + ")";
        }
    };

    Complex::Complex(int real, int imagine) : real(real), imagine(imagine) {};

    Complex Complex::operator+(Complex &point) {
        return Complex(this->real + point.real, this->imagine + point.imagine);
    }

    Complex Complex::operator+(int r) {
        return Complex(this->real + r, this->imagine);
    }

    Complex operator-(const Complex &point1, const Complex &point2) {
        return Complex(point1.real - point2.real, point1.imagine - point2.imagine);
    }

    Complex operator+(int real, const Complex &point) {
        return Complex(point.real + real, point.imagine);
    }

    TEST(operator_overload, operator_on_same_class) {
        Complex point1(1, 1);
        Complex point2(1, 1);

        Complex addition1 = point1 + point2;
        // 等价于
        Complex addition2 = point1.operator+(point2);

        Complex difference = point1 - point2;

        cout << "addition1: " << addition1.to_string() << endl;
        cout << "addition2: " << addition2.to_string() << endl;
        cout << "difference: " << difference.to_string() << endl;
    }

    /**
     * 有时只能用友元函数来重载运算符
     */
    TEST(operator_overload, operator_on_different_type) {
        Complex complex(1, 1);

        Complex addition1 = complex + 1;
        Complex addition2 = complex.operator+(1);
        // 只能用友元函数
        Complex addition3 = 1 + complex;
        // 等价于
        Complex addition4 = operator+(1, complex);

        cout << "addition1: " << addition1.to_string() << endl;
        cout << "addition2: " << addition2.to_string() << endl;
        cout << "addition3: " << addition3.to_string() << endl;
        cout << "addition4: " << addition4.to_string() << endl;
    }

}

namespace StreamInsertionExtractionOverloadExample {
    class Point {
    private:
        int x, y;
    public:
        Point(int, int);

        friend ostream &operator<<(ostream &output, Point &point);

        friend istream &operator>>(istream &input, Point &point);
    };

    Point::Point(int x, int y) : x(x), y(y) {}

    ostream &operator<<(ostream &output, Point &point) {
        output << "(" << std::to_string(point.x) << ", " << std::to_string(point.y) << ")";
        return output;
    }

    istream &operator>>(istream &input, Point &point) {
        input >> point.x >> point.y;
        return input;
    }

    TEST(stream_insertion_overload, basic) {
        Point point(1, 1);

        cout << "point: " << point << endl;
        // 等价于
        cout << "point: ";
        operator<<(cout, point);
        cout << endl;
    }
}

namespace TypeConversionOperatorOverloadExample {
    class Complex {
    private:
        int real, imagine;
    public:
        Complex(int real, int imagine) : real(real), imagine(imagine) {};

        operator int() {
            return real;
        }
    };

    TEST(type_conversion_overload, basic) {
        Complex complex(1, 2);
        // explicit conversion
        int real1 = (int) complex;
        int real2 = complex.operator int();
        // implicit conversion
        int real3 = complex;
        cout << "real1: " << real1 << endl;
        cout << "real2: " << real2 << endl;
        cout << "real3: " << real3 << endl;
        EXPECT_EQ(real1, 1);
        EXPECT_EQ(real2, 1);
        EXPECT_EQ(real3, 1);
    }
}

namespace IncreaseDecreaseOverloadSample {
    class Operand {
    public:
        int value;
        Operand(int value) : value(value) {};

        /**
         * overload prefix form of increase operator
         * e.g. ++operand
         * here we return `Operand &`, align to the c++'s custom
         * @return returned value should be a reference to *this
         */
        Operand &operator++() {
            value++;
            cout << "this: " << this << endl;
            return *this;
        }

        /**
         * overload postfix form of increase operator
         * e.g. operand++
         *
         * The operator symbol for both prefix(++i) and postfix(i++) are the same.
         * Hence, we need two different function definitions to distinguish between them.
         * This is achieved by passing a dummy int parameter in the postfix version.
         * 槽点!
         * @param k
         * @return returned value should be a copy of the object before increment
         */
        Operand operator++(int k) {
            // call default copy constructor
            Operand tmp = (*this);
            value++;
            return tmp;
        }
    };

    TEST(inc_dec_overload, prefix_form) {
        Operand a(0);
        const Operand *pointerOfA = &a;
//        Operand res = ++a;  // 这里不能这样写, 这样会调用默认复制构造函数, 生成一个新对象
        Operand &res = ++a;

        cout << a.value << endl;
        cout << res.value << endl;
        cout << &a << endl;
        cout << pointerOfA << endl;
        cout << &res << endl;

        EXPECT_EQ(a.value, 1);
        EXPECT_EQ(res.value, 1);
        EXPECT_EQ(&a, pointerOfA);
        EXPECT_EQ(&res, &a);

        // tips: 还可以这样调用
//        a.operator++();
    }

    TEST(inc_dec_overload, postfix_form) {
        Operand a(0);
        const Operand *pointerOfA = &a;
        // 这里不能这么写, 就很费解
        // 报 Non-const lvalue reference to type 'IncreaseDecreaseOverloadSample::Operand' cannot bind to a temporary of type 'IncreaseDecreaseOverloadSample::Operand
        // 只能在前面加个 const...
//        Operand &res = a++;
        const Operand &res = a++;

        cout << a.value << endl;
        cout << res.value << endl;
        cout << &a << endl;
        cout << pointerOfA << endl;
        cout << &res << endl;

        EXPECT_EQ(a.value, 1);
        EXPECT_EQ(res.value, 0);
        EXPECT_EQ(&a, pointerOfA);
        EXPECT_NE(&res, &a);

        // tips: 还可以这样调用
        a.operator++(0);
    }

    class OperandMimicKotlinInc {
    public:
        const int value;
        OperandMimicKotlinInc(int value) : value(value) {};
        OperandMimicKotlinInc(const OperandMimicKotlinInc &operand): value(value) {
            cout << "复制构造函数 is called" << endl;
        };

        OperandMimicKotlinInc operator++() {
            return OperandMimicKotlinInc(value + 1);
        }

        OperandMimicKotlinInc operator++(int k) {
            return OperandMimicKotlinInc(value + 1);
        }
    };

    /**
     * 无法在 c++ 中模拟 kotlin 的 inc 重载行为
     */
    TEST(inc_dec_overload, mimic_kotlin_behavior) {
        OperandMimicKotlinInc a(0);
        const OperandMimicKotlinInc *pointerOfA = &a;
        const OperandMimicKotlinInc &res = a++; // 这个调用结束后, a 指向的对象不会变, 跟 kotlin 中不一样

        cout << a.value << endl;
        cout << res.value << endl;
        cout << &a << endl;
        cout << pointerOfA << endl;
        cout << &res << endl;

        EXPECT_EQ(a.value, 0);
        EXPECT_EQ(res.value, 1);
        EXPECT_EQ(&a, pointerOfA);
        EXPECT_NE(&res, &a);
    }

}

namespace AssignOverloadSample {
    class Complex {
    private:
        int real, imagine;
    public:
        Complex(int real, int imagine) : real(real), imagine(imagine) {};

        Complex &operator=(Complex &complex) {
            this->real = complex.real;
            this->imagine = complex.imagine;
        }

        friend ostream &operator<<(ostream &output, Complex &complex);
    };

    ostream &operator<<(ostream &output, Complex &complex) {
        output << "(" << std::to_string(complex.real) << ", " << std::to_string(complex.imagine) << ")";
        return output;
    }

    TEST(assign_overload, basic) {
        Complex complex1(1, 1);
        Complex complex2 = complex1;
        Complex complex3(2, 2);
        complex3.operator=(complex1);

        cout << "complex1: " << complex1 << endl;
        cout << "complex2: " << complex2 << endl;
        cout << "complex3: " << complex3 << endl;

        cout << "&complex1: " << &complex1 << endl;
        cout << "&complex2: " << &complex2 << endl;
        cout << "&complex3: " << &complex3 << endl;

        EXPECT_NE(&complex1, &complex2);
        EXPECT_NE(&complex1, &complex3);
    }

    /**
     * 1. 对象浅拷贝后,多个对象引用同一块内存空间,多次释放同一块内存空间会报错
     * 2. 发生浅拷贝时,原对象申请的空间不会被释放,造成内存泄漏
     * e.g.
     * ```c++
     * Sample sample1;
     * Sample sample2;
     * sample1 = sample2;  // 此时 sample1.pointer 指向的内存空间没有被释放, 内存泄漏
     * ```
     */
    class ShallowCopySample {
    private:
    public:
        int value;
        int *pointer;

        ShallowCopySample(int value = 0, int *pointer = new int(0)) : value(value), pointer(pointer) {};

        // Error: free(): double free detected in tcache 2
        // Signal: SIGABRT (Aborted)
//        ~ShallowCopySample() {
//            if (pointer != NULL) delete pointer;
//        }
    };

    TEST(assign_overload, shallow_copy) {
        ShallowCopySample sample1;
        ShallowCopySample sample2(sample1); // 调用复制构造函数
        ShallowCopySample sample3 = sample2; // 调用复制构造函数

        cout << "sample1.value: " << sample1.value << endl;
        cout << "sample2.value: " << sample2.value << endl;
        cout << "sample3.value: " << sample3.value << endl;
        cout << "sample1.pointer: " << sample1.pointer << endl;
        cout << "sample2.pointer: " << sample2.pointer << endl;
        cout << "sample3.pointer: " << sample3.pointer << endl;
        cout << "*sample1.pointer: " << *sample1.pointer << endl;
        cout << "*sample2.pointer: " << *sample2.pointer << endl;
        cout << "*sample3.pointer: " << *sample3.pointer << endl;

        sample1.value = 1;
        *sample1.pointer = 1;

        cout << "sample1.value: " << sample1.value << endl;
        cout << "sample2.value: " << sample2.value << endl;
        cout << "sample3.value: " << sample3.value << endl;
        cout << "sample1.pointer: " << sample1.pointer << endl;
        cout << "sample2.pointer: " << sample2.pointer << endl;
        cout << "sample3.pointer: " << sample3.pointer << endl;
        cout << "*sample1.pointer: " << *sample1.pointer << endl;
        cout << "*sample2.pointer: " << *sample2.pointer << endl;
        cout << "*sample3.pointer: " << *sample3.pointer << endl;
    }

    class DeepCopySample {
    private:
    public:
        int value;
        int *pointer;

        DeepCopySample(int value = 0, int *pointer = new int(0)) : value(value), pointer(pointer) {};

        // 复制构造函数
        DeepCopySample(DeepCopySample &sample) {
            cout << "复制构造函数 is called" << endl;
            if (this != &sample) {
                value = sample.value;

                // 感觉这里的 pointer 可能还不是 new 的值, 而是分配到了一片空的内存空间
                // We cannot delete pointer here.
                // incorrect: free(): invalid pointer
//                if (pointer != NULL) delete pointer;

                pointer = new int();
                cout << pointer << endl;
                *pointer = *sample.pointer;
            }
        }

        // 赋值运算符重载
        DeepCopySample &operator=(const DeepCopySample &sample) {
            cout << "赋值运算符重载 is called" << endl;
            if (this == &sample) return *this;
            if (pointer != NULL) delete pointer;
            pointer = new int(*sample.pointer);
            return *this;
        }

        ~DeepCopySample() {
            if (pointer != NULL) delete pointer;
        }
    };

    TEST(assign_overload, deep_copy) {
        DeepCopySample sample1;
        DeepCopySample sample2(sample1); // 调用复制构造函数
        DeepCopySample sample3 = sample2; // 调用复制构造函数
        sample3 = sample1; // 调用赋值运算符重载

        cout << "sample1.value: " << sample1.value << endl;
        cout << "sample2.value: " << sample2.value << endl;
        cout << "sample3.value: " << sample3.value << endl;
        cout << "sample1.pointer: " << sample1.pointer << endl;
        cout << "sample2.pointer: " << sample2.pointer << endl;
        cout << "sample3.pointer: " << sample3.pointer << endl;
        cout << "*sample1.pointer: " << *sample1.pointer << endl;
        cout << "*sample2.pointer: " << *sample2.pointer << endl;
        cout << "*sample3.pointer: " << *sample3.pointer << endl;

        sample1.value = 1;
        *sample1.pointer = 1;

        cout << "sample1.value: " << sample1.value << endl;
        cout << "sample2.value: " << sample2.value << endl;
        cout << "sample3.value: " << sample3.value << endl;
        cout << "sample1.pointer: " << sample1.pointer << endl;
        cout << "sample2.pointer: " << sample2.pointer << endl;
        cout << "sample3.pointer: " << sample3.pointer << endl;
        cout << "*sample1.pointer: " << *sample1.pointer << endl;
        cout << "*sample2.pointer: " << *sample2.pointer << endl;
        cout << "*sample3.pointer: " << *sample3.pointer << endl;
    }
}

