#ifndef EX3_COMPLEX_H
#define EX3_COMPLEX_H
namespace MtmMath {
    class Complex {
    public:///////////////
        double re,im;
    public:
        Complex(double r = 0, double i = 0): re(r), im(i){}
        Complex(const Complex& c): re(c.re), im(c.im){}
        Complex& operator=(const Complex&);
        Complex& operator+=(const Complex& c);
        Complex& operator-=(const Complex& c);
        Complex operator-() const {return Complex(-re, -im);}
        bool operator==(const Complex& c) const;

    };
}
#endif //EX3_COMPLEX_H
