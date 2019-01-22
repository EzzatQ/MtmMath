#include <stdio.h>
#include "MtmMatTriag.h"

using namespace MtmMath;

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

int main(){
    MtmMat<int> a(Dimensions(5,5), 0);
    printMat(a);
    MtmMatSq<int> b(a);
    printMat(b);
    MtmMatTriag<int> b2(b);
    printMat(b2);
    MtmMatTriag<int> c(a);
    printMat(c);
    c[0][3] = 3;
    printMat(c);
    MtmMatTriag<int> d(5, 2, false);
    printMat(d);
    MtmMatTriag<int> e(5, 2, true);
    printMat(e);
    MtmMatTriag<int> e2(e);
    printMat(e2);
    MtmMat<int> f = e + d;
    printMat(f);
    MtmMatSq<int> g(5, 2);
    printMat(g);
    MtmMat<int> h = f - g;
    printMat(h);
    printMat(e);
    e.transpose();
    printMat(e);
    e.resize(Dimensions(10,10), 3);
    printMat(e);
    e.reshape(Dimensions(10,9));
    printMat(e);
    
    
    
    return 1;
}
