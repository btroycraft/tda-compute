#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#include "vec_compr.h"
#include "vec_compr_int.h"

// Give the next index in the compressed array

inline void next_index_vec_compr(Vec_Compr vec, Index_Vec_Compr index){

  bool flag = vec.width + index.off > UINT_VEC_COMPR_BIT;

  return (Index_Vec_Compr) {.ind = index.ind + flag, .off = index.off + vec.width - UINT_VEC_COMPR_BIT*flag};
}
