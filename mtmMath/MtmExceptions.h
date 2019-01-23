#ifndef EX3_MTMEXCEPTIONS_H
#define EX3_MTMEXCEPTIONS_H

#include <exception>
#include <string>
#include <iostream>
#include "Auxilaries.h"

namespace MtmMath {
    namespace MtmExceptions {
        class MtmExceptions : public std::exception {
        public:
            virtual ~MtmExceptions() throw() {}
        };
        
        /*
         * Exception for illegal initialization of an object, needs to output
         * "MtmError: Illegal initialization values" in what() class function
         */
        class IllegalInitialization : public MtmExceptions {
        public:
            std::string what(){
                return "MtmError: Illegal initialization values";
            }
        };
        
        /*
         * Exception for Memory allocation failure for an object, needs to output
         * "MtmError: Out of memory" in what() class function
         */
        class OutOfMemory : public MtmExceptions {
        public:
            std::string what(){
                return "MtmError: Out of memory";
            }
        };
        
        /*
         * Exception for dimension mismatch during a mathematical function, needs to output
         * "MtmError: Dimension mismatch: (<mat 1 row>,<mat 1 col>) (<mat 2 row>,<mat 2 col>)"
         * in what() class function
         */
        class DimensionMismatch : public MtmExceptions {
            Dimensions dim1;
            Dimensions dim2;
        public:
            DimensionMismatch(){}
            DimensionMismatch(Dimensions newDim1,Dimensions newDim2):dim1(newDim1) ,dim2(newDim2){}
            std::string what(){
                
                return "MtmError: Dimension mismatch: "+ dim1.to_string() +" " + dim2.to_string();
            }
        };
        
        /*
         * Exception for error for changing matrix/vector shape in reshape and resize, needs to output
         * "MtmError: Change matrix shape failed from: (<mat row>,<mat col>) (<new mat row>,<new mat col>)"
         * in what() class function
         */
        class ChangeMatFail : public MtmExceptions {
            Dimensions dim1;
            Dimensions dim2;
        public:
            ChangeMatFail(){}
            ChangeMatFail(Dimensions newDim1,Dimensions newDim2):dim1(newDim1) ,dim2(newDim2){}
            std::string what(){
                
                return "MtmError: Change matrix shape failed from: "+ dim1.to_string() +" " + dim2.to_string();
            }
        };
        
        /*
         * Exception for accessing an illegal element in matrix or vector, needs to output
         * "MtmError: Attempt access to illegal element" in what() class function
         */
        class AccessIllegalElement : public MtmExceptions {
        public:
            std::string what(){
                return "MtmError: Attempt access to illegal element";
            }
        };
    }
}


#endif //EX3_MTMEXCEPTIONS_H
