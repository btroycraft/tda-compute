#include <cstlib>
#include <cstdint>

#include "VecCompr.hpp"

// Expand vector allocation to at least the required size

void VecCompr::increase_size_to(std::size_t req){

  // Get new size via multiples of the previous size

  std::size_t reqExp;
  {
    float temp;
    for(temp = size_; temp <= req; temp *= SIZE_MULT_VEC_COMPR);

    reqExp = temp < SIZE_MAX ? (std::size_t) temp : SIZE_MAX;
  }

  // Make reallocation

  uint_vec_compr_t *init;
  try{

    init = (uint_vec_compr_t *) std::realloc(init_, reqExp*sizeof(uint_vec_compr_t));

    if(!init){
      throw std::bad_alloc();
    }

    size_ = reqExp;
  }
  catch(std::bad_alloc){

    // Retry using size "req" if necessary

    try{

      init = (uint_vec_compr_t *) std::realloc(init_, req*sizeof(uint_vec_compr_t));

      if(!init){
        throw std::bad_alloc();
      }

      size_ = req;
    }
  }

  init_ = init;
}
