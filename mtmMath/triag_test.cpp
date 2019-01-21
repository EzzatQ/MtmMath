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
    MtmMat<int> a(Dimensions(5,5), 3);
    printMat(a);
    MtmMatTriag<int> b(a);
    printMat(b);
    
    
    return 1;
}
