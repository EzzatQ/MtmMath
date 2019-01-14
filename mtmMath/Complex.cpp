#include "Complex.h"
using namespace MtmMath;

Complex& Complex::operator=(const Complex& c){
    re = c.re;
    im = c.im;
    return *this;
}

Complex& Complex::operator+=(const Complex& c){
    re += c.re;
    im += c.im;
    return *this;
}

Complex operator+(const Complex& a, const Complex& b){
    Complex c = a;
    return c +=b;
}

Complex& Complex::operator-=(const Complex& c){
    return Complex::operator+=(-c);
}

Complex operator-(const Complex& a, const Complex& b){
    Complex c = a;
    return c -=b;
}

bool Complex::operator==(const Complex& c) const {
    return re == c.re && im == c.im;
}

Complex& Complex::operator*=(const Complex& c){
    re = re * c.re - im * c.im;
    im = re * c.im + im * c.re;
    return *this;
}

Complex operator*(const Complex& a, const Complex& b){
    Complex c = a;
    return c *= b;
}

Complex& Complex::operator/=(const Complex& c){
    Complex a = c;
    *this *= a.conjugate();
    double dividend = c.re * c.re + c.im *c.im;
    re /= dividend;
    im /= dividend;
    return *this;
}

Complex operator/(const Complex& a, const Complex& b){
    Complex c = a;
    return c /= b;
}

