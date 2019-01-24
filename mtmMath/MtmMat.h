#ifndef EX3_MTMMAT_H
#define EX3_MTMMAT_H


#include <vector>
#include "MtmExceptions.h"
#include "Auxilaries.h"
#include "MtmVec.h"
#include "Complex.h"

using std::size_t;

namespace MtmMath {
    
    template <typename T>
    class MtmMat{
    protected:
        MtmVec<MtmVec<T> > matrix;
        Dimensions dim;
        
    public:
        /*
         * Matrix constructor, dim_t is the dimension of the matrix and val is the initial value for the
         * matrix elements
         */
        MtmMat(Dimensions dim_t = Dimensions(1,1), const T& val=T());
        
        explicit MtmMat(const MtmVec<T>& v);
        
        virtual ~MtmMat();
        
        MtmMat(const MtmMat& m);
        
        MtmMat& operator=(const MtmMat& mat);
        MtmMat operator-() const;
        bool operator==(const MtmMat& m){
            return (matrix == m.matrix && dim == m.dim);
        }
        MtmMat& operator+=(const MtmMat& m);
        MtmMat& operator+=(const T& s);
        MtmMat& operator-=(const MtmMat& m);
        MtmMat& operator-=(const T& s);
        MtmMat& operator*=(const MtmMat& m);
        MtmMat& operator*=(const T& s);
        MtmMat& operator*=(const MtmVec<T>& v);
        
        
        /*
         * Returns Dimenstions of Martix.
         */
        Dimensions getDim() const{
            return dim;
        }
        
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
        
        /*
         * First operator[]  of the matrix, returns a vector which is the i'th row
         * if you try to access an illegal element, method will throw AccessIllegalElement exception;
         */
        MtmVec<T>& operator[](const size_t i){
            if(i >= dim.getRow()){
                throw MtmExceptions::AccessIllegalElement();
            }
            return matrix[i];
        }
        
        const MtmVec<T>& operator[](const size_t i) const{
            if(i >= dim.getRow()){
                throw MtmExceptions::AccessIllegalElement();
            }
            return matrix[i];
        }
        
        /*
         * Iterator allows you to go through all the elements in the matrix by linear indecees
         * you can start an iterator with the begin() method of the vector and needs to be compared
         * with end() method to see when you have reached the end
         */
        class iterator{
        protected:
            MtmMat<T>& matrix;
            size_t i;
            size_t j;
            
        public:
            
            iterator(MtmMat<T>& m): matrix(m), i(0), j(0){}
            
            iterator(const iterator& it): matrix(it.matrix){
                matrix = it.matrix;
                i = it.i;
                j = it.j;
            }
            
            iterator& operator=(const iterator& i){
                *this = iterator(i);
                return *this;
            }
            
            bool operator==(const iterator a) const{
                return (matrix == a.matrix && i == a.i && j == a.j);
            }
            
            bool operator!=(const iterator a) const{
                return !((*this) == a);
            }
            
            virtual iterator& operator++(){
                if(i == matrix.getDim().getRow()-1){
                    i = 0;
                    if(j <= matrix.getDim().getCol()-1)
                        j++;
                }else{
                    if(!(i == 0 && j== matrix.getDim().getCol()))
                        i++;
                }
                return *this;
            }
            
            virtual T& operator*(){
                if(i < matrix.getDim().getRow() && j < matrix.getDim().getCol())
                    return matrix[i][j];
                throw MtmExceptions::AccessIllegalElement();
            }
        };
        
        /*
         * to be used to initialize an iterator
         */
        iterator begin(){
            iterator a(*this);
            return a;
        }
        
        /*
         * to be used to compare iterator with the end of the matrix
         */
        iterator end(){
            int size = static_cast<int>((this->dim.getRow())*\
                                        (this->dim.getCol()));
            iterator a(*this);
            for(int i = 0; i < size; i++, ++a);
            return a;
        }
        
        /*
         * nonzero_terator allows you to go through all the elements in the matrix by linear indecees
         * that are not zero.
         * you can start an iterator with the nzbegin() method of the matrix and needs to be compared
         * with nzend() method to see when you have reached the end
         */
        class nonzero_iterator: public iterator{
        public:
           explicit nonzero_iterator(iterator i): iterator(i){}
            
            nonzero_iterator(MtmMat<T>& m = MtmMat<T>()): iterator(m){
                if(*(*this) == 0) this->operator++();
            }
            
