#include <cstlib>
#include <cstdint>

#include "VecCompr.hpp"

// Expand VecCompr capacity to occomodate a number of new entries

void VecCompr::increase_size_by(std::size_t num){

  if(num == 0){
    return;
  }

  // Get required allocation size

  try{

    std::size_t q = num / UINT_VEC_COMPR_BIT;
    std::size_t r = num - UINT_VEC_COMPR_BIT*q;

    std::size_t v1 = width_*q;
    std::size_t v2 = (width_*r + end_.off_ + (UINT_VEC_COMPR_BIT-1)) / UINT_VEC_COMPR_BIT;

    std::size_t req = end_.ind_ + v1 + v2;

    // Check for possible size_t overflows in req

    if(q > SIZE_MAX / width_ || end_.ind_ > SIZE_MAX - v1 || end_.ind_ + v1 > SIZE_MAX - v2){
      throw std::bad_alloc();
    }

    increase_size_to(req);
  }
}
