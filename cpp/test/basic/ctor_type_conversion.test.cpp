//
// Created by xy on 23-9-9.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

/**
 */
class TypeConversionCtorSample {
private:
    string name;
    int age;
public:
    TypeConversionCtorSample(string);

    TypeConversionCtorSample(int);

    string getName() {
        return name;
    }

    void setName(string n) {
        name = n;
    }

    int getAge() {
        return age;
    }
};

TypeConversionCtorSample::TypeConversionCtorSample(string name) : name(name) {};

TypeConversionCtorSample::TypeConversionCtorSample(int _age) : age(_age) {};


TEST(ctor, type_conversion_ctor_sample) {
    TypeConversionCtorSample sample1(1);
    sample1.setName("foo");

    cout << "sample1.getName(): " << sample1.getName() << endl;
    cout << "sample1.getAge(): " << sample1.getAge() << endl;
    cout << "&sample1" << &sample1 << endl;

    sample1 = 2;

    cout << "sample1.getName(): " << sample1.getName() << endl;
    cout << "sample1.getAge(): " << sample1.getAge() << endl;
    cout << "&sample1" << &sample1 << endl;

    EXPECT_EQ(sample1.getAge(), 2);
    EXPECT_EQ(sample1.getName(), "");

}


