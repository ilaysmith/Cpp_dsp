//#pragma once
#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>

template<typename T>
class Complex {
private:
    T real_;
    T imag_;

public:
    Complex() : real_(0), imag_(0) {}

    Complex(T real, T imag) : real_(real), imag_(imag) {}

    T get_real() const {
        return real_;
    }

    T get_imag() const {
        return imag_;
    }

    void set_real(T real) {
        real_ = real;
    }

    void set_imag(T imag) {
        imag_ = imag;
    }

    T magnitude() const {
        return std::sqrt(real_ * real_ + imag_ * imag_);
    }

    T phase() const {
        return std::atan2(imag_, real_);
    }

    Complex<T> conjugate() const {
        return Complex<T>(real_, -imag_);
    }

    // операторы

    Complex<T> operator+(const Complex<T> &other) const {
        return Complex<T>(real_ + other.real_, imag_ + other.imag_);
    }

    Complex<T> operator-(const Complex<T> &other) const {
        return Complex<T>(real_ - other.real_, imag_ - other.imag_);
    }

    Complex<T> operator*(const Complex<T> &other) const {
        return Complex<T>(real_ * other.real_ - imag_ * other.imag_, real_ * other.imag_ + imag_ * other.real_);
    }

    Complex<T> operator*(T scalar) const {
        return Complex<T>(real_ * scalar, imag_ * scalar);
    }

};

#endif 