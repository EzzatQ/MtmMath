#include <stdio.h>
#include "MtmMat.h"

using namespace MtmMath;
MtmMat::MtmMat(Dimensions dim_t, const T& val = T()){
    size_t col = dim_t.getCol();
    size_t row = dim_t.getRow();
    values = new T[col*row];
    for(int i = 0; i < col*row; i++){
        values[i] = val;
    }
}

MtmMat::MtmMat(const MtmMat& m){
    size_t col = m.dim.getCol();
    size_t row = m.dim.getRow();
    MtmMat newMatrix(m.dim,0);
    for(int i = 0; i < col*row; i++){
        values[i] = m.values[i];
    }
}

MtmMat::~MtmMat(){
    delete[] values;
}

MtmMat& Operator=(const MtmMat& m){
    if(this == &m){
        return *this;
    }
    delete[] values;
    size_t col = m.dim.getCol();
    size_t row = m.dim.getRow();
    MtmMat newMatrix(m.dim,0);
    for(int i = 0; i < col*row; i++){
        values[i] = m.values[i];
    }
    return *this;
}
