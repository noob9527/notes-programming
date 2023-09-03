//
// Created by xy on 23-9-9.
//

#include <iostream>

using namespace std;

namespace MainDtorSample {
    class Sample {
    public:
        Sample() {
            cout << "constructor is called" << endl;
        }
        ~Sample() {
            cout << "destructor is called" << endl;
        }
    };
}

/**
 * it shows that
 * destructor will be called before main function return
 * @return
 */
int main() {
    MainDtorSample::Sample sample;
    return 0;
}
