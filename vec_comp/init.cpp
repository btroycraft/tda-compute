#include "vec_compr.h"
#include "vec_compr_int.h"

// Initialize vector with initial allocation
// Requires "width" parameter dictating the size in bits of a single element
// "add" parameter is an optional pointer containing additional information about the vector

void VecCompr::VecCompr(size_t width = UINT_VEC_COMPR_BIT, void *add = NULL){

  init = new uint_vec_compr_t[ALLOC_INIT_VEC_COMPR];
  this->width = width;

  *vec = (Vec_Compr) {.init = init, .width = width, .alloc = ALLOC_INIT_VEC_COMPR, .add = add};

  return;
}