            nonzero_iterator& operator++(){
                iterator::operator++();
                try{
                    while(*(*this) == 0){
                        iterator::operator++();
                        
                    }
                }catch(MtmExceptions::AccessIllegalElement& e){
                    return *this;
                }
                return *this;
                
            }
            
            bool operator==(const nonzero_iterator a) const{
                return iterator::operator==(a);
            }
            
            bool operator!=(const nonzero_iterator a) const{
                return !((*this) == a);
            }
            
            bool operator==(const iterator a) const{
                return iterator::operator==(a);
            }
            
            bool operator!=(const iterator a) const{
                return !((*this) == a);
            }
        };
        
        /*
         * to be used to initialize an nonzero_iterator
         */
        nonzero_iterator nzbegin(){
            nonzero_iterator a(*this);
            return a;
        }
        
        /*
         * to be used to compare a nonzero_iterator with the end of the vector
         */
        nonzero_iterator nzend(){
            nonzero_iterator a(end());
            return a;
        }
        
    };
    
    /*
     * Constructers of MtmMat
     */
    template <class T>
    MtmMat<T>::MtmMat(Dimensions dim_t, const T& val):
    matrix(dim_t.getRow(),MtmVec<T>(dim_t.getCol(),val)) , dim(dim_t){
        for(size_t i = 0; i < dim_t.getRow(); i++){
            matrix[i].transpose();
        }
    }
    
    template<class T>
    MtmMat<T>::MtmMat(const MtmVec<T>& v){
        bool isCol = v.is_column();
        size_t size = v.size();
        if(isCol){
            MtmMat<T> newMat(Dimensions(size, 1));
            for(size_t i = 0; i < size; i++){
                newMat[i][0] = v[i];
            }
            *this = newMat;
        } else{
            MtmMat<T> newMat(Dimensions(1, size));
            for(size_t i = 0; i < size; i++){
                newMat[0][i] = v[i];
            }
            *this = newMat;
        }
        
    }
    
    /*
     * Copy Constructers
     */
    template <class T>
    MtmMat<T>::MtmMat(const MtmMat& mat): matrix(MtmVec<MtmVec<T> >()){
        matrix = mat.matrix;
        dim = mat.dim;
    }
    
