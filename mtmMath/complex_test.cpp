#include <iostream>
#include "Complex.h"
using namespace MtmMath;


void printComplex(Complex& c){
    std::cout << "(" << c.real() << "," << c.imag() << ")\n ";
}

int main(){
    Complex a;
    printComplex(a);
    Complex a1 = Complex(5, 2);
    printComplex(a1);
    Complex b(a1);
    printComplex(b);
    Complex a2 = b;
    printComplex(a2);
    a2 = b + 2;
    printComplex(a2);
    bool t = a1 != b;
    std::cout << t<< std::endl;
    Complex c(b + a1);
    printComplex(c);
    Complex d(c * a1);
    printComplex(d);
    Complex e(d - c);
    printComplex(e);
    Complex f(a1 / a1);
    printComplex(f);
    Complex g = -f;
    printComplex(g);
    
}
