#include <stdio.h>
#include "MtmMat.h"

using namespace MtmMath;

template <class T>
MtmMat<T>::MtmMat(Dimensions dim_t, const T& val):
matrix(dim_t.getCol(),MtmVec<T>(dim_t.getRow(),val)) , dim(dim_t){
    matrix.transpose();
}

template <class T>
MtmMat<T>::MtmMat(const MtmMat& mat): matrix(MtmVec<MtmVec<T>>(1,T())){
    if(dim != mat.dim){
        throw MtmExceptions::DimensionMismatch();
    }
    matrix = mat.matrix;
    dim = mat.dim;
}

template <class T>
MtmMat<T>::~MtmMat<T>(){}

template <class T>
MtmMat<T>& MtmMat<T>::operator=(const MtmMat& mat){
    if(this == &mat){
        return *this;
    }
    matrix = mat.matrix;
    dim = mat.dim;
    return *this;
}

template <class T>
template <typename Func>
MtmVec<T> MtmMat<T>::matFunc(Func& f) const{
    MtmVec<T> output(dim.getCol());
    for(int i = 0; i < dim.getCol(); i++){
        output[i] = matrix[i].vecFunc(f);
    }
    return output;
}

template <class T>
void MtmMat<T>::resize(Dimensions dim, const T& val){
    size_t newCol = dim.getCol();
    size_t newRow = dim.getRow();
    matrix.resize(Dimensions(newCol, 1), val);
    size_t colSize = matrix.size();
    for(int i = 0; i < colSize; i++){
        matrix[i].resize(Dimensions(1, newRow), val);
    }
}

template <class T>
void MtmMat<T>::reshape(Dimensions newDim){
    size_t newCol = newDim.getCol(), newRow = newDim.getRow();
    size_t col = dim.getCol(), row = dim.getCol();
    if(newCol * newRow != col * row){
        throw MtmExceptions::DimensionMismatch();
    }
    T tempArr = new T[col*row];
    for(int i = 0; i < col; i++){
        for(int j = 0; j < row; j++){
            tempArr[i * col + j] = matrix[i][j];
        }
    }
    resize(newDim);
    for(int i = 0; i < newCol; i++){
        for(int j = 0; j < newRow; j++){
            matrix[i][j] = tempArr[i * newCol + j];
        }
    }
    delete[] tempArr;
}

template<class T>
void MtmMat<T>::transpose(){
    size_t col = dim.getCol(), row = dim.getCol();
    dim.transpose();
    MtmMat<T> temp(*this);
    reshape(Dimensions(col,row));
    for(int i = 0; i < col; i++){
        for(int j = 0; j < row; j++){
            matrix[j][i] = temp[i][j];
        }
    }
}
