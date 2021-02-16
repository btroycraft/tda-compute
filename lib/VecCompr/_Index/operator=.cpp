#include <cstlib>
#include <cstdint>

#include "VecCompr.hpp"
#include "_Index.hpp"

// Overload the assignment = operator to assign the given value to the location referenced by the _Index proxy

void VecCompr::_Index::operator=(uint_vec_compr_t value){

  bool flag = index_.off_ > index_.widthComp_;

  init_[index_.ind_] = (init_[index_.ind_] & ~(UINT_VEC_COMPR_MAX >> index_.widthComp_ << index_.off_) | value << index_.off_;
  init_[index_.ind_ + flag] = (init_[index_.ind_ + flag] & ~(UINT_VEC_COMPR_MAX >> index_.widthComp_ >> index_.offComp_)) | value >> index_.offComp_;
}
