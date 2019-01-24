#ifndef EX3_MTMMATTRIAG_H
#define EX3_MTMMATTRIAG_H


#include <vector>
#include "MtmExceptions.h"
#include "Auxilaries.h"
#include "MtmMatSq.h"

using std::size_t;

namespace MtmMath {
    
    
    template <typename T>
    class MtmMatTriag : public MtmMatSq<T>{
        bool isUpper;
        
        class safeVec{
            MtmVec<T>* rowVect;
            MtmVec<T> const* const_rowVect;
            size_t rowNum;
            bool isUpper;
            
        public:
            
            safeVec(MtmVec<T>& v, size_t rowNum_t, bool isUpper_t):
                rowVect(&v), const_rowVect(NULL){
                rowNum = rowNum_t;
                isUpper = isUpper_t;
            }
            
            safeVec(const MtmVec<T>& v, size_t rowNum_t, bool isUpper_t):
            rowVect(NULL), const_rowVect(&v){
                rowNum = rowNum_t;
                isUpper = isUpper_t;
            }
            
            safeVec(const safeVec& sv): const_rowVect(sv.const_rowVect){
                rowVect = NULL;
                rowNum = sv.rowNum;
                isUpper = sv.isUpper;
            }
            
            
            safeVec(safeVec& sv): const_rowVect(NULL){
                rowVect = sv.rowVect;
                rowNum = sv.rowNum;
                isUpper = sv.isUpper;
            }

            
            T& operator[](size_t j){
                if(j >= rowVect->size()) {
                    throw MtmExceptions::AccessIllegalElement();
                }
                if((isUpper && j < rowNum) || (!isUpper && j > rowNum)){
                    throw MtmExceptions::AccessIllegalElement();
                }
                return (*rowVect)[j];
            }
            
            const T& operator[](size_t j) const{
                if(j >= const_rowVect->size()) {
                    throw MtmExceptions::AccessIllegalElement();
                }
                return (*const_rowVect)[j];
            }
        };
        
    public:
        
        /*
         * Triangular Matrix constructor, m is the number of rows and columns in the matrix,
         * val is the initial value for the matrix elements and isUpper_ is whether it is upper
         * Rectangular matrix (true means it is)
         */
        MtmMatTriag(size_t m, const T& val=T(), bool isUpper_t = true):
        MtmMatSq<T>(m,0){
            isUpper = isUpper_t;
            for(size_t i = 0; i < m; i++){
                for(size_t j = 0; j < m; j++)
                    if(isUpper){
                        this->matrix[i][j] = i <= j ? val : 0;
                    } else {
                        this->matrix[i][j] = i >= j ? val : 0;
                    }
            }
        }
        
        
        MtmMatTriag(const MtmMatTriag<T>& m): MtmMatSq<T>(m){
            *this = m;
        }
        
        MtmMatTriag(const MtmMatSq<T>& m): MtmMatSq<T>(m){
            bool Upper = true, Lower = true;
            for(size_t i = 0; i < m.getDim().getRow(); i++){
                for(size_t j = 0; j < m.getDim().getCol(); j++){
                    if(i < j && m[i][j] != 0) Lower = false;
                    if(i > j && m[i][j] != 0) Upper = false;
                }
            }
            if(!Upper && !Lower){
                throw MtmExceptions::IllegalInitialization();
            }
            isUpper = Upper ? true : false;
            
            MtmMat<T>::operator=(MtmMat<T>(m));
        }
        
        MtmMatTriag(const MtmMat<T>& m): MtmMatSq<T>(m){
            if(m.getDim().getRow() != m.getDim().getCol()){
                throw MtmExceptions::IllegalInitialization();
            }
            MtmMatSq<T> temp(m);
            *this = MtmMatSq<T>(temp);
            
        }
        
        
        MtmMatTriag& operator=(const MtmMatTriag<T>& m){
            isUpper = m.isUpper;
            this->matrix = m.matrix;
            this->dim = m.getDim();
            return *this;
        }
        
        safeVec operator[](size_t i){
            if(i >= this->dim.getRow()){
                throw MtmExceptions::AccessIllegalElement();
            }
            safeVec v(this->matrix[i], i, isUpper);
            return v;
        }
        
        const safeVec operator[](size_t i) const{
            if(i >= this->dim.getRow()){
                throw MtmExceptions::AccessIllegalElement();
            }
            safeVec v((this->matrix[i]), i, isUpper);
            return v;
        }
        
        void transpose(){
            MtmMat<T>::transpose();
            isUpper = !isUpper;
        }
        
        void resize(Dimensions dim, const T& val=T()){
            Dimensions oldDim = this->dim;
            MtmMatSq<T>::resize(dim, val);
            if(dim.getRow() < oldDim.getRow()) return;
            if(isUpper){
                for(size_t i = 0;\
                    i < dim.getRow(); i++){
                    for(size_t j = 0; j < i; j++){
                        this->matrix[i][j] = 0;
                    }
                }
            } else {
                for(size_t i = 0; i < dim.getRow(); i++){
                    for(size_t j = i + 1; j < dim.getCol(); j++){
                        this->matrix[i][j] = 0;
                    }
                }
            }
        }
        
    };
    
}

#endif //EX3_MTMMATTRIAG_H
