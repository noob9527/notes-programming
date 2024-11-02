//
// Created by 许炎 on 2024/11/2.
//

#ifndef COMPLEX_H
#define COMPLEX_H


class Complex
{
public:
    int real = 0;
    int imagine = 0;

    Complex()
    {
    }

    Complex(int real, int imagine): real(real), imagine(imagine)
    {
    }

    Complex& operator=(Complex& other)
    {
        if(&other == this) return *this;
    }

    Complex& operator+(Complex& other)
    {
        // Complex result;
        this->real = this->real + other.real;
        this->imagine = this->imagine + other.imagine;
        // return this;
    }
};


#endif //COMPLEX_H
