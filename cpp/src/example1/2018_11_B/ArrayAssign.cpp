//
// Created by 许炎 on 2024/10/30.
//

#include "ArrayAssign.h"


void MulDate(int a[], int b[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        b[i] = a[i] * b[i];
    }
}
