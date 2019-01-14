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
    public: ///////////////////////////////
        MtmVec<MtmVec<T>> matrix;
        Dimensions dim;
    public:
        /*
         * Matrix constructor, dim_t is the dimension of the matrix and val is the initial value for the matrix elements
         */
        MtmMat(Dimensions dim_t, const T& val=T());
        
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
            if(i >= dim.getRow()){
                throw MtmExceptions::AccessIllegalElement();
            }
            MtmVec<T> a;
            for (int j = 0; j < dim.getRow(); j++) {
                a.vect[j]= &matrix[j][i];
            }
            return &a;
        }
        
        const MtmVec<T>& operator[](const int i) const{//what to do here..?
            if(i >= dim.getCol()){
                throw MtmExceptions::AccessIllegalElement();
            }
            return matrix[i];
        }

    };
}


#endif //EX3_MTMMAT_H
