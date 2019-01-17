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
    /*Complex c(b + a);
    printComplex(c);
    Complex d(c * a);
    printComplex(d);
    Complex e(d - c);
    printComplex(e);
    Complex f(a / a);
    printComplex(f);*/
    
}
