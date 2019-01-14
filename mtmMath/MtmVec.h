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
    public:////////////////////////
        vector<T> vect;
        typename vector<T>::iterator itr;
        bool column;

        
    public:
        
        class end_of_vector{};
        class start_of_vector{};
        
        /*
         * Vector constructor, m is the number of elements in it and val is the initial value for the matrix elements
         */
        MtmVec(size_t m, const T& val = T()){
            vect = vector<T>(m,val);
            itr = vect.begin();
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
            itr = vect.begin();
            column = v.column;
        }
        
        /*
         * Vector operator=, v is the vector you want to assign, itr will be set to the beginning.
         */
        MtmVec& operator=(const MtmVec& v){
            vect = v.vect;
            itr = vect.begin();
            column = v.column;
            return *this;
        }
        
        typename vector<T>::iterator getItr() const{
            return itr;
        }
        
        void resetItr(){
            itr = vect.begin();
        }
        
        void advanceItr(){
            typename vector<T>::iterator temp = next(itr, 1);
            if(temp == vect.end()){
                return;//throw end_of_vector();
            }
            itr = temp;
        }
        
        void reverseItr(){
            typename vector<T>::iterator temp = prev(itr, 1);
            if(temp == vect.begin()){
                return; //throw start_of_vector();
            }
            itr = temp;
        }

        /*
         * Function that get function object f and uses it's () operator on each element in the vectors.
         * It outputs the function object's * operator after iterating on all the vector's elements
         */
        template <typename Func>
        T vecFunc(Func& f) const{
            for(int i = 0; i < vect.size(); i++){
                f(vect[i]);
            }
            return *f;///////////
        }
        
        T& operator[](const int i){
            //std::cout << "i = " << i << ", size = " << vect.size()<<   std::endl;
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
        
        size_t size(){
            return vect.size();
        }

        /*
         * Resizes a vector to dimension dim, new elements gets the value val.
         * Notice vector cannot transpose through this method.
         */
        void resize(Dimensions dim, const T& val=T()){
            size_t col = dim.getCol(), row = dim.getRow();
            if(col != 1 && row != 1){
                throw MtmExceptions::DimensionMismatch();
            }
            if((column && col != 1) || (!column && row != 1)){
                throw MtmExceptions::DimensionMismatch();
            }
            size_t newDim = column ? col : row;
            size_t oldDim = vect.size();
            if(newDim == oldDim) return;
            if(newDim > oldDim){
                size_t i = newDim - oldDim;
                while(i){
                    vect.push_back(val);
                    i--;
                }
            }
            if(newDim < oldDim){
                vect.resize(newDim);
                vect.shrink_to_fit();
            }
            dim = newDim;
        }
        
        
        /*
         * Performs transpose operation on matrix
         */
        void transpose(){
            column = false;
        }
            
        
    };
}

//template<classT>

#endif //EX3_MTMVEC_H
