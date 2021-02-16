#include <cstlib>
#include <cstdint>

#include "VecCompr.hpp"

// Constructor for the VecCompr class
// "width" parameter dictates the size in bits of a single element
// "add" parameter is an optional pointer containing additional information about the vector

VecCompr::VecCompr(std::size_t width = UINT_VEC_COMPR_BIT, void *add = NULL)
  : width_(width), end_(Index(width)), size_(SIZE_INIT_VEC_COMPR), add_(add)
{
  try{

    uint_vec_compr_t *init = (uint_vec_compr_t *) std::malloc(SIZE_INIT_VEC_COMPR * sizeof(uint_vec_compr_t));

    if(!init){
      throw std::bad_alloc();
    }

    init_ = init;
  }
}
