#ifndef EX3_MTMMAT_H
#define EX3_MTMMAT_H


#include <vector>
#include "MtmExceptions.h"
#include "Auxilaries.h"
#include "MtmVec.h"

using std::size_t;

//typedef int T;

namespace MtmMath {

    template <typename T>
    class MtmMat {
    public:
        //protected:
        MtmVec<MtmVec<T> > matrix;
        Dimensions dim;
    public:
        /*
         * Matrix constructor, dim_t is the dimension of the matrix and val is the initial value for the matrix elements
         */
        MtmMat(Dimensions dim_t, const T& val=T());
        
        MtmMat(){
            MtmMat(Dimensions(1, 1));
        }
        
        ~MtmMat(); //
        
        MtmMat(const MtmMat& m);
        
        MtmMat& operator=(const MtmMat& mat);
        
        //might need changing
        MtmMat& operator+=(const MtmMat& mat);
        MtmMat& operator+=(const T& s);
        MtmMat& operator-=(const MtmMat& mat);
        MtmMat& operator-=(const T& s);
        MtmMat& operator*=(const MtmMat& mat);
        MtmMat& operator*=(const T& s);
        MtmMat& operator*=(const MtmVec<T>& vec);
        /*
         * Function that get function object f and uses it's () operator on each element in the matrix columns.
         * It outputs a vector in the size of the matrix columns where each element is the final output
         * by the function object's * operator
         */
        template <typename Func>
        MtmVec<T> matFunc(Func& f) const;

        /*
         * resizes a matrix to dimension dim, new elements gets the value val.
         */
        virtual void resize(Dimensions dim, const T& val=T());

        /*
         * reshapes matrix so linear elements value are the same without changing num of elements.
         */
        virtual void reshape(Dimensions newDim);

        /*
         * Performs transpose operation on matrix
         */
        virtual void transpose();
        
        MtmVec<T>& operator[](const int i){
            if(i >= dim.getCol()){
                throw MtmExceptions::AccessIllegalElement();
            }
            return matrix[i];
        }
        
        const MtmVec<T>& operator[](const int i) const{//what to do here..?
            if(i >= dim.getCol()){
                throw MtmExceptions::AccessIllegalElement();
            }
            return matrix[i];
        }

    };
    
    //the constructor
    template <class T>
    MtmMat<T>::MtmMat(Dimensions dim_t, const T& val):
    matrix(dim_t.getRow(),MtmVec<T>(dim_t.getCol(),val)) , dim(dim_t){
        for(int i = 0; i < dim_t.getRow(); i++){
        matrix.transpose();
        }
    }
    
    //the copy constructor
    template <class T>
    MtmMat<T>::MtmMat(const MtmMat& mat): matrix(MtmVec<MtmVec<T> >(1,T())){
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
        MtmVec<T> output(dim.getRow());
        for(int i = 0; i < dim.getRow(); i++){
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
        matrix.resize(Dimensions(1, newRow), MtmVec<T>());//// its calling the matrix resize not the vect one
        for(int i = 0; i < newRow; i++){
            matrix[i].resize(Dimensions(newCol,1), val);
        }
    }
    
    
    //
    template <class T>
    void MtmMat<T>::reshape(Dimensions newDim){
        size_t newCol = newDim.getCol(), newRow = newDim.getRow();
        size_t col = dim.getCol(), row = dim.getRow();
        if(newCol * newRow != col * row){
            throw MtmExceptions::DimensionMismatch();
        }
        T* tempArr = new T[col*row];
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
        size_t row = dim.getRow(), col = dim.getCol();
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
        size_t rows = mat.dim.getRow(), cols = mat.dim.getCol(), thisRows = dim.getRow();///////////// get row/col for mat
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
            newMat[i][i] = s;
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
        if(a != nullptr)
            return a += b;
    }
    
    template <class T>
    T& operator-(T a,T b){
        if(a != nullptr)
            return a -= b;
    }
    
    template <class T, class S>
    MtmMat<S>& operator*(MtmMat<S> a,T b){
        if(a != nullptr)
            return a *= b;
    }
    
    
}


#endif //EX3_MTMMAT_H
