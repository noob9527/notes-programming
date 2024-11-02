//
// Created by 许炎 on 2024/11/2.
//

#ifndef COMPLEX_H
#define COMPLEX_H


class Complex {
public:
    int real = 0;
    int imagine = 0;

    Complex() = default;

    Complex(int real, int imagine) : real(real), imagine(imagine) {
    }

    Complex &operator=(const Complex &other) {
        if (&other == this) return *this;
        real = other.real;
        imagine = other.imagine;
        return *this;
    }

    Complex operator+(const Complex &other) const {
        return {real + other.real, imagine + other.imagine};
    }

    Complex operator-(const Complex &other) const {
        return {real - other.real, imagine - other.imagine};
    }

    Complex operator*(const Complex &other) const {
        return {real * other.real, imagine * other.imagine};
    }

    Complex operator/(const Complex &other) const {
        return {real / other.real, imagine / other.imagine};
    }
};


#endif //COMPLEX_H
