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
        MtmMat(Dimensions dim_t = Dimensions(1,1), const T& val=T());
        
        ~MtmMat();
        
        MtmMat(const MtmMat& m);
        
        MtmMat& operator=(const MtmMat& mat);
        
        //might need changing
        MtmMat& operator-();
        MtmMat& operator+=(const MtmMat& m);
        MtmMat& operator+=(const T& s);
        MtmMat& operator-=(const MtmMat& m);
        MtmMat& operator-=(const T& s);
        MtmMat& operator*=(const MtmMat& m);
        MtmMat& operator*=(const T& s);
        MtmMat& operator*=(const MtmVec<T>& v);
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
            if(i >= dim.getRow()){
                throw MtmExceptions::AccessIllegalElement();
            }
            return matrix[i];
        }
        
        const MtmVec<T>& operator[](const int i) const{
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
            matrix[i].transpose();
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
    MtmMat<T>& MtmMat<T>::operator=(const MtmMat<T>& mat){
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
        MtmVec<T> output;
        size_t col = dim.getCol();
        if(!matrix.is_column()){
            output = MtmVec<T>(col);
            for(int i = 0; i < col; i++){
                output[i] = matrix[i].vecFunc(f);
            }
        } else {
            output = MtmVec<T>(col);
            MtmMat<T> temp(*this);
            temp.transpose();
            for(int i = 0; i < col; i++){
                output[i] = temp[i].vecFunc(f);
            }
        }
        return output;
    }
    
    template <class T>
    void MtmMat<T>::resize(Dimensions newDim, const T& val){
         if(newDim == dim) return;
        size_t newRow = newDim.getRow(), newCol = newDim.getCol();
        size_t row = dim.getRow(), col = dim.getCol();
        bool isCol = matrix.is_column();
        size_t Old = isCol ? row : col;
        size_t New = isCol ? newRow : newCol;
        if(New < Old){
            while(New != Old){
                matrix.pop_back();
                Old--;
            }
        } else if(New > Old){
            while(New != Old){
                matrix.push_back(MtmVec<T>());
                Old++;
            }
        }
        dim = newDim;
        for(int i = 0; i < New; i++){
            if(matrix[0].is_column()){
            matrix[i].resize(Dimensions(newRow,1), val);
            } else matrix[i].resize(Dimensions(1,newCol), val);
        } 
    }
    
    template <class T>
    void MtmMat<T>::reshape(Dimensions newDim){
        size_t newCol = newDim.getCol(), newRow = newDim.getRow();
        size_t col = dim.getCol(), row = dim.getRow();
        if(newCol * newRow != col * row){
            throw MtmExceptions::DimensionMismatch();
        }
        T* tempArr = new T[col*row];
        for(int j = 0; j < col; j++){
            for(int i = 0; i < row; i++){
                tempArr[j * row + i] = matrix[i][j];
            }
        }
        resize(newDim);
        int k = 0;
        for(int j = 0; j < newCol; j++){
            for(int i = 0; i < newRow; i++){
                matrix[i][j] = tempArr[k++];
            }
        }
        delete[] tempArr;
    }
    
    
    template<class T>
    void MtmMat<T>::transpose(){
        size_t row = dim.getRow(), col = dim.getCol();
        MtmMat<T> temp(*this);
        *this = MtmMat<T>(Dimensions(col,row));
        size_t tmp = col;//???
        col = row;//???
        row = tmp;//???
        for(int i = 0; i < col; i++){
            for(int j = 0; j < row; j++){
                matrix[j][i] = temp[i][j];
            }
        }
    }
    
    template <class T>
    MtmMat<T>& MtmMat<T>::operator-(){
        size_t row = dim.getRow(), col = dim.getCol();
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                (*this)[i][j] = -(*this)[i][j];
            }
        }
        return *this;
    }
    
    template <class T>
    MtmMat<T>& MtmMat<T>::operator+=(const MtmMat<T>& m){
        if(dim != m.dim){
            throw MtmExceptions::DimensionMismatch();
        }
        size_t row = dim.getRow(), col = dim.getCol();
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                (*this)[i][j] += m[i][j];
            }
        }
        return *this;
    }
    
    template <class T>
    MtmMat<T> operator+(const MtmMat<T>& a, const MtmMat<T>& b){
        MtmMat<T> c(a);
        c += b;
        return c;
    }
    
    template <class T>
    MtmMat<T>& MtmMat<T>::operator+=(const T& s){
        size_t row = dim.getRow(), col = dim.getCol();
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                (*this)[i][j] += s;
            }
        }
        return *this;
    }
    
    template <class T>
    MtmMat<T> operator+(const MtmMat<T>& a, const T& s){
        MtmMat<T> c(a);
        c += s;
        return c;
    }
    
    template <class T>
    MtmMat<T>& MtmMat<T>::operator-=(const MtmMat<T>& m){
        MtmMat<T> a(m);
        return (*this) += -a;
        
    }
    
    template <class T>
    MtmMat<T> operator-(const MtmMat<T>& a, const MtmMat<T>& b){
        MtmMat<T> c(a);
        MtmMat<T> d(b);
        c += -d;
        return c;
    }
    
    template <class T>
    MtmMat<T>& MtmMat<T>::operator-=(const T& s){
        return (*this) += -s;
    }
    
    template <class T>
    MtmMat<T> operator-(const MtmMat<T>& a, const T& s){
        MtmMat<T> c(a);
        c += -s;
        return c;
    }
    
    template <class T>
    MtmMat<T>& MtmMat<T>::operator*=(const MtmMat<T>& m){
        size_t mRow = m.dim.getRow(), mCol = m.dim.getCol();
        size_t row = dim.getRow(), col = dim.getCol();
        if(mRow != col){
            throw MtmExceptions::DimensionMismatch();
        }
        MtmMat<T> result(Dimensions(mRow,col),T());
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < mCol; j++) {
                T sum = 0;
                for (int k = 0; k < row; k++) {
                    sum+= (*this)[i][k] * m[k][j];
                }
                result[i][j] = sum;
            }
        }
        (*this) = result;
        return *this;
    }
    
    template <class T>
    MtmMat<T>& MtmMat<T>::operator*=(const T& s){
        size_t col = dim.getCol();
        MtmMat<T> newMat(Dimensions(col,col),0);
        for (int i = 0; i < col; i++) {
            newMat[i][i] = s;
        }
        return (*this) *= newMat;
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
    
    /*template <class T>
    MtmMat<T> operator+(const MtmMat<T>& a,const MtmMat<T> b){
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
    }*/
    
    
}


#endif //EX3_MTMMAT_H
