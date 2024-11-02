//
// Created by 许炎 on 2024/11/2.
//

#ifndef MAX_H
#define MAX_H

template <typename T>
T max(T t1, T t2)
{
    return t1 > t2 ? t1 : t2;
}

/**
 * 模板参数表中的 class 关键词等价于 typename 关键词, 可以混用
 * @tparam T1
 * @tparam T2
 */
template <typename T1, class T2>
class Pair
{
public:
    T1 first;
    T2 second;
};

#endif //MAX_H
