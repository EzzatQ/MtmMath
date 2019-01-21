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
         * Matrix constructor, dim_t is the dimension of the matrix and val is the initial value for the matrix elements
         */
        MtmMat(Dimensions dim_t = Dimensions(1,1), const T& val=T());
        
        explicit MtmMat(const MtmVec<T>& v);
        
        virtual ~MtmMat();
        
        MtmMat(const MtmMat& m);
        
        MtmMat& operator=(const MtmMat& mat);
        
        Dimensions getDim() const{
            return dim;
        }
        
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
        
        class iterator{
        protected:
            typename MtmVec<typename MtmVec<T>::iterator>::iterator itr;
            MtmVec<typename MtmVec<T>::iterator> iterators;
            int pos;
        public:
            
            iterator(MtmMat<T>& m): iterators(0){
                pos =0;
                int size = static_cast<int>(m.dim.getRow());
                for(int i = 0; i < size; i++){
                    typename MtmVec<T>::iterator it = m[i].begin();
                    iterators.push_back(it);
                }
                itr = iterators.begin();
            }
            
            iterator(iterator& i){
                if(*this == i) return;
                itr = i.itr;
                iterators = i.iterators;
            }
            
            iterator& operator=(iterator& i){
                itr = i.itr;
                iterators = i.iterators;
                return *this;
            }
            
            bool operator==(iterator a){
                return (*itr == *a.itr && iterators == a.iterators);
            }
            
            bool operator!=(iterator a){
                return !((*this) == a);
            }
            
            virtual iterator& operator++(){
                if(pos == iterators.size()-1) {
                    itr = iterators.begin();
                    pos = 0;
                    for(int i = 0; i < iterators.size(); i++){
                        ++(iterators[i]);
                    }
                }else{
                    pos++;
                    ++itr;
                }
                return *this;
            }
            
            T& operator*(){
                return *(*itr);
            }
        };
        
        iterator& begin(){
            iterator a(*this);
            return a;
        }
        
        iterator& end(){
            int size = static_cast<int>((this->dim.getRow())*\
                                        (this->dim.getCol()));
            iterator a(*this);
            for(int i = 0; i < size; i++, ++a);
            return a;
        }
        
        class nonzero_iterator: public iterator{
        public:
            
            nonzero_iterator(MtmMat<T>& m): iterator(m){
                if(*(*this) == 0) this->operator++();
            }
            
            explicit nonzero_iterator(iterator i): iterator(i){}
            
            nonzero_iterator& operator++(){
                iterator::operator++();
                try{
                    while(*(*this) == 0){
                        iterator::operator++();
                    }
                    
                } catch(...){
                    return *this;
                }
                return *this;
                
            }
            bool operator==(nonzero_iterator a){
                return iterator::operator==(a);
            }
            
            bool operator!=(nonzero_iterator a){
                return !((*this) == a);
            }
        };
        
        nonzero_iterator& nzbegin(){
            nonzero_iterator a(*this);
            return a;
        }
        
        nonzero_iterator& nzend(){
            nonzero_iterator a(this->end());
            return a;
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
    
    template<class T>
    MtmMat<T>::MtmMat(const MtmVec<T>& v){
        bool isCol = v.is_column();
        size_t size = v.size();
        if(isCol){
            MtmMat<T> newMat(Dimensions(size, 1));
            for(int i = 0; i < size; i++){
                newMat[i][0] = v[i];
            }
        } else{
            MtmMat<T> newMat(Dimensions(1, size));
            for(int i = 0; i < size; i++){
                newMat[0][i] = v[i];
            }
        }
    }
    
    
    //the copy constructor
    template <class T>
    MtmMat<T>::MtmMat(const MtmMat& mat): matrix(MtmVec<MtmVec<T> >()){
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
        dim.transpose();
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
    MtmMat<T> operator*(const MtmMat<T>& a, const MtmMat<T>& b){
        MtmMat<T> c(b);
        return c *= a;
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
    MtmMat<T> operator*(const MtmMat<T>& a, const T& s){
        MtmMat<T> c(a);
        return c *= s;
    }
    
    template <class T>
    MtmMat<T> operator*(const T& s, const MtmMat<T>& a){
        MtmMat<T> c = MtmMat<T>(a * s);
        return c;
    }
    
    template <class T>
    MtmMat<T>& MtmMat<T>::operator*=(const MtmVec<T>& v){
        size_t row = dim.getRow(), col = dim.getCol();
        if(!v.is_column() || v.size() != col){
            throw MtmExceptions::DimensionMismatch();
        }
        MtmMat<T> newMat(Dimensions(row, 1));
        for (int i = 0; i < row;  i++){
            int sum = 0;
            for(int j = 0; j < col; j++){
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
        MtmMat<T> c(m);
        return c *= v;
    }
    
    template<class T>
    MtmMat<T> operator*(const MtmVec<T>& a, const MtmVec<T>& b){
        MtmMat<T> c(a), d(b);
        return c * b;
    }
}


#endif //EX3_MTMMAT_H
