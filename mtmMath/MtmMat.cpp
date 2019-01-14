#include <stdio.h>
#include "MtmMat.h"

using namespace MtmMath;

//the constructor
template <class T>
MtmMat<T>::MtmMat(Dimensions dim_t, const T& val):
matrix(dim_t.getCol(),MtmVec<T>(dim_t.getRow(),val)) , dim(dim_t){
    matrix.transpose();
}

//the copy constructor
template <class T>
MtmMat<T>::MtmMat(const MtmMat& mat): matrix(MtmVec<MtmVec<T>>(1,T())){
    if(dim != mat.dim){
        throw MtmExceptions::DimensionMismatch();
    }
    matrix = mat.matrix;
    dim = mat.dim;
}


//the destructor
template <class T>
MtmMat<T>::~MtmMat<T>(){}


//the assigning operator
template <class T>
MtmMat<T>& MtmMat<T>::operator=(const MtmMat& mat){
    if(this == &mat){
        return *this;
    }
    matrix = mat.matrix;
    dim = mat.dim;
    return *this;
}


//who said func works on columns?
template <class T>
template <typename Func>
MtmVec<T> MtmMat<T>::matFunc(Func& f) const{
    MtmVec<T> output(dim.getCol());
    for(int i = 0; i < dim.getCol(); i++){
        output[i] = matrix[i].vecFunc(f);
    }
    return output;
}

//what should it do exactly?
//switch the places for col and row as arguments
template <class T>
void MtmMat<T>::resize(Dimensions dim, const T& val){
    size_t newCol = dim.getCol();
    size_t newRow = dim.getRow();
    matrix.resize(Dimensions(1, newCol), val);
    size_t colSize = matrix.size();
    for(int i = 0; i < colSize; i++){
        matrix[i].resize(Dimensions(newRow,1), val);
    }
}


//
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


//nice
template<class T>
void MtmMat<T>::transpose(){
    size_t col = dim.getCol(), row = dim.getRow();
    dim.transpose();
    MtmMat<T> temp(*this);
    reshape(Dimensions(col,row));
    for(int i = 0; i < col; i++){
        for(int j = 0; j < row; j++){
            matrix[j][i] = temp[i][j];
        }
    }
}

template <class T>
MtmMat<T>& MtmMat<T>::operator+=(const MtmMat& mat){
    matrix = matrix + mat;
    return *this;
}

template <class T>
MtmMat<T>& MtmMat<T>::operator-=(const MtmMat& mat){
    matrix = matrix - mat;
    return *this;
}

template <class T>
MtmMat<T>& MtmMat<T>::operator+=(const T& s){
    MtmMat<T> mat(dim,s);
    return matrix += mat;
}

template <class T>
MtmMat<T>& MtmMat<T>::operator-=(const T& s){
    MtmMat<T> mat(dim,s);
    return matrix -= mat;
}

template <class T>
MtmMat<T>& MtmMat<T>::operator*=(const MtmMat& mat){
    size_t rows = mat.dim.getRow(), cols=mat.dim.getCol(), thisRows=dim.getRow();
    if(rows != dim.getCol()){
        throw MtmExceptions::DimensionMismatch();
    }
    MtmMat<T> result(Dimensions(thisRows,cols),T());
    for (unsigned int i = 0; i < thisRows; i++) {
        for (unsigned int j = 0; j < cols; j++) {
            T sum = 0;//?
            for (unsigned int m=0; m < rows; m++) {
                sum+= matrix[i][m] * mat.matrix[m][j];
            }
            result[i][j] = sum;
        }
    }
    return &result;
}

template <class T>
MtmMat<T>& MtmMat<T>::operator*=(const T& s){
    size_t cols = dim.getCol();
    MtmMat<T> newMat(Dimensions(cols,cols),0); //is it legal?
    for (int i = 0; i < cols; i++) {
        newMat[i][i]=s;
    }
    return this*=newMat;
}
template <class T>
MtmMat<T>& MtmMat<T>::operator*=(const MtmVec<T>& vec){
    Dimensions d(vec.size(),1);
    if(!vec.column)
        d.transpose();
    MtmMat<T> newMat(d,T());
    int m = 0;
    for (int j = 0; j < d.getCol(); j++) {
        for (int i = 0; i < d.getRow(); i++) {
            newMat[i][j] = vec[m];
            m++;
        }
    }
    return this*=newMat;
}


///////things that need to be templated for all functions




template <class T>
T& operator+(T a,T b){
    if(a!=nullptr)
        return a+=b;
}

template <class T>
T& operator-(T a,T b){
    if(a!=nullptr)
        return a-=b;
}

template <class T, class S>
MtmMat<S>& operator*(MtmMat<S> a,T b){
    if(a!=nullptr)
        return a*=b;
}






