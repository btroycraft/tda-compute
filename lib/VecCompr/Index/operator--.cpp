#include <cstlib>
#include <cstdint>

#include "VecCompr.hpp"

// Decrements the Index object

VecCompr::Index& VecCompr::Index::operator--(){

  bool flag = offComp_ > widthComp_;

  ind_ -= flag;
  off_ = widthComp_ + UINT_VEC_COMPR_BIT*flag - offComp_;
  offComp_ = UINT_VEC_COMPR_BIT - off_;

  return *this;
}

VecCompr::Index VecCompr::Index::operator--(int){

  Index temp = *this;

  --*this;

  return temp;
}
