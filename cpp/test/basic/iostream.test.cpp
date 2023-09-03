//
// Created by xy on 23-9-9.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace IoStreamSample {
    TEST(iostream, ios_status) {
        cout << cin.goodbit << endl;
        cout << cin.eofbit << endl;
        cout << cin.failbit << endl;
        cout << cin.badbit << endl;
        cout << cin.good() << endl;
        cout << cin.eof() << endl;
        cout << cin.fail() << endl;
        cout << cin.bad() << endl;
        cout << cin.rdstate() << endl;
    }

    TEST(iostream, iostream_stream_operator_1) {
        cout << "|";
        cout << ends;
        cout << "|";
        cout << endl;
        cout << "-------------";
    }

    TEST(iostream, iostream_stream_operator_dec_hex_oct) {
        int n = 1023;
        cout << dec << n << endl;
        cout << hex << n << endl;
        cout << oct << n << endl;
    }

    TEST(iostream, iostream_stream_operator_setbase) {
        int n = 1023;
        cout << setbase(10) << n << endl;
        cout << setbase(16) << n << endl;
        cout << setbase(8) << n << endl;
        cout << setbase(2) << n << endl;
    }

    TEST(iostream, iostream_stream_operator_setw) {
        string tmp = "foo";
        cout << setw(5) << setfill('*') << tmp << endl;
        cout << setw(10) << setfill('*') << tmp << endl;
        cout << setw(15) << setfill('*') << tmp << endl;
    }

    /**
     * show point even when it is zero
     * e.g. 123.0
     *
     * see also noshowpoint, only show point when it exists
     */
    TEST(iostream, iostream_stream_operator_showpoint) {
        cout << showpoint << 123 << endl;
        cout << 123.0 << endl;
        cout << showpoint << 123.0 << endl;  // 123.000
    }

    TEST(iostream, cout_member_function) {
        string tmp = "foo";
        cout.width(5);
        cout.fill('*');
        cout << tmp << endl;
        cout.width(10);
        cout << tmp << endl;
        cout.width(15);
        cout << tmp << endl;
    }

    TEST(iostream, iostream_stream_operator_setiosflags) {
        double x = 12.34;
        cout << setiosflags(ios::scientific | ios::showpos) << x << endl;
        cout << setiosflags(ios::fixed) << x << endl;
        cout << resetiosflags(ios::fixed) << setiosflags(ios::scientific | ios::showpos) << x << endl;
        cout << resetiosflags(ios::showpos) << x << endl;
    }

}
