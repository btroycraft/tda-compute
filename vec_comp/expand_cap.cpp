#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>

#include "vec_compr.h"
#include "vec_compr_int.h"

// Expand vector capacity to occomodate at least "num" new entries

bool expand_cap_vec_compr(Vec_Compr vec, size_t num){

  if(num == 0 || vec.width == 0){
    return false;
  }

  // Get required allocation size

  size_t req;
  {
    size_t q = num / UINT_VEC_COMPR_BIT;
    size_t r = num - UINT_VEC_COMPR_BIT*q;

    size_t v1 = vec.width*q;
    size_t v2 = (vec.width*r + vec.end.off + (UINT_VEC_COMPR_BIT-1)) / UINT_VEC_COMPR_BIT;

    req = vec.end.ind + v1 + v2;

    // Check for possible size_t overflows

    if(q > SIZE_MAX / vec.width || vec.end.ind > SIZE_MAX - v1 || vec.end.ind + v1 > SIZE_MAX - v2){
      errno = ENOMEM;
      return vec;
    }
  }

  // Expand allocation

  errno = 0;

  return expand_alloc_vec_compr(vec, req);
}
