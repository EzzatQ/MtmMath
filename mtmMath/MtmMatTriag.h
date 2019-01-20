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
        //bool** legalAccess;
        MtmMat<T> Access; // m * m+1
    public:

        /*
         * Triangular Matrix constructor, m is the number of rows and columns in the matrix,
         * val is the initial value for the matrix elements and isUpper_ is whether it is upper
         * Rectangular matrix (true means it is)
         */
        MtmMatTriag<T> (size_t m, const T& val=T(), bool isUpper_t = true): MtmMatSq<T>(m,0){
            isUpper = isUpper_t;
            legalAccess = new bool*[m];
            for(int i = 0; i < m; i++){
                legalAccess[i] = new int[m];
            }
            for(int i = 0; i < m; i++){
                for(int j = 0; j < m; j++)
                    if(isUpper){
                        legalAccess[i][j] = i < j ? val : 0;
                    } else {
                        legalAccess[i][j] = i > j ? val : 0;
                    }
            }
        }
        
        ~MtmMatTriag<T>();
        
        MtmMatTriag<T>(const MtmMatTriag<T>& m): MtmMatSq<T>(m){
            isUpper = m.isUpper;
        }
        
        //MtmMatTriag<T>(const MtmMat<T>& m);
        
        //MtmMatTriag<T>(const MtmMatSq<T>& m);//is this neccessery? sq is mat
    };

}

#endif //EX3_MTMMATTRIAG_H
