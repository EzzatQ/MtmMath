#include "Complex.hpp"

Complex& Complex::operator+=(const Complex& c){
    re += c.re;
    im += c.im;
    return *this;
}

Complex& Complex::operator-=(const Complex& c){
    return Complex::operator+=(-c);
}

Complex operator+(const Complex& a, const Complex& b){
    Complex c = a;
    return c +=b;
}

Complex operator-(const Complex& a, const Complex& b){
    Complex c = a;
    return c -=b;
}

bool Complex::operator==(const Complex& c) const {
    return re == c.re && im == c.im;
}

