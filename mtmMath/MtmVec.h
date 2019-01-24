#ifndef EX3_MTMVEC_H
#define EX3_MTMVEC_H

#include <vector>
#include <iterator>
#include "MtmExceptions.h"
#include "Auxilaries.h"
#include "Complex.h"

using std::size_t;
using std::vector;

namespace MtmMath {
    template <typename T>
    class MtmVec {
    protected:
        vector<T> vect;
        bool column;
        
    public:
        
        /*
         * Vector constructor, m is the number of elements in it and val is the initial value for the matrix elements
         */
        explicit MtmVec(size_t m , const T& val = T()){
            if(m == 0)
                throw MtmExceptions::IllegalInitialization();
            try{
                vect = vector<T>(m,val);
            } catch(...){
                throw MtmExceptions::OutOfMemory();
            }
            column = true;
        }
        
        MtmVec(){
            MtmVec(1);
        }
        
        /*
         * Vector copy constructor, v is the vector you want to copy, itr will be set to the beginning.
         */
        MtmVec(const MtmVec& v){
            try{
                vect = vector<T>(v.vect);
            }
            catch(...){
                throw MtmExceptions::OutOfMemory();
            }
            column = v.column;
        }
        
        /*
         * Vector operator=, v is the vector you want to assign, itr will be set to the beginning.
         */
        MtmVec& operator=(const MtmVec& v){
            vect = v.vect;
            column = v.column;
            return *this;
        }
        
        MtmVec operator-() const;
        MtmVec& operator+=(const MtmVec& v);
        MtmVec& operator+=(const T& s);
        MtmVec& operator-=(const MtmVec& v);
        MtmVec& operator-=(const T& s);
        MtmVec& operator*=(const T& s);
        bool operator==(const MtmVec<T>& v);
        bool operator!=(const MtmVec<T>& v);
        
        /*
         * Function that get function object f and uses it's () operator on each element in the vectors.
         * It outputs the function object's * operator after iterating on all the vector's elements
         */
        template <typename Func>
        T vecFunc(Func& f) const{
            Func g;
            for(size_t i = 0; i < vect.size(); i++){
                g(vect[i]);
            }
            return *g;
        }
        
        /*
         * First operator[]  of the matrix, returns a vector which is the i'th row
         * if you try to access an illegal element, method will throw AccessIllegalElement exception;
         */
        T& operator[](const size_t i){
            if(i >= vect.size()) {
                throw MtmExceptions::AccessIllegalElement();
            }
            return vect[i];
        }
        
        const T& operator[](const size_t i) const{
            if(i >= vect.size()){
                throw MtmExceptions::AccessIllegalElement();
            }
            return vect[i];
        }
        
        /*
         *returns size of vector
         */
        size_t size() const{
            return vect.size();
        }
        
        size_t size(){
            return vect.size();
        }
        
        /*
         * Iterator allows you to go through all the elements in the vector one by one
         * you can start an iterator with the begin() method of the vector and needs to be compared
         * with end() method to see when you have reached the end
         */
        class iterator{
            
            typename vector<T>::iterator itr;
            size_t pos;
            size_t endPos;
            
        public:
            
            iterator(MtmVec<T>& v){
                typename vector<T>::iterator itr2 = (v.vect).begin();
                itr = itr2;
                pos = 0;
                endPos = v.size();
            }
            
            iterator(){}
            
            iterator& operator=(const iterator& a){
                itr = a.itr;
                pos = a.pos;
                endPos = a.endPos;
                return *this;
            }
            bool operator==(const iterator a){
                return (this->itr == a.itr && pos == a.pos);
            }
            bool operator!=(const iterator a){
                return !((*this) == a);
            }
            
            virtual iterator& operator++(){
                ++(this->itr);
                pos++;
                return *this;
            }
            
