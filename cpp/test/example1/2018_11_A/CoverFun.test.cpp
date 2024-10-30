#include <string>
#include <gtest/gtest.h>

using namespace std;

namespace Q_2018_11_A
{
    string CoverFun(string str);
}

TEST(CoverFun, CoverFun)
{
    const string res = Q_2018_11_A::CoverFun("this23ThiS");
    EXPECT_EQ("this23this", res);
}
