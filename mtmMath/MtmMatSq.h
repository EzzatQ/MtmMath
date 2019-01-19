#ifndef EX3_MTMMATREC_H
#define EX3_MTMMATREC_H

#include <vector>
#include "MtmExceptions.h"
#include "Auxilaries.h"
#include "MtmMat.h"

using std::size_t;

namespace MtmMath {
    
    template <typename T>
    class MtmMatSq : public MtmMat<T>{
    public:
        /*
         * Rectangular Matrix constructor, m is the number of rows and columns in the matrix
         * and val is the initial value for the matrix elements
         */
        MtmMatSq (size_t m, const T& val=T()): \
        MtmMat<T>(Dimensions(m,m),val) {};
        
        MtmMatSq(const MtmMat<T>& m): MtmMat<T>(m){
            if(m.dim.getCol()!=m.dim.getRow())
                throw MtmExceptions::DimensionMismatch();
        };
        
        MtmMatSq(const MtmMatSq& m): MtmMatSq<T>(m){};
        
        virtual void resize(Dimensions dim, const T& val=T()){
            if(dim.getRow() != dim.getCol()){
                throw MtmExeptions::DimensionMismatch();
            }
            MtmMat<T>::resize(dim, cal);
        }
        
        void reshape(Dimensions dim){
            throw MtmExceptoins::ChangeMatFail();
        }
    };
    
}

#endif //EX3_MTMMATREC_H