            T& operator*(){
                if(pos >= endPos){
                    throw MtmExceptions::AccessIllegalElement();
                }
                return *(this->itr);
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
         * to be used to compare iterator with the end of the vector
         */
        iterator end(){
            iterator a(*this);
            for(size_t i = 0; i < this->size() ; i++, ++a);
            return a;
        }
        
        /*
         * Iterator allows you to go through all the elements that aren't zero in the vector one by one
         * you can start an iterator with the nzbegin() method of the vector and needs to be compared
         * with nzend() method to see when you have reached the end
         */
        class nonzero_iterator: public iterator{
        public:
            
            nonzero_iterator(MtmVec<T>& v): iterator(v){
                if(*(*this) == T(0)) this->operator++();
            }
            
            explicit nonzero_iterator(const iterator a): iterator(a){}
            
            nonzero_iterator& operator++() override{
                try{
                    iterator::operator++();
                    while(*(*this) == 0){
                        iterator::operator++();
                    }
                    return *this;
                }
                catch(...){
                    return *this;
                }
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
            nonzero_iterator a(this->end());
            return a;
        }
        
        /*
         * Resizes a vector to dimension dim, new elements gets the value val.
         * Notice vector cannot transpose through this method.
         */
        void resize(Dimensions dim, const T& val=T());
        
        
        /*
         * Performs transpose operation on matrix
         */
        void transpose(){
            column = !column;
        }
        
        /*
         * Adds an element to the end of the vector
         */
        void push_back(const T& val = T()){
            vect.push_back(val);
        }
        
        /*
         * Removes an element from the end of the vector
         */
        void pop_back(){
            vect.pop_back();
        }
        
        /*
         * Returns if vector is a row vector or a column vector
         */
        bool is_column() const{
            return column;
        }
    };
    
    template <class T>
    MtmVec<T> MtmVec<T>::operator-() const{
        MtmVec<T> a(*this);
        for(size_t i  = 0; i < a.size(); i++){
            a[i] = -(*this)[i];
        }
        return a;
    }
    
    template <class T>
    MtmVec<T>& MtmVec<T>::operator+=(const MtmVec& v){
        size_t thisSize = size();
        if(thisSize != v.size() || (is_column() != v.is_column())) {
            Dimensions thisDim, vDim;
            thisDim = is_column() ? Dimensions(size(), 1):Dimensions(1, size());
            vDim = v.is_column() ? Dimensions(v.size(), 1):Dimensions(1, v.size());
            throw MtmExceptions::DimensionMismatch(thisDim, vDim);
        }
        for(size_t i = 0; i < thisSize; i++){
            vect[i] += v[i];
        }
        return *this;
    }
    
    template <class T>
    MtmVec<T> operator+(const MtmVec<T>& v1, const MtmVec<T> v2){
        MtmVec<T> v3(v1);
        return v3 += v2;
    }
    
    template <class T>
    MtmVec<T>& MtmVec<T>::operator+=(const T& s){
        for(size_t i = 0; i < size(); i++){
            vect[i] += s;
        }
        return *this;
    }
    
    template <class T>
    MtmVec<T> operator+(const MtmVec<T>& v1, const T& s){
        MtmVec<T> v2(v1);
        return v2 += s;
    }
    
    template <class T>
    MtmVec<T> operator+(const T& s, const MtmVec<T>& v1){
        MtmVec<T> v2(v1);
        return v2 += s;
    }
    
    template <class T>
    MtmVec<T>& MtmVec<T>::operator-=(const MtmVec& v){
        return (*this) += -v;
    }
    
    template <class T>
    MtmVec<T> operator-(const MtmVec<T>& v1, const MtmVec<T> v2){
        MtmVec<T> v3(v1);
        return v3 -= v2;
    }
    
    template <class T>
    MtmVec<T>& MtmVec<T>::operator-=(const T& s){
        return (*this) += -s;
    }
    
    template <class T>
    MtmVec<T> operator-(const MtmVec<T>& v1, const T& s){
        MtmVec<T> v2(v1);
        return v2 -= s;
    }
    
    template <class T>
    MtmVec<T> operator-(const T& s, const MtmVec<T>& v1){
        return (-v1) + s;
    }
    
    template <class T>
    MtmVec<T>& MtmVec<T>::operator*=(const T& s){
        for(size_t i = 0; i < size(); i++){
            vect[i] *= s;
        }
        return *this;
    }
    
    template <class T>
    MtmVec<T> operator*(const MtmVec<T>& v, const T& s){
        MtmVec<T> v2(v);
        return v2 *= s;
    }
    
    template <class T>
    MtmVec<T> operator*(const T& s, const MtmVec<T>& v){
        return v * s;
    }
    
    template <class T>
    bool MtmVec<T>::operator==(const MtmVec<T>& v){
        if(v.size() == (*this).size()){
            for(size_t i = 0; i < v.size(); i++){
                T a = v[i], b = (*this)[i];
                if(a != b)
                    return false;
            }
            return true;
        } else
            return false;
    }
    
    template<class T>
    bool MtmVec<T>::operator!=(const MtmVec<T>& v){
        return !(*this == v);
    }
    
    template <class T>
    void MtmVec<T>::resize(Dimensions dim, const T& val){
        size_t col = dim.getCol(), row = dim.getRow();
        Dimensions thisDim;
        thisDim = is_column() ? Dimensions(size(), 1):Dimensions(1, size());
        if(col != 1 && row != 1){
            throw MtmExceptions::ChangeMatFail(thisDim, dim);
        }
        if(((column && col != 1) || (!column && row != 1))){
            throw MtmExceptions::ChangeMatFail(thisDim, dim);
        }
        size_t newDim = column ? row : col;
        size_t oldDim = vect.size();
        if(newDim == oldDim) return;
        vect.resize(newDim, val);
        dim = newDim;
    }

    
}

#endif //EX3_MTMVEC_H