    /*
     * Destructer
     */
    template <class T>
    MtmMat<T>::~MtmMat<T>(){}
    
    
    /*
     * Assignment operator
     */
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
            for(size_t i = 0; i < col; i++){
                output[i] = matrix[i].vecFunc(f);
            }
        } else {
            output = MtmVec<T>(col);
            MtmMat<T> temp(*this);
            temp.transpose();
            for(size_t i = 0; i < col; i++){
                output[i] = temp[i].vecFunc(f);
            }
        }
        return output;
    }
    
    template <class T>
    void MtmMat<T>::resize(Dimensions newDim, const T& val){
        if(newDim == dim) return;
        size_t newRow = newDim.getRow(), newCol = newDim.getCol();
        for(size_t i = 0; i < dim.getRow(); i++){
            matrix[i].resize(Dimensions(1, newCol),val);
        }
        MtmVec<T> m = MtmVec<T>(newCol,val);
        m.transpose();
        matrix.resize(Dimensions(newRow, 1), m);
        dim = newDim;
    }
    
    template <class T>
    void MtmMat<T>::reshape(Dimensions newDim){
        size_t newCol = newDim.getCol(), newRow = newDim.getRow();
        size_t col = dim.getCol(), row = dim.getRow();
        if(newCol * newRow != col * row){
            throw MtmExceptions::ChangeMatFail(dim, newDim);
        }
        T* tempArr = new T[col*row];
        for(size_t j = 0; j < col; j++){
            for(size_t i = 0; i < row; i++){
                tempArr[j * row + i] = matrix[i][j];
            }
        }
        resize(newDim);
        size_t k = 0;
        for(size_t j = 0; j < newCol; j++){
            for(size_t i = 0; i < newRow; i++){
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
        for(size_t i = 0; i < col; i++){
            for(size_t j = 0; j < row; j++){
                matrix[i][j] = temp[j][i];
            }
        }
    }
    
    template <class T>
    MtmMat<T> MtmMat<T>::operator-() const{
        size_t row = dim.getRow(), col = dim.getCol();
        MtmMat<T> temp(*this);
        for(size_t i = 0; i < row; i++){
            for(size_t j = 0; j < col; j++){
                temp[i][j] = -(*this)[i][j];
            }
        }
        return temp;
    }
    
    template <class T>
    MtmMat<T>& MtmMat<T>::operator+=(const MtmMat<T>& m){
        if(dim != m.dim){
            throw MtmExceptions::DimensionMismatch(dim, m.dim);
        }
        size_t row = dim.getRow(), col = dim.getCol();
        for(size_t i = 0; i < row; i++){
            for(size_t j = 0; j < col; j++){
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
        for(size_t i = 0; i < row; i++){
            for(size_t j = 0; j < col; j++){
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
    MtmMat<T> operator+(const T& s, const MtmMat<T>& a){
        return a + s;
    }
    
    template <class T>
    MtmMat<T> operator+(const MtmMat<T>& m, const MtmVec<T>& v){
        MtmMat<T> temp(v);
        return m + temp;
    }
    
    template <class T>
    MtmMat<T> operator+(const MtmVec<T>& v, const MtmMat<T>& m){
        MtmMat<T> temp(v);
        return m + temp;
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
    MtmMat<T> operator-(const T& s, const MtmMat<T>& a){
        return (-a) + s;
    }
    
    template <class T>
    MtmMat<T> operator-(const MtmMat<T>& m, const MtmVec<T>& v){
        MtmMat<T> temp(v);
        return m + (-temp);
    }
    
    template <class T>
    MtmMat<T> operator-(const MtmVec<T>& v, const MtmMat<T>& m){
        MtmMat<T> temp(v);
        return temp + (-m);
    }
    
    template <class T>
    MtmMat<T>& MtmMat<T>::operator*=(const MtmMat<T>& m){
        size_t mRow = m.dim.getRow(), mCol = m.dim.getCol();
        size_t row = dim.getRow(), col = dim.getCol();
        if(mRow != col){
            throw MtmExceptions::DimensionMismatch(dim ,m.dim );
        }
        MtmMat<T> result(Dimensions(row,mCol),T());
        for (size_t i = 0; i < row; i++) {
            for (size_t j = 0; j < mCol; j++) {
                T sum = 0;
                for (size_t k = 0; k < col; k++) {
                    sum+= (*this)[i][k] * m[k][j];
                }
                result[i][j] = sum;
            }
        }
        (*this) = result;
        return *this;
    }
    
    template <class T>
    MtmMat<T> operator*(const MtmMat<T>& a, const MtmMat<T>& b){
        MtmMat<T> c(a);
        return c *= b;
    }
    
    template <class T>
    MtmMat<T>& MtmMat<T>::operator*=(const T& s){
        size_t col = dim.getCol();
        MtmMat<T> newMat(Dimensions(col,col),0);
        for (size_t i = 0; i < col; i++) {
            newMat[i][i] = s;
        }
        return (*this) *= newMat;
    }
    
    template <class T>
    MtmMat<T> operator*(const MtmMat<T>& a, const T& s){
        MtmMat<T> c(a);
        return c *= s;
    }
    
    template <class T>
    MtmMat<T> operator*(const T& s, const MtmMat<T>& a){
        return a * s;
    }
    
    template <class T>
    MtmMat<T>& MtmMat<T>::operator*=(const MtmVec<T>& v){
        size_t row = dim.getRow(), col = dim.getCol();
        if(!v.is_column() || v.size() != col){
            throw MtmExceptions::DimensionMismatch(dim, Dimensions(row, 1));
        }
        MtmMat<T> newMat(Dimensions(row, 1));
        for (size_t i = 0; i < row;  i++){
            int sum = 0;
            for(size_t j = 0; j < col; j++){
                sum += ((*this)[i][j] * v[j]);
            }
            newMat[i][0] = sum;
        }
        (*this) = newMat;
        return *this;
    }
    
    template <class T>
    MtmMat<T> operator*(const MtmMat<T>& m, const MtmVec<T>& v){
        MtmMat<T> c(m);
        return c *= v;
    }
    
    template <class T>
    MtmMat<T> operator*(const MtmVec<T>& v, const MtmMat<T>& m){
        MtmMat<T> c(v);
        return c * m;
    }
    
    template<class T>
    MtmMat<T> operator*(const MtmVec<T>& a, const MtmVec<T>& b){
        MtmMat<T> c(a), d(b);
        return c * d;
    }
}

#endif //EX3_MTMMAT_H
