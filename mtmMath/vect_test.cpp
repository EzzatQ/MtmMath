#include <stdio.h>
#include "MtmVec.h"
#include "Complex.h"
using namespace MtmMath;

void FuncExample() {
    class maxAbsolute {
        int currMax;
    public:
        maxAbsolute() : currMax(0) {}
        void operator()(int x) {
            int absX = x>(-x) ? x : -x;
            if (currMax<absX) {currMax=absX;}
        }
        int operator*() { return  currMax;}
    };
    MtmVec<int> v(5,0);
    v[1]=3;v[2]=-7;v[3]=-1;v[4]=2;
    maxAbsolute f;
    if(v.vecFunc(f)==7){
        std::cout << "good job" << std::endl;
    }
}

void printVect(MtmVec<int>& v){
    std::cout<<std::endl;
    for(int i = 0; i< v.size(); i++){
            std::cout << v[i] << "  ";
        }
    std::cout<<std::endl;
    
}

void printVect(MtmVec<Complex>& v){
    std::cout<<std::endl;
    for(int i = 0; i< v.size(); i++){
        std::cout << v[i].real() << "," << v[i].imag() << "  ";
    }
    std::cout<<std::endl;
}

void fillvectfrom(MtmVec<int>& v, int j){
    for(MtmVec<int>::iterator i = v.begin(); i != v.end(); ++i , j++){
        *i = j;
    }
}

void printNonZero(MtmVec<int>& v){
     std::cout<<std::endl;
    MtmVec<int>::nonzero_iterator j = v.nzend();
    for(MtmVec<int>::nonzero_iterator i = v.nzbegin(); i != j; ++i){
        std::cout << *i << "  ";
    }
     std::cout<<std::endl;
}

void printNormal(MtmVec<int>& v){
    std::cout<<std::endl;
    MtmVec<int>::iterator j = v.end();
    for(MtmVec<int>::iterator i = v.begin(); i != j; ++i){
        std::cout << *i << "  ";
    }
    std::cout<<std::endl;
}


int main(){
    MtmVec<int> v1(10, 0);
    printVect(v1);
    v1.resize(Dimensions(15,1),0);
    v1[0] = v1[2] = v1[4] = v1[6] = v1[8] = v1[10] = v1[12] = v1[14] = 1;
    printNormal(v1);
    printNonZero(v1);
    v1.transpose();
    printVect(v1);
    v1.resize(Dimensions(1,13));
    printVect(v1);
    fillvectfrom(v1, 1);
    printVect(v1);
    MtmVec<int> v2(10, 1);
    printVect(v2);
    fillvectfrom(v2, 2);
    printVect(v2);
    MtmVec<Complex> v4(5,Complex(1,2));
    printVect(v4);
    MtmVec<Complex> v5(5,Complex(2,4));
    printVect(v5);
    MtmVec<Complex> v6(v4 + v5);
    printVect(v6);
    v6 = v6 * Complex(3);
    printVect(v6);
    v6 = Complex(0) * v6;
    printVect(v6);
    MtmVec<int> v3(v1);
    printVect(v1);
    fillvectfrom(v3, 0);
    printVect(v3);
    v1 += v3 ;
    printVect(v1);
    return 1;
}
