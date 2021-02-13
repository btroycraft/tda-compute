#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#include "vec_compr.h"
#include "vec_compr_int.h"

// Extract value from vector at given index

inline uint_vec_compr_t extract_val_vec_compr(Vec_Compr vec, Index_Vec_Compr index){

  uint_vec_compr_t v1 = vec.init[index.ind] >> index.off;
  uint_vec_compr_t v2 = vec.init[index.ind+1] << (UINT_VEC_COMPR_BIT - index.off);

  return (v1 | v2) & ~(UINT_VEC_COMPR_MAX << vec.width);
}
