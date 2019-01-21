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

        class safeVec {
            MtmVec<T>& rowVect;
            int rowNum;
            bool isUpper;
        public:
            
            //template <class S>
            safeVec(const MtmVec<T>& v, int rowNum_t, bool isUpper_t){
                rowVect = v;
                rowNum = rowNum_t;
                isUpper = isUpper_t;
            }
        
            safeVec(const safeVec& sv){
                *this = sv;
            }
            
            safeVec& operator=(const safeVec& sv){
                rowVect = sv.rowvect;
                rowNum = sv.rowNum;
                isUpper = sv.isUpper;
                return *this;
            }
            
            T& operator[](int j){
                if(j >= rowVect.size()) {
                    throw MtmExceptions::AccessIllegalElement();
                }
                if((isUpper && j < rowNum) || (!isUpper && j > rowNum)){
                    throw MtmExceptions::AccessIllegalElement();
                }
                return rowVect[j];
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
                        this->matrix[i][j] = i < j ? val : 0;
                    } else {
                        this->matrix[i][j] = i > j ? val : 0;
                    }
            }
        }
        
        ~MtmMatTriag();
        
        MtmMatTriag(const MtmMatTriag<T>& m): MtmMatSq<T>(m, 0){
            *this = m;
        }
        
        MtmMatTriag(const MtmMatSq<T>& m): MtmMatSq<T>(m, 0){
            
        }
        
        MtmMatTriag(const MtmMat<T>& m): MtmMatSq<T>(m, 0){
            
        }
        
        
        MtmMatTriag& operator=(const MtmMatTriag<T>& m){
            isUpper = m.isUpper;
            this->matrix = m.matrix;
            this->dim = m.dim;
            return *this;
        }
        
        safeVec& operator[](int i){
            if(i >= this->dim.getRow()){
                throw MtmExceptions::AccessIllegalElement();
            }
            safeVec v(this->matrix[i], i, isUpper);
            return v;
        }
        
        //MtmMatTriag<T>(const MtmMat<T>& m);
        
        //MtmMatTriag<T>(const MtmMatSq<T>& m);//is this neccessery? sq is mat
    };

}

#endif //EX3_MTMMATTRIAG_H
