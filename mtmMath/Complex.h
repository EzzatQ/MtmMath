#ifndef EX3_COMPLEX_H
#define EX3_COMPLEX_H
namespace MtmMath {
    class Complex {
        double re,im;
    public:
        Complex(double r = 0, double i = 0): re(r), im(i){}
        Complex(const Complex& c): re(c.re), im(c.im){}
        Complex& operator=(const Complex&);
        Complex& operator+=(const Complex& c);
        bool operator==(const Complex& c) const;
        bool operator!=(const Complex& c) const { return !operator==(c);}
        friend Complex operator+(const Complex& a, const Complex& b);
        Complex& operator-=(const Complex& c);
        friend Complex operator-(const Complex& a, const Complex& b);
        Complex operator-() const {return Complex(-re, -im);}
        Complex& operator*=(const Complex& c);
        friend Complex operator*(const Complex& a, const Complex& b);
        Complex& operator/=(const Complex& c);
        friend Complex operator/(const Complex& a, const Complex& b);
        Complex conjugate(){im = -im; return *this;}
        double real() { return re;}
        double imag() { return im;}
    };
}
#endif //EX3_COMPLEX_H
