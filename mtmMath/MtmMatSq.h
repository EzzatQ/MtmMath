#ifndef EX3_MTMMATREC_H
#define EX3_MTMMATREC_H

#include <vector>
#include "MtmExceptions.h"
#include "Auxilaries.h"
#include "MtmMat.h"

using std::size_t;

namespace MtmMath {

    template <typename T>
    class MtmMatSq:protected MtmMat<T>{
    public:
        /*
         * Rectangular Matrix constructor, m is the number of rows and columns in the matrix
         * and val is the initial value for the matrix elements
         */
        MtmMatSq (size_t m, const T& val=T()): \
                                        MtmMat<T>(Dimensions(m,m),val) {};
        ~MtmMatSq(){}; //
        MtmMatSq(const MtmMat<T>& m):MtmMat<T>(m){};
        MtmMatSq(const MtmMatSq& m):MtmMat<T>(m){};
        MtmMatSq& operator=(const MtmMatSq& mat);
        
        //might need changing
        /*MtmMatSq& operator+=(const MtmMatSq& mat);
        MtmMatSq& operator+=(const T& s);
        MtmMatSq& operator-=(const MtmMatSq& mat);
        MtmMatSq& operator-=(const T& s);
        MtmMatSq& operator*=(const MtmMatSq& mat);
        MtmMatSq& operator*=(const T& s);
        MtmMatSq& operator*=(const MtmVec<T>& vec);*/
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
         * Performs transpose operation on matrix
         */
        virtual void transpose();
    };

}

#endif //EX3_MTMMATREC_H
