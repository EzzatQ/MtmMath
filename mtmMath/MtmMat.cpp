#include <stdio.h>
#include "MtmMat.h"

using namespace MtmMath;

//template <class T>
MtmMat::MtmMat(Dimensions dim_t, const T& val = T()):
matrix(dim_t.getCol(),MtmVec<T>(dim_t.getRow(),val)) , dim(dim_t){}


MtmMat::MtmMat(const MtmMat& mat): matrix(MtmVec<MtmVec<T>>(1,T())){
    if(dim != mat.dim){
        throw MtmExceptions::DimentionMismatch();
    }
    matrix = mat.matrix;
    dim = mat.dim;
}

MtmMat::~MtmMat(){}

MtmMat& MtmMat::operator=(const MtmMat& mat){
    if(this == &mat){
        return *this;
    }
    matrix = mat.matrix;
    dim = mat.dim;
    return *this;
}

template <typename Func>
MtmVec<T> MtmMat::matFunc(Func& f) const{
    for(int i = 0; i < dim.getCol(); i++){
        matrix[i].vecFunc(f);
    }
    return *f;
}
