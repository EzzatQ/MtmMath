#include <stdio.h>
#include "MtmMatSq.h"

using namespace MtmMath;


template <class T>
MtmMatSq<T>& MtmMatSq<T>::operator=(const MtmMatSq& mat){
    return &MtmMatSq<T>(MtmMat<T>(mat));
}

