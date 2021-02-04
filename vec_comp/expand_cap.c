#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#include "vec_compr.h"
#include "vec_compr_int.h"

// Expand vector capacity to occomodate at least "num" new entries

bool expand_cap_vec_compr(Vec_Compr *vec, size_t num){

  size_t width = vec->width;
  size_t next = vec->next;
  size_t off = vec->off;

  if(num == 0 || width == 0){
    return false;
  }

  // Get required allocation size

  size_t req;
  {
    size_t q = num / CHAR_BIT;
    size_t r = num - CHAR_BIT*q;

    size_t v1 = width*q;
    size_t v2 = (width*r + off + (CHAR_BIT-1)) / CHAR_BIT;

    req = next + v1 + v2;

    // Check for possible size_t overflows

    if(q > SIZE_MAX / width || next > SIZE_MAX - v1 || next + v1 > SIZE_MAX - v2){
      return true;
    }
  }

  // Expand allocation

  return expand_alloc_vec_compr(vec, req);
}
