#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#include "vec_compr.h"
#include "vec_compr_int.h"

// Expand vector allocation to be at least "req" in size

bool expand_alloc_vec_compr(Vec_Compr *vec, size_t req){

  // Get new allocation size based on previous allocation size

  size_t reqExp;
  {
    float temp;
    for(temp = vec->alloc; temp <= req; temp *= ALLOC_MULT_VEC_COMPR);

    reqExp = tern_size_t_vec_compr_int(temp < SIZE_MAX, (size_t) temp, SIZE_MAX);
  }

  // Make reallocation

  void* init = realloc(vec->init, reqExp);

  // Check for failed allocation

  if(!init){

    // Retry using size "req" if necessary

    init = realloc(vec->init, req);

    if(!init){
      return true;
    }

    vec->alloc = req;
  }
  else{

    vec->alloc = reqExp;
  }

  vec->init = init;

  return false;
}
