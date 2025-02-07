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
        MtmMatSq(size_t m = 1, const T& val=T()): \
        MtmMat<T>(Dimensions(m,m),val) {};
        
        ~MtmMatSq(){}
        
        MtmMatSq(const MtmMatSq& m): MtmMat<T>(m){};
        
        MtmMatSq(const MtmMat<T>& m): MtmMat<T>(m){
            if(m.getDim().getCol()!= m.getDim().getRow())
                throw MtmExceptions::IllegalInitialization();
        }
        
        MtmMatSq& operator=(const MtmMat<T>& m){
            MtmMat<T>::operator=(m);
            return *this;
        }
        
        virtual void resize(Dimensions dim, const T& val=T()){
            if(dim.getRow() != dim.getCol()){
                throw MtmExceptions::ChangeMatFail(this->dim, dim);
            }
            MtmMat<T>::resize(dim, val);
        }
        
        void reshape(Dimensions dim){
            throw MtmExceptions::ChangeMatFail(this->dim, dim);
        }
    };
    
}

#endif //EX3_MTMMATREC_H
