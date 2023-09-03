//
// Created by xy on 23-9-9.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace FriendClassSample {

    class Sample {
    private:
        string name;
    public:
        Sample(string);

        string getName() {
            return name;
        }

        friend class FriendOfSample;
    };

    class FriendOfSample {
    public:
        void setName(Sample &sample, string n) {
            sample.name = n;
        }

        string getName(Sample sample) {
            return sample.name;
        }
    };

    Sample::Sample(string name) : name(name) {}


    TEST(friend_class, basic_sample) {
        Sample sample1("foo");
        FriendOfSample _friend;

        cout << "sample1.getName(): " << sample1.getName() << endl;
        cout << "sample1.getName(): " << _friend.getName(sample1) << endl;

        _friend.setName(sample1, "bar");

        cout << "sample1.getName(): " << sample1.getName() << endl;
        cout << "sample1.getName(): " << _friend.getName(sample1) << endl;

        EXPECT_EQ(sample1.getName(), "bar");
    }
}
