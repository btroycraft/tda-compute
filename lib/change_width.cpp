#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#include "vec_compr.h"
#include "vec_compr_int.h"

// Expand vector capacity to occomodate at least "num" new entries

bool expand_width_vec_compr(Vec_Compr vec, size_t width){

  const Index_Vec_Compr next = vec.next;
  size_t widthOut = width;
  const size_t widthIn = vec->width;
  const size_t next = vec->next;
  const size_t off = vec->off;

  if((vec.next == 0 && vec.off == 0) || vec.width == width){
    return false;
  }

  size_t req;
  {
    // Get required allocation size and check for possible size_t overflows

    size_t q = next / widthIn;
    size_t r = next - widthIn*q;

    {
      if(q > SIZE_MAX / widthOut){
        return true;
      }

      req = widthOut*q;
    }

    {
      size_t temp = (widthOut*((CHAR_WIDTH*r + off) / widthIn) + (CHAR_WIDTH-1)) / CHAR_WIDTH;
      if(req > SIZE_MAX - temp){
        return true;
      }

      req += temp;
    }
  }

  if(expand_alloc_vec_c(vec, req)){
    return true;
  }


}
