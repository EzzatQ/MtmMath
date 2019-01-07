#ifndef Complex_hpp
#define Complex_hpp

#include <stdio.h>

class Complex {
    double re, im;
public:
    Complex(double r = 0, double i = 0): re(r), im(i){}
    Complex& operator+=(const Complex& c);
    Complex& operator-=(const Complex& c);
    Complex operator-() const {return Complex(-re, -im);}
    bool operator==(const Complex& c) const;
};
#endif /* Complex_hpp */
