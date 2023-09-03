//
// Created by xy on 23-9-9.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

/**
 * Destructor
 */
class DestructorSample {
private:
    string name;
public:
    DestructorSample(string);

    ~DestructorSample() {
        cout << "destructor is called" << endl;
    }

    string getName() {
        return name;
    }
};

DestructorSample::DestructorSample(string name) : name(name) {};


/**
 */
TEST(dtor, default_copy_ctor_sample) {
    DestructorSample *sample1 = new DestructorSample("foo");
    delete sample1;
}

