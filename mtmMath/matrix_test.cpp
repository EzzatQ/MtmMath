#include <stdio.h>
#include <iostream>
#include "MtmVec.h"
#include "MtmMat.h"
#include "Auxilaries.h"
#include <assert.h>

using namespace MtmMath;

void printVect(MtmVec<int>& v){
    std::cout<<std::endl;
    for(int i = 0; i< v.size(); i++){
        std::cout << v[i] << "  ";
    }
}

void printMat(MtmMat<int> m){
    size_t col = m.getDim().getCol();
    size_t row = m.getDim().getRow();
    for(int i = 0; i < row; i++){
        std::cout << std::endl;
        for(int j = 0; j < col; j++){
            std::cout << m[i][j] << " ";
        }
    }
    std::cout << std::endl << std::endl;
}

void printNormal(MtmMat<int>& v){
    std::cout<<std::endl;
    MtmMat<int>::iterator j = v.end();
    for(MtmMat<int>::iterator i = v.begin(); i != j; ++i){
        std::cout << *i << "  ";
    }
    std::cout<<std::endl;
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
    Dimensions a = Dimensions(2, 1);
    Dimensions b = Dimensions(2,2);
    MtmMat<int> m1(a, 1);
    //printNormal(m1);
    MtmMat<int> m2(b, 2);
    m2[0][0] = 0; m2[0][1] = 1; m2[1][0] = 2; m2[1][1] = 3;
    printNormal(m2);
    MtmMat<int> m3(a, 3);
    MtmVec<int> v1(2, 5);
    //m1 = m2 * m3;
    //printMat(m1);
    m1 = 5 * m2;
    printMat(m1);
    //m1 = v1 * m2;
    //printMat(m1);
    m1 = m2;
    printMat(m1);
    for(int i = 0; i < m1.getDim().getRow(); i++){
        for(int j = 0; j < m1.getDim().getCol(); j++){
            m1[i][j] = i + j * (int)m1.getDim().getRow();
            m2[i][j] = i + j * (int)m2.getDim().getRow();
        }
    }
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
    std::cout << "we are testing this \n";
    MtmMat<int> m4(Dimensions(15,4), 0);
    
    printMat(m4);
    m4[14][3] = 9;
    m4[5][0] = 2;
    printMat(m4);
    MtmMat<int>::nonzero_iterator p = m4.nzbegin();
    
    
    //(m4.nzend()).printItr();
    std::cout << "iterator pointing at: " << *p << std::endl;
    for(MtmMat<int>::nonzero_iterator i = m4.nzbegin(); i != m4.nzend(); ++i){
        //i.printItr();
        *i = 1;
    }
    printMat(m4);
    p = m4.nzbegin();
    std::cout << "iterator pointing at: " << *p << std::endl;
    MtmMat<int>::iterator n = m2.begin();
    MtmMat<int>::iterator m = m2.begin();
    //if(!(p == n)) std::cout << "yessssss" << std::endl;
    ++n;
    std::cout << (*n) << std::endl;
    m2[1][0]=2;
    std::cout << (*n) << std::endl;
    ++m;
    std::cout << (n == m) << std::endl;
    
    
    
    
    return 1;
}
