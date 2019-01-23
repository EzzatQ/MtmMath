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
            int rowNum;
            bool isUpper;
            
        public:
            
            safeVec(MtmVec<T>& v, int rowNum_t, bool isUpper_t): rowVect(&v){
                rowNum = rowNum_t;
                isUpper = isUpper_t;
            }
            
            safeVec(const safeVec& sv){
                *this = sv;
            }
            
            safeVec& operator=(const safeVec& sv){
                rowVect = sv.rowVect;
                rowNum = sv.rowNum;
                isUpper = sv.isUpper;
                return *this;
            }
            
            T& operator[](int j){
                if(j >= rowVect->size()) {
                    throw MtmExceptions::AccessIllegalElement();
                }
                if((isUpper && j < rowNum) || (!isUpper && j > rowNum)){
                    throw MtmExceptions::AccessIllegalElement();
                }
                return (*rowVect)[j];
            }
            
            const T& operator[](int j) const{
                if(j >= rowVect->size()) {
                    throw MtmExceptions::AccessIllegalElement();
                }
                if((isUpper && j < rowNum) || (!isUpper && j > rowNum)){
                    throw MtmExceptions::AccessIllegalElement();
                }
                return (*rowVect)[j];
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
            for(int i = 0; i < m; i++){
                for(int j = 0; j < m; j++)
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
            for(int i = 0; i < m.getDim().getRow(); i++){
                for(int j = 0; j < m.getDim().getCol(); j++){
                    if(i < j && m[i][j] != 0) Upper = false;
                    if(i > j && m[i][j] != 0) Lower = false;
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
        
        safeVec operator[](int i){
            if(i >= this->dim.getRow()){
                throw MtmExceptions::AccessIllegalElement();
            }
            safeVec v(this->matrix[i], i, isUpper);
            return v;
        }
        
        const safeVec operator[](int i) const{
            if(i >= this->dim.getRow()){
                throw MtmExceptions::AccessIllegalElement();
            }
            safeVec v(this->matrix[i], i, isUpper);
            return v;
        }
        
        void transpose(){
            MtmMat<T>::transpose();
            isUpper = !isUpper;
        }
        
        void resize(Dimensions dim, const T& val=T()){
            MtmMatSq<T>::resize(dim, val);
            if(dim.getRow() < this->dim.getRow()) return;
            if(isUpper){
                for(int i = static_cast<int>(this->dim.getRow());\
                    i < dim.getRow(); i++){
                    for(int j = 0; j < i; j++){
                        this->matrix[i][j] = 0;
                    }
                }
            } else {
                for(int i = 0; i < dim.getRow(); i++){
                    for(int j = i + 1; j < dim.getCol(); j++){
                        this->matrix[i][j] = 0;
                    }
                }
            }
        }
        
    };
    
}

#endif //EX3_MTMMATTRIAG_H
