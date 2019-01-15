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
    for(int i = 0; i< v.vect.size(); i++){
            std::cout << v[i] << "  ";
        }
    
}

void printVect(MtmVec<Complex>& v){
    std::cout<<std::endl;
    for(int i = 0; i< v.vect.size(); i++){
        std::cout << v[i].real() << "," << v[i].imag() << "  ";
    }
}

void fillvectfrom(MtmVec<int>& v, int j){
    for(int i = 0; i < v.vect.size();i++, j++){
        v[i] = j;
    }
}

int main1(){
    MtmVec<int> v1(10, 0);
    std::cout << "size of v1 is: " << v1.size() << std::endl;
    printVect(v1);
    v1.resize(Dimensions(15,1), 100);
    std::cout << "size of v1 is: " << v1.size() << std::endl;
    v1.transpose();
    v1.resize(Dimensions(1,13));
    std::cout << "size of v1 is: " << v1.size() << std::endl;
    printVect(v1);
    fillvectfrom(v1, 1);
    MtmVec<int> v2(10, 1);
    fillvectfrom(v2, 2);
    MtmVec<Complex> v4(5,Complex(2,2));
    MtmVec<int> v3(v1);
    v1 = v2;
    printVect(v1);
    printVect(v2);
    printVect(v3);
    printVect(v4);
    return 1;
}
