//
// Created by xy on 23-9-9.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;


class Person {
private:
    string name;
    int age;
public:
    Person();

    Person(string);

    string getName();

    int getAge();

};

Person::Person() {

}

Person::Person(string name) : name(name), age(0) {}

string Person::getName() {
    return name;
}

int Person::getAge() {
    return age;
}

/**
 * 定义类变量的方法1
 */
TEST(class, create_object_1) {
    Person person1;
    Person person2("foo");
    Person person3 = Person("foo");
    cout << "person1.getName():" << person1.getName() << endl;
    cout << "person1.getAge():" << person1.getAge() << endl;
    cout << "person2.getName():" << person2.getName() << endl;
    cout << "person2.getAge():" << person2.getAge() << endl;
    cout << "person3.getName():" << person3.getName() << endl;
    cout << "person3.getAge():" << person3.getAge() << endl;
}

/**
 * 定义类变量的方法2
 */
TEST(class, create_object_2) {
    Person *person1 = new Person;
    Person *person2 = new Person();
    Person *person3 = new Person("foo");
    cout << "person1 -> getName:" << person1->getName() << endl;
    cout << "person1 -> getAge:" << person1->getAge() << endl;
    cout << "person2 -> getName:" << person2->getName() << endl;
    cout << "person2 -> getAge:" << person2->getAge() << endl;
    cout << "person3 -> getName:" << person3->getName() << endl;
    cout << "person3 -> getAge:" << person3->getAge() << endl;
    delete person1;
    delete person2;
    delete person3;
}
