
#include <gtest/gtest.h>
#include "example1/2020_11_A/StrOrder.h"

using namespace std;

using namespace Q_2020_11_A;

TEST(sortInput, case1) {
    string str = "Bdsclid";

    string res = sortInput(str);

    EXPECT_EQ(res, "Bcdilsd");
}
