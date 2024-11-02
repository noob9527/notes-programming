/**
 *
 * 第二题：
 *
 * 长度为7的字符串，首尾保持不变，中间字符按ASCII码升序排列，
 * 然后输出。举例如”Bdsaclid",排序后输出“Bacdlisd"。
 */

#include <iostream>
#include <algorithm>
#include "StrOrder.h"

using namespace std;

namespace Q_2020_11_A {

    void mySort(string &s, int start, int end) {
        char tmp;
        // insertion sort
        for (int i = start + 1; i <= end; i++) {
            if (s[i] > s[i - 1]) continue;

            for (int j = i; j > 0; j--) {
                if (s[j] < s[j - 1]) {
                    tmp = s[j - 1];
                    s[j - 1] = s[j];
                    s[j] = tmp;
                }
            }
            s[i] = s[i + 1];
        }
    }

    string sortInput(string input) {
        if (input.length() != 7)
            return string();

        // the standard library's sort() function:
        sort(input.begin() + 1, input.end() - 1);

//        mySort(input.begin() + 1, input.end() - 1);
        return input;
    }

}

//int main() {
//    string input;
//    while (input.length() < 7) {
//        cout << "> type in a string with at least 7 chars" << endl;
//        cin >> input;
//    }
//    input = input.substr(0, 7);
//    cout << "input: " + input << endl;
//    cout << "output: " + Q_2020_11_A::sortInput(input) << endl;
//    cout << "input: " + input << endl;
//    return 0;
//}
