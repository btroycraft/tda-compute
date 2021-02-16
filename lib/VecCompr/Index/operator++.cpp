#include <cstlib>
#include <cstdint>

#include "VecCompr.hpp"

// Increments the Index object

VecCompr::Index& VecCompr::Index::operator++(){

  bool flag = off_ > widthComp_;

  ind_ += flag;
  offComp_ = widthComp_ + UINT_VEC_COMPR_BIT*flag - off_;
  off_ = UINT_VEC_COMPR_BIT - offComp_;

  return *this;
}

VecCompr::Index VecCompr::Index::operator++(int){

  Index temp = *this;

  ++*this;

  return temp;
}
