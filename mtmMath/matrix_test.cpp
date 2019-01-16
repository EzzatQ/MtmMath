#include <stdio.h>
#include <iostream>
#include "MtmVec.h"
#include "MtmMat.h"
#include "Auxilaries.h"
#include <assert.h>

using namespace MtmMath;

void printVect(MtmVec<int>& v){
    std::cout<<std::endl;
    for(int i = 0; i< v.vect.size(); i++){
        std::cout << v[i] << "  ";
    }
}

void printMat(MtmMat<int> m){
    size_t col = m.dim.getCol();
    size_t row = m.dim.getRow();
    for(int i = 0; i < row; i++){
        std::cout << std::endl;
        for(int j = 0; j < col; j++){
            std::cout << m.matrix[i][j] << " ";
        }
    }
    std::cout << std::endl << std::endl;
}

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
    MtmMat<int> m(Dimensions(2,3),0);
    m[0][1]=1;m[1][0]=2;
    m[0][1]=3;m[1][1]=2;
    m[0][2]=5;m[1][2]=-6;
    maxAbsolute f;
    assert (v.vecFunc(f)==7);
    MtmVec<int> res(m.matFunc(f));
    assert(res[0]==2 and res[1]==3 and res[2]==6);
}



int main(){
    Dimensions a = Dimensions(2,2);
    Dimensions b = Dimensions(2,2);
    MtmMat<int> m1(a, 1);
    MtmMat<int> m2(b, 2);
    MtmMat<int> m3(a, 3);
    m1 *= m2;
    printMat(m1);
    m1 *= 5;
    printMat(m1);
    m1 = m2 - m3;
    printMat(m1);
    m1 = m2 - 5;
    printMat(m1);
    /*for(int i = 0; i < m1.dim.getRow(); i++){
        for(int j = 0; j < m1.dim.getCol(); j++){
            m1[i][j] = i + j * (int)m1.dim.getRow();
        }
    }*/
    //printMat(m1);
    //m1.reshape(Dimensions(10,3));
    //printMat(m1);
    //m1.transpose();
    //printMat(m1);
    //printMat(m2);
    //printMat(m3);
    //printMat(m4);
    //MtmMat<int> m4 = m1 + m3;
    //FuncExample();
    
    
    
    
    return 1;
}
