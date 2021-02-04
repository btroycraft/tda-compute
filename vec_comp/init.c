#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#include "vec_compr.h"
#include "vec_compr_int.h"

// Initialize vector with initial allocation
// Requires "width" parameter dictating the size in bits of a single element
// "add" parameter is an optional pointer containing additional information about the vector

bool init_vec_compr(Vec_Compr *vec, size_t width, void *add){

  void *init = malloc(ALLOC_INIT_VEC_COMPR);
  if(!init){
    return true;
  }

  *vec = (Vec_Compr) {.init = init, .width = width, .next = 0, .off = 0, .alloc = ALLOC_INIT_VEC_COMPR, .add = add};

  return false;
}
