#include <stdio.h>
#include <iostream>
#include "MtmVec.h"
#include "MtmMat.h"
#include "Auxilaries.h"

using namespace MtmMath;

void printMat(MtmMat<int> m){
    size_t col = m.dim.getCol();
    size_t row = m.dim.getRow();
    for(int i = 0; i < col; i++){
        std::cout << std::endl;
        for(int j = 0; j < row; j++){
            std::cout << m.matrix[i][j] << " ";
        }
    }
    std::cout << std::endl << std::endl;
}


int main(){
    Dimensions a = Dimensions(5,6);
    MtmMat<int> m1(a);
    MtmMat<int> m2(Dimensions(4,4), 1);
    MtmMat<int> m3(Dimensions(8,6), 2);
    printMat(m1);
    printMat(m2);
    printMat(m3);
    
    
    
    
    return 1;
}
