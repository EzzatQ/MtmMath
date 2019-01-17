#ifndef EX3_MTMVEC_H
#define EX3_MTMVEC_H

#include <vector>
#include <iterator>
#include "MtmExceptions.h"
#include "Auxilaries.h"
#include "Complex.h"

using std::size_t;
using std::vector;

//typedef int T;

namespace MtmMath {
    template <typename T>
    class MtmVec {
   // public:////////////////////////
        vector<T> vect;
        bool column;

        
    public:
        
        class end_of_vector{};
        class start_of_vector{};
        
        /*
         * Vector constructor, m is the number of elements in it and val is the initial value for the matrix elements
         */
        explicit MtmVec(size_t m, const T& val = T()){
            vect = vector<T>(m,val);
            column = true;
        }
        
        MtmVec(){
            MtmVec(1);
        }

        
        /*
         * Vector copy constructor, v is the vector you want to copy, itr will be set to the beginning.
         */
        MtmVec(const MtmVec& v){
            vect = vector<T>(v.vect);
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
        
        MtmVec operator-();
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
            for(int i = 0; i < vect.size(); i++){
                g(vect[i]);
            }
            return *g;
        }
        
        T& operator[](const int i){
            if(i >= vect.size()) {
                throw MtmExceptions::AccessIllegalElement();
            }
            return vect[i];
        }
        
        const T& operator[](const int i) const{
            if(i >= vect.size()){
                throw MtmExceptions::AccessIllegalElement();
            }
            return vect[i];
        }
        
        size_t size() const{
            return vect.size();
        }
        
        size_t size(){
            return vect.size();
        }
        
        class nonzero_iterator;
        class iterator{
        protected:
            MtmVec<T>* data;
            int pos;
            int endPos;
        public:
            
            iterator(MtmVec<T>& a, int i = 0) : data(NULL){
                if(i < 0){
                    throw MtmExceptions::AccessIllegalElement();
                }
                data = &a;
                pos = i;
                endPos = a.size();
            }
            
            iterator(const iterator& i){
                iterator a(*(i.data), i.pos);
                *this = a;
            }
            
            iterator& operator=(const iterator& a){
                pos = a.pos;
                data = a.data;
                endPos = a.endPos;
                return *this;
            }
            
            bool operator==(const iterator& a){
                if(data != a.data) return false;
                if(pos == a.pos) return true;
                return false;
            }
            
            bool operator!=(const iterator& a){
                return !((*this) == a);
            }
            
            virtual iterator& operator++(){
                    pos++;
                return *this;
            }
            
            T& operator*(){
                return (*(data))[pos];
            }
            /////////////
            void printItr(){
                std::cout << "itr is at (" << pos << ") \n";
            }
            ////////////
        };
        
        iterator begin(){
            iterator a(*this);
            return a;
        }
        
        iterator end(){
            iterator a(*this, this->size());
            return a;
        }
        
        class nonzero_iterator: public iterator{
        public:
            
            nonzero_iterator(MtmVec<T>& a, int i = 0): iterator(a){
                if(*(*this) == 0) this->operator++();
            }
            
            explicit nonzero_iterator(iterator i): iterator(*(i.getData())){}
            
            nonzero_iterator& operator++() override{
                do{
                    iterator::operator++();
                } while(this->pos != this->endPos && *(*this) == 0);
                return *this;
            }
            
        };
        
        nonzero_iterator nzbegin(){
            nonzero_iterator a(*this);
            return a;
        }
        
        nonzero_iterator nzend(){
            nonzero_iterator a(*this, this->endPos);
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
        
        void push_back(const T& val){
            vect.push_back(val);
        }
        
        void pop_back(){
            vect.pop_back();
        }
        
        bool is_column() const{
            return column;
        }
        
        
    };
    
    template <class T>
    MtmVec<T> MtmVec<T>::operator-(){
        MtmVec<T> a(*this);
        for(int i  = 0; i < a.size(); i++){
            a[i] = (*this)[i];
        }
        return a;
    }
    
    template <class T>
    MtmVec<T>& MtmVec<T>::operator+=(const MtmVec& v){
        size_t thisSize = size();
        if(thisSize != v.size()) {
            throw MtmExceptions::DimensionMismatch();
        }
        for(int i = 0; i < thisSize; i++){
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
        for(int i = 0; i < size(); i++){
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
        MtmVec<T> v2(v1);
        return v2 -= s;
    }
    
    template <class T>
    MtmVec<T>& MtmVec<T>::operator*=(const T& s){
        for(int i = 0; i < size(); i++){
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
            for(int i = 0; i < v.size(); i++){
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
        if(col != 1 && row != 1){
            throw MtmExceptions::DimensionMismatch();
        }
        if(((column && col != 1) || (!column && row != 1))){
            throw MtmExceptions::DimensionMismatch();
        }
        size_t newDim = column ? row : col;
        size_t oldDim = vect.size();
        if(newDim == oldDim) return;
        if(newDim > oldDim){
            while(oldDim != newDim){
                vect.push_back(val);
                oldDim++;
            }
        }
        if(newDim < oldDim){
            vect.resize(newDim);
            vect.shrink_to_fit();
        }
        dim = newDim;
    }
        
    
        
}

#endif //EX3_MTMVEC_H
