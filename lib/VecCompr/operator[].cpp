#include <cstlib>
#include <cstdint>

#include "VecCompr.hpp"

// Overload the r-value subset [] operator to extract the numerical value denoted by the given index object

uint_vec_compr_t VecCompr::operator[](std::size_t index) & {

  return Index_(index);
}

uint_vec_compr_t VecCompr::operator[](std::size_t ind) & {

  return Index_(Index(ind));
}

uint_vec_compr_t VecCompr::operator[](Index index) && {

  bool flag = index.off_ > index.widthComp_;

  return (init_[index.ind_] >> index.off_ | init_[index.ind_ + flag] << index.offComp_) & UINT_VEC_COMPR_MAX >> index.widthComp_;
}
