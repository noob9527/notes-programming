/**
 * 二、设计函数CoverFun,要求：将用户输入的字符串中的大写字母都改为对应的小写字母，其他字符不变；
 * 同时设计主函数测试该函数。
 * 例如：若输入“this23ThiS”,则输出“this23this”。
*/

#include <string>
#include <iostream>

using namespace std;

const int DIFF = 'a' - 'A';

namespace Q_2018_11_A
{
    string CoverFun(string str)
    {
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] >= 'A' && str[i] <= 'Z')
            {
                str[i] += DIFF;
            }
        }
        return str;
    }
}
